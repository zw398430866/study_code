#include <stdio.h>
#include <iostream>
#include <Windows.h>

using namespace std;

typedef void(CALLBACK *printComm)(void *p);

class Cmain
{
public:
    void doRegist(printComm handle, void *para)
	{
        m_handle = handle;
        m_para   = para;
    }

    void doPrint()
    {
        (*m_handle)(m_para);
    }
private:
    printComm m_handle;
    void *m_para;
};

void CALLBACK my_print(void *p)
{
	int *pint = (int*)p;
    printf("my_print %d\n", *pint);
}

void CALLBACK getSum(void *p)
{
    double *pdouble = (double*)p;
    *pdouble += 1;
    printf("my_print %f\n", *pdouble);
}

int main()
{
    Cmain myclass;
	double i = 1;
    myclass.doRegist(getSum, &i);
    myclass.doPrint();
}