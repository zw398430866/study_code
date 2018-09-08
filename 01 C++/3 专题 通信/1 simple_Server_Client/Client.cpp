#include <WinSock2.h>
#include <iostream>

/*这个必须，否则无法编译过*/
#pragma comment(lib, "ws2_32.lib")  

#define  VOS_OK (0)
#define  VOS_ERR (1)
using namespace std;

int main()
{	
	const int BUFF_SIZE = 64;

	WSADATA wsd;
	SOCKET sHost;
	SOCKADDR_IN servAddr;

	char buf[BUFF_SIZE];
	char bufRecv[BUFF_SIZE];

	int ret;

	/* 判断版本 */
	if (WSAStartup(MAKEWORD(2,2), &wsd) != VOS_OK)
	{
		cout<< "WSASatrt up fail!\n" <<endl;
		return VOS_ERR;
	}


	/* 创建套接字 */
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		cout<< " socket invalid!\n "<<endl;
		WSACleanup();  // 如果不释放会怎么样
		return VOS_ERR;
	}


	/* 服务器套接字： 地址，内容 */
	servAddr.sin_family = AF_INET;
	servAddr.sin_port   = htons(4999);  
	servAddr.sin_addr.s_addr = inet_addr("192.168.0.102");

	ret = connect(sHost, (LPSOCKADDR) &servAddr, sizeof(servAddr));
	if (ret == SOCKET_ERROR)
	{
		cout<<"connect err!\n"<<endl;
		closesocket(sHost);
		WSACleanup();
	}

	while (true)
	{
		ZeroMemory(buf,BUFF_SIZE);
		cout<<"向服务器发送的数据：";
		cin>>buf;

		ret = send(sHost, buf, strlen(buf), 0);
		if (ret == SOCKET_ERROR)
		{
			cout<<"send err!\n"<<endl;
			closesocket(sHost);
			WSACleanup();
			return VOS_ERR;
		}

		ZeroMemory(bufRecv, BUFF_SIZE);
		recv(sHost, bufRecv, BUFF_SIZE, 0);
		cout<<"从服务器接收数据:" <<bufRecv<<endl;
	}

	closesocket(sHost);
	WSACleanup();
}