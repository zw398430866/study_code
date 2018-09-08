//定时器操作
#include "myTimer.h"
myThread::myThread(void) :  m_StopFlag(false), m_ThreadHandle(INVALID_HANDLE_VALUE)
{

}

myThread::~myThread(void)
{
	Stop();
}

void myThread::Start()
{
	//传this 指针  -- 是为了在threadProc指针中，对myThread类进行操作
	m_ThreadHandle = ::CreateThread(NULL, 0, threadProc, this, 0, NULL);
}

DWORD WINAPI myThread::threadProc(LPVOID p)
{
	myThread* pThread = (myThread*)p; 

	pThread->Run();

	if (pThread->m_ThreadHandle != INVALID_HANDLE_VALUE)
	{
		if (WAIT_ABANDONED != WaitForSingleObject(pThread->m_ThreadHandle, INFINITE))
		{
			CloseHandle(pThread->m_ThreadHandle);
		}
		pThread->m_ThreadHandle = INVALID_HANDLE_VALUE;
	}

	return 0;
}


void myThread::Stop()
{
	m_StopFlag = true;

	if (m_ThreadHandle != INVALID_HANDLE_VALUE)
	{
		if (WAIT_ABANDONED != WaitForSingleObject(m_ThreadHandle, INFINITE))
		{
			CloseHandle(m_ThreadHandle);
		}
		m_ThreadHandle = INVALID_HANDLE_VALUE;
	}
}

bool myThread::IsStop()
{
	return m_StopFlag;
}
/***********************************************************************************/

myTimer::myTimer(void) : m_InterVal(0), m_HandleFuc(0), m_HandleParam(0)
{
}

myTimer::~myTimer(void)
{
}

void myTimer::RegisteFunc(TimeHandle handle, void *p)
{
	m_HandleFuc = handle;
	m_HandleParam = p;
}


void myTimer::SetInterVal(int millisecond)
{
	m_InterVal = millisecond;
}

void myTimer::Run()
{
	unsigned long m_tickNow = ::GetTickCount();
	unsigned long m_tickLast = m_tickNow;

	while( !IsStop() )
	{
		m_tickNow = ::GetTickCount();
		if ( (m_tickNow - m_tickLast) > m_InterVal )
		{
			//回调函数是地址
			(*m_HandleFuc)(m_HandleParam);
			m_tickLast = ::GetTickCount();
		}
		::Sleep(1);
	}
}

void myTimer::Cancel()
{
	Stop();
}