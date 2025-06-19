## string的简单模拟
```
namespace Zzc
{
	class string
	{
	private:
		char* str;//存储数据
		size_t size;//存储有效字符数目
		size_t capacity;//最大可存的有效字符数目/容量
		void expand(size_t newcapacity)
		{
			if (capacity >= newcapacity)return;//总是忘记这一步，写一个函数前一定要考虑一些特殊情况
			char* tmp = new char[newcapacity + 1];
			if (str)
			{
				strcpy(tmp, str);
				delete[]str;

			}
			str = tmp;
			capacity = newcapacity;

		}
	public:
		static const size_t npos = -1;
		//无参构造
		string() :str(nullptr), size(0), capacity(0) {}
		//有参构造
		string(const char* k_str) :str(nullptr), size(0), capacity(0) {
			if (k_str)
			{
				size_t len = strlen(k_str);
				str = new char[len + 1];
				capacity = len;
				strcpy(str, k_str);
			}
		}
		//拷贝构造
		string(const string& k_str) :str(nullptr), size(0), capacity(0) {
			if (k_str.str != str)
			{
				//size_t len = strlen(k_str.str);//这里其实就没有必要像上面的有参构造一样那么写了
				//str = new char[len + 1];
				//strcpy(str, k_str.str);
				//capacity = k_str.capacity;
				//size = k_str.size;
				size = k_str.size;
				capacity = k_str.capacity;
				str = new char[capacity + 1];
				strcpy(str, k_str.str);
			}
		}
		//析构函数
		~string()
		{
			delete[]str;
			str = NULL;
			size = capacity = 0;
		}
		//赋值运输符重载
		string& operator=(const string& k_str)
		{
			//if (k_str.str == str)return;//这种验证是不对的，因为存储数据相同但容量的大小本身也是一种属性，需要也也一样
			//delete[]str;
			//if (capacity < k_str.capacity)
			//{
			//	expand(k_str.capacity);//扩容一般在增操作需要，而且扩容有保留以前的数据，这样写肯定是错的。
			//}
			//strcpy(str, k_str.str);
			//size = k_str.size;
			//因为我们不能用*this==k_str
			if (this != &k_str)
			{
				delete[]str;
				str = nullptr;
				size = k_str.size;
				capacity = k_str.capacity;
				if (k_str.size)
				{
					str = new char[capacity + 1];
					strcpy(str, k_str.str);
				}
			}
			return *this;
		}
		// 基本访问函数
		//设为const意义：首先，本来就是只要访问，所以设为const不矛盾，还有一个重要原因
		//常函数可以被常对象调用也可以被普通对象调用
		//所以，如果有传参进到函数，即使参数是常对象，也可以调用常函数
		size_t getsize() const { return size; }
		size_t getcapacity() const { return capacity; }
		bool empty() const { return size == 0; }
		const char* c_str() const { return str ? str : ""; }
		//元素的访问：重载[]
		//为啥要同时写这两个，主要是我们要遵从常对象不可被修改原则
		//常对象返回的应该是不可访问的，普通成员对象返回的是可访问的
		char& operator[](size_t pos)
		{
			return str[pos];
		}
		const char& operator[](size_t pos)const
		{
			return str[pos];
		}
		// 迭代器
		char* begin() { return str; }
		const char* begin() const { return str; }
		char* end() { return str + size; }
		const char* end() const { return str + size; }
		// 修改操作
		void clear() {
			if (str) {
				str[0] = '\0';
			}
			size = 0;
		}
		//增操作
		void pushback(const char a)
		{
			if (capacity == size)
			{
				expand(capacity == 0 ? 2 : capacity * 2);
			}
			str[size++] = a;
			str[size] = '\0';

		}
		void append(const char* a)
		{/*
			size_t len = strlen(a);
			if (len + size > capacity)
			{
				expand(len + size);
			}
			for (int i = 0; i < size; i++)
			{
				str[size + i] = a[i];
			}
			size += len;
			str[size] = '\0';*///可以用strcpy()也有自动追加那个'\0'
			size_t len = strlen(a);
			if (len + size > capacity)
			{
				expand(len + size);
			}
			strcpy(str + size, a);
			size += len;
		}
		string& operator+=(const char k)
		{
			pushback(k);
			return *this;
		}
		string& operator+=(const char* k_str)
		{
			append(k_str);
			return *this;
		}
		string& operator+=(const string& k_str)
		{
			append(k_str.str);
			return *this;
		}
		void reserve(size_t newcapacity)
		{
			expand(newcapacity);
		}
		void resize(size_t newsize, char k = '\0')
		{
			if (newsize < size)
			{
				str[newsize] = '\0';
				size = newsize;
			}
			else
			{
				if (capacity < newsize)
				{
					expand(newsize);
				}
				for (int i = size; i < newsize; i++)
				{
					str[i] = k;
				}
				size = newsize;
				str[size] = '\0';//这一步总是容易忘
			}
		}
		bool operator==(const string& k_str)const
		{
			if (k_str.size != size)return false;
			//if (k_str.str != str)return false;比较字符串应该用的是strcmp
			//return true;
			return strcmp(k_str.str, str) == 0;
		}
		bool operator!=(const string& k_str)
		{
			return !(k_str == *this);//一开始这么写报错了，原因：没把operator==声明为常函数
		}
		string operator+(const string& a)//这里返回类型不能写成string&
		{
			return string(*this += a);
		}
	};

}
// 输入输出运算符
std::ostream& operator<<(std:: ostream& os, const Zzc::string& str) {//如果不写namespace ,在外面写string时就会指代不明
	os << (str.c_str() ? str.c_str() : "");
	return os;
}
std::istream& operator>>(std::istream& is, Zzc::string& str) {//Ai写的，这部分需要学习
	str.clear();
	char ch;

	// 跳过前导空白
	while (is.get(ch) && std::isspace(static_cast<unsigned char>(ch))) {}

	if (is) {
		str += ch;
		while (is.get(ch) && !std::isspace(static_cast<unsigned char>(ch))) {
			str += ch;
		}

		// 把空白字符放回流中
		if (is) {
			is.putback(ch);
		}
	}
	return is;
}
```