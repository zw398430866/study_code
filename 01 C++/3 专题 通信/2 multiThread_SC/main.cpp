#include "CServerSocket.h"
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")  

using namespace std;

#define  VOS_OK (0)
#define  VOS_ERR (1)


int main()
{
    CServerSocket my_socket(4999, "192.168.0.103");
    my_socket.start();

}