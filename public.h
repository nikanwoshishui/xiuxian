#ifndef PUBLIC_H
#define PUBLIC_H 1

/*服务端socket*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>

class socket_FWD
{
	public:
	int sock;		//监听的socket
	int sockfd;		//连接上来的socket

	~socket_FWD();		//析构函数
	socket_FWD();	//构造函数
	bool CJ(int port);	//创建socket
	bool LJ();			//连接
};

/*客户端socket*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

class socket_KHD
{
	public:
	int sockfd;		//用于通讯的socket

	~socket_KHD();		//析构函数
	socket_KHD();	//构造函数
	bool CJ(const char* IP, int port);	//创建socket
};

#endif
