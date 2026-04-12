#include<iostream>
#include<assert.h>
#include<string>
using namespace std;
int main()
{
	string a = "hello world";
	string::iterator it = a.begin();//auto it=a.begin()
	//begin返回的是迭代器类型
	cout << *it << " ";
	//迭代器：
	//1.迭代器不一定是指针，但很像指针
	while (it != a.end())//end指向的是最后一个字符的再后一个
	{
		cout << *it << " ";
		it++;
	}
	//范围for
	//1.自动把a里的给了t
	//2.自动加加
	//3.原理：被替换成迭代器类似于上面代码
	for (auto t : a)
	{
		cout << t << " ";
	}
}