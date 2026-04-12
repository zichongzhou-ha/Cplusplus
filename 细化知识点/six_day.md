### 左值引用 右值引用

左值引用 &：
- 绑左值
- 表达共享、别名

右值引用 &&：
- 绑右值
- 表达临时值、即将销毁的值
- 用来实现移动语义，偷资源，避免拷贝

移动语义的意义
- 大对象拷贝昂贵（string、vector、智能指针）
- 临时对象马上销毁，不用白不用
- 移动 = 偷家，速度极快

---

### bind

- 适配器：把一个原本不满足接口的东西 → 包装一下 → 变成满足你要的接口。
    - stack/queue 包装 容器（vector/list/deque）
    - bind 包装 函数 / 可调用对象
    - 让它 “变个样子” 给别人用。
- 为什么要有这个函数
>   比如有个接口，只接受无参函数：

    void run(function<void()> func) {
        func();
    }

    但你只有一个带参函数：
    void test(int x) { ... }
    直接传不行，用 bind 适配：run(bind(test, 10));
    bind 就是为了让不匹配的函数，变得匹配

- 用法

**bind 就是：提前把一些参数绑死，生成一个新的函数。**

1. 绑死所有参数
```
有个两参数函数：
int add(int a, int b) {
    return a + b;
}
//你想让它变成不用传参就能调用：
auto f = bind(add, 10, 20);

<!-- 这就表示：
调用 f() 的时候
自动调用 add(10, 20) -->

cout << f() << endl;   // 输出 30
```

2. 绑死一部分，留一部分（最常用）

```
//用 placeholders::_1 表示 “以后再传的参数”。
auto add10 = bind(add, 10, placeholders::_1);

<!-- 意思：
第一个参数固定为 10
第二个参数 = 以后调用时传的第一个参数 -->

<!-- add10(20);  → add(10,20)
add10(50);  → add(10,50)
bind 把 2 参 → 适配成 1 参 -->

```

3. 调换参数顺序
```
void print(int a, int b) {
    cout << a << " " << b << endl;
}
<!-- 想让参数反过来： -->
auto f = bind(print, placeholders::_2, placeholders::_1);

f(10, 20); → print(20, 10);
<!-- bind 改变参数顺序来适配接口 -->

```

4. 绑定成员函数（重要）
```
//成员函数必须带对象或指针，bind 可以帮你绑好：
struct A {
    void show(int x) {
        cout << x << endl;
    }
};
A a;
a.show(100);
//用 bind 包装成普通函数：
auto f = bind(&A::show, &a, placeholders::_1);
f(100);  // 等价 a.show(100)
bind 把成员函数 → 适配成普通可调用对象
```

5. 为什么要用 bind？（真实场景）
```
比如有个接口，只接受无参函数：

void run(function<void()> func) {
    func();
}

void test(int x) { ... }
//直接传不行，用 bind 适配：
run(bind(test, 10));

```
### function + bind

function 也是适配器，而且它和 bind 是天生一对，几乎总是配合使用。

1. function 是什么适配器？
function 是 “可调用对象包装器” 适配器
也叫：类型擦除适配器
它做的事情就一句话：把各种乱七八糟的可调用类型，统一包装成同一个类型
比如：
    - 普通函数
    - lambda
    - 函数指针
    - 仿函数
    - 成员函数
    - bind 表达式
它们类型全都不一样，但套上 function 之后：function<void(int)> f;
全部变成 同一个类型 function<void(int)>。
所以它的身份是：接口统一适配器 / 类型擦除适配器

2. function 和 bind 配合使用

- bind 会生成一个奇怪的匿名类型对象,你没法直接写它的类型，也存不起来,用 function 一包装，就能存、能传、能赋值

3. 最经典配合示例

```
void print(int a, int b)
{
    cout << a << " " << b << endl;
}
//用 bind 生成一个新函数：
auto bf = bind(print, 10, placeholders::_1);

<!-- 但 bf 的类型是匿名的，很难用。
套上 function 就舒服了： -->

function<void(int)> f = bind(print, 10, placeholders::_1);
现在你可以：放 vector 里 做函数参数 做成员变量
```

4. 最常用场景：把成员函数变成普通可调用对象

```
struct A
{
    void show(int x)
    {
        cout << x << endl;
    }
};

A a;
function<void(int)> f = bind(&A::show, &a, placeholders::_1);

f(100);  // 完美调用
```

这就是：
bind 负责适配参数
function 负责包装类型

5. 一句话总结

stack 适配容器
bind 适配函数参数、顺序、成员函数
function 适配类型，把所有可调用对象统一成一种类型（类型擦除）
bind + function = C++ 里最强大的函数接口适配组合
