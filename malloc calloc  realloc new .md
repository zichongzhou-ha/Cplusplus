## malloc calloc realloc new 用法
1. malloc 申请空间
   ```
    char* p = (char*)malloc(sizeof(char) * 6);//开6个字节
    if (p == NULL)
    {
    printf("分配失败");
    return 1;
    }
    ```
2. calloc 申请空间，并默认初始化为0
    ```
   	char* p = (char*)calloc(5,sizeof(char));//开5个字节
	if (p == NULL)
	{
		printf("分配失败");
		return 1;
	}
    ```
3. realloc 对原有空间进行扩容
   ```
    char* p1 = (char*)realloc(p, sizeof(char) * 10);
    if (p == NULL)
    {
        printf("分配失败");
        return 1;
    }
    ```
    >然后统一用free释放空间
    ## 然后C++为什么要引入new  ##
4. new
- new不仅申请了空间，与malloc最根本性的差别是还进行了初始化，即调用了构造函数。
- 此外，new申请空间如果失败了，会抛异常，但malloc不会
  > char* p = new char[4];
- new的空间最后通过delete释放
  >delete不仅释放空间，还调用了析构函数

## 那么，怎么以C语言的方式完成对象的构造和初始化？ 

引入 operator new
> 与malloc区别:都申请空间，但处理错误的方式不一样，malloc出错返回0，而operator new出错会抛异常
所以operator new是通过malloc+失败抛异常来实现的

```
int main()
{
	//test_string();
	A* p = new A(3);
	delete p;
	//仿造
	A* p1 = (A*)operator new(sizeof(A));
	new (p1)A(3);
    p1->~A();
	operator delete(p1);
	return 0;
}
```