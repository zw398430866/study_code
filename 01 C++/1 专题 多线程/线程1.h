#pragma once

#ifndef _MY_TIMER_H_
#define  _MY_TIMER_H_

#include <Windows.h>



class myThread
{
public:
	myThread();
	virtual ~myThread();   //

	/* 启动一个定时进程 */
	void Start();

	/* 停止该定时进程 */
	void Stop();

	/* 在该定时进程中的定时处理 */
	virtual void Run() = 0;

	/* 封装一个标识，继承的类可以不用对变量进行操作 */
	bool IsStop();


protected:
	/* 线程处理函数 */
	static DWORD WINAPI threadProc(LPVOID p);

private:
	/* CreateThread成功会保存一个handle，如果线程结束，用CloseHandle结束 */
	HANDLE m_ThreadHandle; 
	bool m_StopFlag;
	
};


class myTimer : public myThread
{
	typedef  void(CALLBACK *TimeCallbackFunc)(void *p);
	typedef  TimeCallbackFunc TimeHandle;
public:
	myTimer(void);
	~myTimer(void);

	void RegisteFunc(TimeHandle handle, void *p);

	void SetInterVal(int millisecond);
	
	/* 通过打点计时，超时即处理回调函数 */
	void Run();

	void Cancel();

private:
	unsigned int      m_InterVal;
	TimeCallbackFunc  m_HandleFuc;
	void*             m_HandleParam;
};


#endif