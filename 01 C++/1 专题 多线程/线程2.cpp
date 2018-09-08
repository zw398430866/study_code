#include <stdio.h>
#include <Windows.h>
#include <process.h>


DWORD WINAPI ThreadFun(LPVOID pM)
{
	int* temp = (int*) pM;

	printf("子线程的线程ID号为：%d\n子线程输出Hello World : input number is %d\n", GetCurrentThreadId(), (*temp)++);
	return 0;
}

unsigned int _stdcall ThreadFun1(LPVOID pM)
{
	printf("子线程的线程ID号为：%d\t子线程输出Hello World\n", GetCurrentThreadId());
	return 0;
}

int main()
{
	int temp = 1000;

	printf("%d\n", sizeof(DWORD));

	HANDLE handle[5];
	for (int i = 0; i<5; i++)
	{
		handle[i] = CreateThread(NULL,0,ThreadFun, &temp, 0,NULL);
	}

	WaitForMultipleObjects(5, handle, true, INFINITE);
	return 0;
}