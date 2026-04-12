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

```
#include<assert.h>
namespace CC
{
	template<class T>
	struct _list_node
	{
		_list_node* _next;
		_list_node* _prev;
		T val;
		_list_node(const T& x=T())
			:val(x)
		{}
	};

	//_list_iterator<T,T&,T*> ->iterator
	//_list_iterator<T,const T&,const T*> ->const_iterator
	template<class T,class Ref,class Ptr>
	struct _list_iterator
	{
		typedef _list_node<T> Node;
		typedef _list_iterator<T, Ref, Ptr> Self;
		Node* node;
		_list_iterator(Node* x)
			:node(x)
		{}
		//*it
		Ref operator *()
		{
			return node->val;
		}
		//it++
		Self& operator ++()
		{
			node = node->_next;
			return *this;
		}
		//it++
		Self operator++(int)//后置的不能返回引用，因为后置加加的目的不过是要返回一个值而已
		{
			Self tmp(*this);
			node = node->_next;
			return tmp;
		}
		Self& operator --()
		{
			node = node->_prev;
			return *this;
		}
		Self operator--(int)
		{
			Self tmp(*this);
			node = node->_prev;
			return tmp;
		}
		//
		//it!=end
		bool operator!= (const Self& it)
		{
			return node != it.node;
		}
		Ptr operator->()
		{
			return &node->val;
		}
		
	};
	template <class T>
	class list
	{
		typedef _list_node<T> Node;
	public:
		typedef _list_iterator< T, T&,T*> iterator;
		typedef _list_iterator<T, const T&, const T*> const_iterator;
		list()
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator begin()const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end()const
		{
			return const_iterator(_head);
		}
		void push_back(const T& x)
		{
			Node* newnode = new Node(x);
			Node* _end = _head->_prev;

			newnode->_prev = _end;
			newnode->_next = _head;
			_end->_next = newnode;
			_head->_prev = newnode;

		}
		void pop_back()
		{
			//erase(_head->_prev);
			erase(--end());
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		void pop_front()
		{
			erase(begin());
		}

		void insert(iterator pos, const T& x)
		{
			Node* cur = pos.node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);

			prev->_next = newnode;
			newnode->_next = cur;
			newnode->_prev = prev;
			cur->_prev = newnode;
		}
		void erase(iterator pos)
		{
			assert(pos != end());
			Node* cur = pos.node;
			Node* next = cur->_next;
			Node* prev = cur->_prev;
			delete cur;
			
			prev->_next = next;
			next->_prev = prev;
			
		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}

		list(const list<T>& lt)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			/*const_iterator it = lt.begin();
			while (it != lt.end())
			{
				push_back(*it);
				it++;
			}*/
			for (auto i : lt)
			{
				push_back(i);
			}
		}
		/*list<T>& operator=(const list<T>& lt)
		{
			if (this != &lt)
			{
				clear();
				for (auto e : lt)
				{
					push_back(e);
				}
			}
			
			return *this;
		}*/
		//现代写法
		list<T>& operator=(list<T> lt)//不用担心空间问题，因为出了作用域调析构函数释放空间了
		{
			swap(_head, lt._head);
			return *this;
		}
	private:
		Node* _head;

	};
	void test()
	{
		list<int>lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

	}
	struct Date
	{
		int year;
		int month;
		int day;
	};
	void test1()
	{
		list<Date> lt;
		lt.push_back(Date());
		lt.push_back(Date());
		lt.push_back(Date());
		list<Date>::iterator it = lt.begin();//it是迭代器，我们把它当作指针用
		//cout << *it;//这里肯定报错，原因是*it-->Date-->需要重载
		cout << (*it).day << " " << (*it).month << " " << (*it).year << endl;//这肯定是可以的，但不常用，应该用->
		cout << it->day << " " << it->month << " " << it->year << endl;//it->Date*这里编译器肯定是做了特殊处理了多加了->
	}
	void Printlist(const list<int>& lt)
	{
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			//*it = 1;
			cout << *it << " ";
			it++;
		}
		cout << endl;
	}
	void test2()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		Printlist(lt);
	}
	void test3()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_front(100);
		lt.erase(lt.begin());
		lt.pop_back();
		Printlist(lt);
		list<int>lt1(lt);
		Printlist(lt1);
		lt.push_back(100);
		lt.push_back(100);
		lt.push_back(100);
		lt1 = lt;
		Printlist(lt1);

	}
}
int main()
{
	CC::test3();
	return 0;
}
```
- vector和list的区别：
- vector是一个可动态增长的数组：
	- 优点：随机访问operator[]-》很好的支持排序，二分查找，堆算法等
	- 缺点：头部或者中间的插入删除效率低+空间不够增容的代价较大
- list是一个带头双向循环的链表
	- 优点：任意位置插入删除数据效率高
	- 缺点：不支持随机访问
- 总结：vector和list是两个相辅相成，互补的容器