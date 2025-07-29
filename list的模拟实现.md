```
#pragma once
#include<assert.h>
namespace bit
{
	template<class T>
	struct _list_node
	{
		_list_node<T>* _next;
		_list_node<T>* _prev;
		T _data;
		/*_list_node()
		{

		}*/
		_list_node(const T& x=T()):_data(x),_next(nullptr),_prev(nullptr)
		{

		}
	};

	template<class T,class Ref,class Ptr>
	struct _list_iterator
	{
		typedef _list_node<T> Node;
		typedef _list_iterator<T, Ref,Ptr> Self;
		Node* _node;
		_list_iterator(Node* node):_node(node)
		{

		}
		Ref operator*()
		{
			return _node->_data;
		}
		Self& operator++()
		{
			_node = _node->_next;

			return *this;
		}
		Self operator++(int)
		{
			Self tmp(*this);
			//_node = _node->_next;
			++(*this);
			return tmp;

		}
		Self& operator--()
		{
			_node = _node->_prev;

			return *this;
		}
		Self operator--(int)
		{
			Self tmp(*this);
			--(*this);
			return tmp;

			return *this;
		}
		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}
		Ptr operator->()
		{
			return  &_node->_data;
		}
	};
	template<class T>
	class list
	{
		typedef _list_node<T> node;
		
	public:
		typedef  _list_iterator<T, T&, T*> iterator;
		typedef  _list_iterator<T, const T&, const T*> const_iterator;
		list()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head; 
		}
		list(const list<T>& It)
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;

			/*const_iterator it = It.begin();
			while (it != It.end())
			{
				push_back(*it);
				++it;
			}*/
			for (auto e : It)
			{
				push_back(e);
			}
		}
		list<T>& operator=(const list<T>& lt)
		{
			if (*this != &lt)
			{
				clear();
				for (auto e : lt)
				{
					push_back(e);
				}
				return *this;
			}
		}
		//现代写法
		//list<T> operator=(const list<T> lt)//不带引用，传参时先拷贝一份来为后面的交换
		//{
		//	swap(_head, lt._head);
		//	return *this;
		//}
		void push_back(const T& x)
		{
			/*node* newnode = new node(x);
			node* tail = _head->_prev;

			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;*/
			insert(end(), x);
		}
		void pushfront(const T& x)
		{
			insert(begin(), x);
		}
		iterator begin()
		{
			return iterator(_head->_next);
		}
		const_iterator begin()const
		{
			return const_iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator end()const
		{
			return const_iterator(_head);
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
		void insert(iterator pos, const T& x)
		{
			node* newnode = new node(x);
			node* cur = pos._node;
			node* prev = cur->_prev;
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
		}
		void erase(iterator pos)
		{
			assert(pos != end());
			node* cur = pos._node;
			node*prev = cur->_prev;
			node* next = cur->_next;
			delete cur;
			prev->_next = next;
			next->_prev = prev;

		}
		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
	private:
		node* _head;
	};
	void test()
	{
		list<int> L;
		L.push_back(1);
		L.push_back(2);
		L.push_back(3);
		L.push_back(4);
		L.push_back(5);
		list<int>::iterator it = L.begin();
		while (it != L.end())
		{
			cout << *it<<" ";
			it++;
		}
		cout << endl;
	}
	struct Date
	{
		int year = 0;
		int month = 8;
	};
	void test2()
	{
		list<Date>l;;
		l.push_back(Date());
		l.push_back(Date());
		list<Date>::iterator it = l.begin();
		while (it != l.end())
		{
			//cout << *it << " ";//*it是一个结构体，所以报错
			//cout <<(& (*it))->month << " ";//硬要用就这样
			//cout <<(*it).month << " ";//硬要用就这样
			cout << it->month << " ";//如果有重载就可以这样写     这里原本应该是it->->month但是为了可读性，编译器特殊处理了一下
			++it;
		}
	}
	void listprint(const list<int>&k)
	{
		list<int>::const_iterator it = k.begin();
		while (it != k.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;
	}
	void  test3()
	{
		list<int> L;
		L.push_back(1);
		L.push_back(2);
		L.push_back(3);
		L.push_back(4);
		L.push_back(5);
		L.pop_back();
		list<int>L1 = L;
		listprint(L1);
	}
}

```