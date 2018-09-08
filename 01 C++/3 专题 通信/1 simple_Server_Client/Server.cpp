//#include "MultiSocket.h"
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")  

using namespace std;

#define  VOS_OK (0)
#define  VOS_ERR (1)


int main()
{
	WSADATA wsd = {0};
	int ret = 0;
	const int BUFF_SIZE = 64;
	char buf[BUFF_SIZE];
	char sendBuf[BUFF_SIZE];

	/* 判断版本 */
	if (WSAStartup(MAKEWORD(2,2), &wsd) != VOS_OK)
	{
		cout<< "WSASatrt up fail!\n" <<endl;
		return VOS_ERR;
	}

	/* 创建套接字 */
	SOCKET sSever = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sSever)
	{
		cout<< " sSever is invalid!\n "<<endl;
		WSACleanup();  // 如果不释放会怎么样
		return VOS_ERR;
	}

	
	/* 服务器套接字： 地址，内容 */
	SOCKADDR_IN addSock;
	addSock.sin_family = AF_INET;
	addSock.sin_port   = htons(4999);  
	addSock.sin_addr.s_addr = inet_addr("192.168.0.102");

	ret =  bind(sSever,  (LPSOCKADDR) &addSock, sizeof(SOCKADDR_IN));
	if (ret == SOCKET_ERROR)
	{
		cout<< " bind err!\n"<<endl; 
		closesocket(sSever);
		WSACleanup();
		return VOS_ERR;
	}

	//开始监听
	ret = listen(sSever, 1);
	if (ret == SOCKET_ERROR)
	{
		cout<< "listen err!\n"<<endl;
		closesocket(sSever);
		WSACleanup();
		return VOS_ERR;
	}

	sockaddr_in addrClient;
	
	int addrClintlen = sizeof(addrClient);
	SOCKET sClint = accept(sSever,(LPSOCKADDR)&addrClient, &addrClintlen);
	if (INVALID_SOCKET == sClint)
	{
		cout<< "accept err!\n"<<endl;
		closesocket(sSever);
		WSACleanup();
		return VOS_ERR;
	}

	while (true)
	{
		ZeroMemory(buf, BUFF_SIZE);   //memset(buf, 0, BUFF_SIZE)
		ret = recv(sClint, buf, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR)
		{
			cout<<"rcv err!\n"<<endl;
			WSACleanup();
			closesocket(sSever);
			closesocket(sClint);
			return VOS_ERR;
		}

		if(buf[0] == '0')
			break;

		cout<<"客户端发送的数据："<<buf<<endl;
		cout<<"向客户端发送的数据：";
		cin>>sendBuf;

		send(sClint,sendBuf,strlen(sendBuf),0);
	}

	closesocket(sClint);
	closesocket(sSever);
	WSACleanup();

	return 0;

}