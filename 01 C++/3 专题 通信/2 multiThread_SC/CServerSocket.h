
#ifndef  _C_SSERVER_SOCKET_
#define _C_SSERVER_SOCKET_

#include <WinSock2.h>
#include <iostream>
#include <stdio.h>
#include <string>

#pragma  comment(lib, "ws2_32.lib")

using namespace std;

#define  BUFF_SIZE  128

class CServerSocket{
public:
	CServerSocket();
	~CServerSocket();

	CServerSocket(int port, string addrIp);
	
	void CServerSetPort(int port);
	void CServerSetAddrIp(string addrIp);
	void CServerSetPortAndIp(int port,string addrIp);

	int start();  /* server����������Ψһ��� */
private:
	int m_Accept();
    //DWORD WINAPI CServerSocket::m_thread_Acception(LPVOID pVoid);  /* ����һ��accept ClientSocket���ڽ��� */

	int m_Port;
	string m_addrIp;

	SOCKET m_ServerSocket;
	//SOCKET m_ClientSocket;
};


#endif
