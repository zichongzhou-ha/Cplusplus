# list
## 为什么要有list
- vector存在以下的缺点：
    1. 当要进行中部插入数据和头插时，需要挪动数据，时间复杂度较高。
    2. 插入数据时空间不够需要扩容，扩容需要开辟新空间，拷贝数据，释放旧空间。
- list的出现就是会了解决vector的缺陷
    1. list中部插入数据和头插时不需要挪动数据，只需要开辟新的节点。
    2. 插入数据不需要扩容
    3. 但是，于vector相比，也存在缺陷：不能随机访问。
## list的常见操作
```
int main()
{
	list<int>a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	for (auto i : a)
	{
		cout << i << " ";
	}
	cout << endl;
	a.push_front(0);
	a.push_front(-1);
	a.push_front(-2);
	a.push_front(-3);
	list<int>::iterator it = a.begin();
	while(it!=a.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	list<int>::reverse_iterator itt = a.rbegin();
	while (itt != a.rend())
	{
		cout << *itt << " ";
		itt++;
	}
	list<int>a;
a.push_back(1);
a.push_back(2);
a.push_back(3);
a.push_back(4);
a.push_back(5);
a.push_back(6);
a.push_back(7);
for (auto i : a)
{
	cout << i << " ";
}
cout << endl;
//a.insert(a.begin() + 3, 5);不支持这个操作，因为他不像数组一样是连续的
list<int>::iterator pos = find(a.begin(), a.end(), 3);
if (pos != a.end())
{
	a.insert(pos, 5);
}
a.sort();
list<int>::iterator it = a.begin();
while (it != a.end())
{
	if (*it % 2 == 0)
	{
		//a.erase(it);报错，erase之后就失效了
		it = a.erase(it);
	}
	else
	{
		it++;
	}
}
for (auto i : a)
{
	cout << i<<" ";
}

	return 0;
}

```

## list的模拟实现