#include "CServerSocket.h"
#include <stdio.h>


#define  VOS_OK  (0)
#define  VOS_ERR (1)


CServerSocket::CServerSocket() : m_Port(0), m_addrIp("127.0.0.1"){}

CServerSocket::~CServerSocket(){}

CServerSocket::CServerSocket(int port, string addrIp){
	m_Port   = port;
	m_addrIp = addrIp;
}

void CServerSocket::CServerSetPort(int port){
	m_Port   = port;
}

void CServerSocket::CServerSetAddrIp(string addrIp){
	m_addrIp = addrIp;
}

void CServerSocket::CServerSetPortAndIp(int port,string addrIp){
	m_Port   = port;
	m_addrIp = addrIp;
}


DWORD WINAPI thread_Acception(LPVOID pVoid)
{
    SOCKET *pclient_socket = (SOCKET*) pVoid;

    int ret = 0;
	char m_Buf[BUFF_SIZE];  /* 保存的客户端发送数据 */
    
    while (true)
    {
        ZeroMemory(m_Buf, BUFF_SIZE);
        ret = recv(*pclient_socket, m_Buf, BUFF_SIZE, 0);
        if (ret == SOCKET_ERROR)
        {
            cout<<"rcv err!\n"<<endl;  
            closesocket(*pclient_socket);
            free(pclient_socket);
            return VOS_ERR;
        }

        cout<<m_Buf<<endl;
    }

    closesocket(*pclient_socket);
    free(pclient_socket);
    
    return 0;
}

int CServerSocket::m_Accept()
{
	int ret = 0;

	WSADATA wsd;

	if (VOS_OK != WSAStartup(MAKEWORD(2,2),&wsd)){
		printf("CServerSocket check version err!\n");
		return VOS_ERR;
	}

	m_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(INVALID_SOCKET == m_ServerSocket){
		printf("CServerSocket create socket err!\n");
		WSACleanup();	
		return VOS_ERR;
	}

	SOCKADDR_IN addSock;
	addSock.sin_family = AF_INET;
	addSock.sin_port   = htons(m_Port);  
	addSock.sin_addr.s_addr = inet_addr(m_addrIp.c_str());

	ret = bind(m_ServerSocket, (LPSOCKADDR) &addSock, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == ret){
		printf("CServerSocket bind socket err!\n");
		WSACleanup();
		closesocket(m_ServerSocket);
		return VOS_ERR;
	}

	ret = listen(m_ServerSocket, 1000);
	if (SOCKET_ERROR == ret)
	{
		printf("CServerSocket m_Accept proc listen socket err!\n");
		WSACleanup();
		closesocket(m_ServerSocket);
		return VOS_ERR;
	}

    printf("server is ready\n");    

    while(true)
    {
        sockaddr_in addrClient;
        int addrClintlen = sizeof(addrClient);

        SOCKET *pclient_socket = (SOCKET*) malloc(sizeof(SOCKET));

        *pclient_socket = accept(m_ServerSocket,(LPSOCKADDR)&addrClient, &addrClintlen);
        printf("server rcv a socket %u\n", *pclient_socket);

        if (INVALID_SOCKET == *pclient_socket)
        {
            printf("CServerSocket m_Accept proc accept socket err!\n");
            closesocket(*pclient_socket);
            free(pclient_socket);
            continue;;
        }

        CreateThread(NULL, 0, &thread_Acception, pclient_socket, 0, NULL);
    }

	WSACleanup();
	closesocket(m_ServerSocket);
	return VOS_OK;
}

/*  socket启动唯一入口 */
int CServerSocket::start(){
	(void)m_Accept();
	return VOS_OK;
}



