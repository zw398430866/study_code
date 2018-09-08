#include <stdio.h>
#include "CTimer.h"



class Object
{
public:
	virtual void Operation()
	{
		printf("Object print\n");
	};
};

class decorator : Object
{
public:
	Object *p_m_object;

	void SetComponet(Object *pObj){
		p_m_object = pObj;
	}

	void Operation(){
		p_m_object->Operation();
	}
private:
	int m_decorator_num;
};

class CompDecoratorA : public decorator
{
public:
    void Operation(){
		decorator::Operation();
		printf("CompDecoratorA print\n");
	}
};

class CompDecoratorB : public decorator
{
public:
	void  Operation(){
		decorator::Operation();
		printf("CompDecoratorB print\n");
	}
};


class BaseTemplator
{
public:
	virtual void myPrintf()
	{
		printf("BaseTemplator print\n");
	}
};

class tempA : public BaseTemplator
{
public:
	void myPrintf()
	{
		printf("tempA print\n");
	}
};

int main()
{	
	//多态和virtual的关系
	BaseTemplator*  t = new tempA();
	t->myPrintf();

	//装饰者模式
	Object dbase;
	CompDecoratorA ca;
	CompDecoratorA cb;

	ca.SetComponet((Object*)&dbase);
	cb.SetComponet((Object*)&ca);

	cb.Operation();
}