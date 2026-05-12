/* 
简单工厂
把对象的创建分装在一个接口函数里，通过传入不同的标识，返回创建的对象
客户不用自己new对象，不用了解对象创建的详细过程

提供创建对象实例的接口函数不闭合，不能对修改关闭

工厂方法
提供了一个纯虚函数(创建产品),定义派生类(具体产品的工厂)负责创建对应的产品，可以做到不同2的产品在不同的工厂
里面创建，能够对现有的工厂以及产品修改关闭

但是，实际上很多产品间是有关系和联系的，属于一个产品簇，不应该放在不同的工厂里面创建，一是不符合逻辑
二是工厂类太多不好维护

抽象工厂
把有关联关系的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里面，
派生类(具体产品的工厂)应该负责创建该产品簇里面所有的产品


*/

#include<iostream>
#include<string>
#include<memory>
using  namespace std;

class Car
{
public:
	Car(string name)
		:_name(name)
	{

	}
	virtual void show() = 0;
protected:
	string _name;
};
class Bmw:public Car
{
public:
	Bmw(string name)
		:Car(name)
	{}
	void show()
	{
		cout << "获取了一辆宝马：" << _name << endl;
	}
};
class Audi :public Car
{
public:
	Audi(string name)
		:Car(name)
	{}
	void show()
	{
		cout << "获取了一辆奥迪：" << _name << endl;
	}
};
//#define 简单工厂//:如果要想要有新的车辆，就必须改工厂里的接口，不符合开闭原则
#ifdef 简单工厂
enum CarType
{
	BMW, AUDI
};
class SimpleFactory
{
public:
	Car* createrCar(CarType ct)
	{
		switch (ct)
		{
		case BMW:
			return new Bmw("X1");
		case AUDI:
			return new Audi("X2");
		default:
			cerr << "传入参数错误" << endl;
		}
		return nullptr;
	}
};
int main()
{
	//cout << "hello world" << endl;
	//Car* p1 = new Bmw("X1");
	//Car* p2 = new Audi("X2");
	//p1->show();
	//p2->show();

	//SimpleFactory* factory = new SimpleFactory();
	unique_ptr<SimpleFactory>factory(new SimpleFactory());
	unique_ptr<Car> p1(factory->createrCar(BMW));
	unique_ptr<Car>p2(factory->createrCar(AUDI));
	//Car* p2 = factory->createrCar(AUDI);
	p1->show();
	p2->show();
	//delete p1;
	//delete p2;
	//delete factory;
	return 0;
}
#endif // !简单工程
//#define 工厂方法//如果想要有新的车辆，直接多一个新的工厂就可以了，不用改接口
#ifdef 工厂方法
class Factory
{
public:
	virtual Car* createCar(string name) = 0;
};
class BMWFactory :public Factory
{
public:
	Car* createCar(string name)
	{
		return new Bmw(name);
	}
};
class AUDIFactory :public Factory
{
public:
	Car* createCar(string name)
	{
		return new Audi(name);
	}
};
int main()
{
	unique_ptr<Factory>bmwfty(new BMWFactory());
	unique_ptr<Factory>audifty(new AUDIFactory());
	unique_ptr<Car>p1(bmwfty->createCar("X1"));
	unique_ptr<Car>p2(audifty->createCar("X2"));
	p1->show();
	p2->show();

}
#endif // 工厂方法

//#define 抽象工厂
#ifdef 抽象工厂//对有一组关联关系的产品簇提供产品对象的统一创建
class Light
{
public:
	virtual void show() = 0;
};
class BmwLight :public Light
{
public:
	void show()
	{
		cout << "BMW light" << endl;
	}
};
class AudiLight :public Light
{
public:
	void show()
	{
		cout << "AUDI light" << endl;
	}
};
class AbstractFactory
{
public:
	virtual Car* createrCar(string name) = 0;
	virtual Light* createrCarLight() = 0;

};
class BMWFactory :public AbstractFactory
{
public:
	Car* createrCar(string name)
	{
		return new Bmw(name);
	}
	Light* createrCarLight()
	{
		return new BmwLight();
	}
};
class AUDIFactory :public AbstractFactory
{
public:
	Car* createrCar(string name)
	{
		return new Audi(name);
	}
	Light* createrCarLight()
	{
		return new AudiLight();
	}
};
int main()
{
	unique_ptr<AbstractFactory>bmwfty(new BMWFactory());
	unique_ptr<AbstractFactory>audifty(new AUDIFactory());
	unique_ptr<Car>p1(bmwfty->createrCar("X1"));
	unique_ptr<Car>p2(audifty->createrCar("X2"));
	unique_ptr<Light>p3(bmwfty->createrCarLight());
	unique_ptr<Light>p4(audifty->createrCarLight());
	p1->show();
	p2->show();
	p3->show();
	p4->show();
}
#endif // !抽象工厂



