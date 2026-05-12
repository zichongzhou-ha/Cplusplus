
#ifdef 装饰器模式
#include<iostream>
using namespace std;
//代理模式：访问权限；装饰器：增加功能
class Car
{
public:
	virtual void show() = 0;
};
class Bmw :public Car
{
public:
	void show()
	{
		cout << "这是一辆宝马汽车，配置有：基类配置";
	}
};
class Audi :public Car
{
public:
	void show()
	{
		cout << "这是一辆奥迪汽车，配置有：基类配置";
	}
};
class Benz :public Car
{
public:
	void show()
	{
		cout << "这是一辆奔驰汽车，配置有：基类配置";
	}
};
//装饰器的基类
class CarDecorator :public Car
{
public:
	CarDecorator(Car* p) :pCar(p)
	{

	}
	void show()
	{
		pCar->show();
	}
protected:
	Car* pCar;
};
class ConcreteDecorator01 :public CarDecorator
{
public:
	ConcreteDecorator01(Car* p) :CarDecorator(p)
	{

	}
	void show()
	{
		pCar->show();
		cout << ",定速巡航";
	}
};
class ConcreteDecorator02 :public CarDecorator
{
public:
	ConcreteDecorator02(Car* p) :CarDecorator(p)
	{

	}
	void show()
	{
		pCar->show();
		cout << ",自动刹车";
	}
};
class ConcreteDecorator03 :public CarDecorator
{
public:
	ConcreteDecorator03(Car* p) :CarDecorator(p)
	{

	}
	void show()
	{
		pCar->show();
		cout << ",车道偏离";
	}
};
int main()
{
	Car* p1 = new ConcreteDecorator01(new Bmw());
	p1 = new ConcreteDecorator02(p1);
	p1->show();
	cout << endl;
	Car* p2 = new ConcreteDecorator02(new Audi());
	p2->show();
	cout << endl;
	Car* p3 = new ConcreteDecorator03(new Benz());
	p3->show();
	cout << endl;
	return 0;
}
#endif // 装饰器模式

