### c++很多都是对c语言缺陷的修改
- c语言的struct默认都是public,访问都是公有的，不安全----->类+访问限定符
- c语言有初始化和销毁的问题---------->构造和析构函数
- c语言如果想定义两个栈，一个存double,一个存int,做不到----------->模板






### static修饰变量
- static修饰局部变量时，首先，它只初始化一次，其次，改变了它的生命周期，程序结束才会销毁，没有改变作用域，最后，初始化的时机是在第一次进入函数运行到它时才初始化，出了函数一次下一次进入不用再初始化，因为只初始化一次，其它的局部变量都是每次进入进行一次初始化
- static修饰全局变量，首先，它和全局变量一样，在main函数执行前就进行初始化，其次，不一样的是，全局变量默认是外部链接的属性，而被static修饰后就变为内部链接的属性了

> 这里就要重点谈谈链接属性的问题了，一般来说，编译：预处理-编译-汇编-链接，而这里的链接就是将多个相关的.cpp或其它文件进行链接，如果其中一个文件要用到另一个文件里的变量时，这时候只需要extern 变量，这里是声明这个变量在其它文件里已经被定义了，这时候就可以用这个变量了，但是如果这个变量在源文件里已经被设为了内部链接属性，那么申明了extern你也是找不到它的

>这里谈到了extern:extern 用于跨文件链接，和 #include 无关；
#include 只是文本替换，不属于链接阶段行为。
- 补充：未显式初始化的全局变量和静态变量，会被自动初始化为 0（放在 BSS 段）；而普通局部变量不初始化是随机垃圾值。


### 内存四区  
- 栈区 堆区 静态区 代码区(代码段)
- 每个区的作用暂且先不管，主要对静态区解释下：静态区=已初始化的数据区+未初始化的数据区=data段(数据段)+BSS

- BSS 段存放未初始化的全局变量和静态变量。
- 系统会自动将 BSS 段内存初始化为 0。
- BSS 不占用可执行文件空间，只记录长度。
- 已初始化的全局 / 静态变量放在 data 段。


### 今天被创死的一道算法题
- 忘记怎么读一行了
- replace的使用
- getline以及cin.ignore的使用
- 不贴题目了，看看就知道是来干嘛的了

```
#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<string>nums(n);
    for(int i=0;i<n;i++)cin>>nums[i];
    int k;
    cin>>k;
    cin.ignore();
    string text;
    getline(cin,text);
    string ret=text;
    int cnt=0;
    for(int i=0;i<n;i++)
        {
            string key=nums[i];
            int pos=0;
            int len=key.size();
            while(pos=ret.find(key,pos)!=string::npos)
                {
                    cnt++;
                    ret.replace(pos,len,"<censored>");
                    pos+=len;
                }
        }
    if(cnt<k)cout<<ret;
    else 
    {
        cout<<cnt<<endl;
        cout<<"He Xie Ni Quan Jia!";
    }
    return 0;
}
```