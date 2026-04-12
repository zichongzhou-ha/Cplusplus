
### 如果对象中涉及到资源管理时，千万不能使用memcpy进行对象之间的拷贝，因为memcpy是浅拷贝，否则可能会引起内存泄漏甚至程序崩溃。

- memcpy 是按字节逐字节拷贝，只拷贝指针的值，不拷贝指向的资源 → 两个对象指向同一块内存 → 析构时同一块内存释放两次 → 程序直接崩溃

```
class String {
public:
    String(const char* str = "") {
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
    }

    ~String() {
        delete[] _str;  // 析构释放资源
    }
private:
    char* _str;
};

int main() {
    String s1("hello");
    String s2;

    // 用 memcpy 拷贝对象
    memcpy(&s2, &s1, sizeof(String));
}


<!-- 只把 s1 的内存按字节复制给 s2
s1 里是一个指针 0x11223300
s2 里也变成了 0x11223300
结果：
s1._str 和 s2._str 指向同一块堆内存！
这就是浅拷贝。 -->

```

--- 

### 写时复制

核心思想
    - 刚开始拷贝对象时：做浅拷贝，大家共用同一块内存，用一个引用计数记录有多少人在用。只要只读，不修改：永远不拷贝，效率极高。
    - 一旦有人要修改数据：才真正开辟新空间 + 深拷贝，改自己的副本，不影响别人。
    - 析构时：引用计数 - 1，减到 0 才真正释放内存。

```
class String {
private:
    char* _str;
    int* _refCount;  // 引用计数，大家共享

String(const String& s)
    : _str(s._str)
    , _refCount(s._refCount)
{
    ++(*_refCount);
}
~String() {
    if (--(*_refCount) == 0) {
        delete[] _str;
        delete _refCount;
    }
}
};
string s1 = "hello";
string s2 = s1;   // 【浅拷贝】s2 和 s1 共享同一块内存
string s3 = s1;   // 继续共享

s2[0] = 'x';
<!-- 触发 COW：
发现引用计数 > 1
开辟新空间
深拷贝一份内容
s2 指向新空间
引用计数各自更新 -->
```

- C++11 之后，很多标准库的 string 都放弃了 COW

---