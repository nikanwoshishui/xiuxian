#include"public.h"

//socket服务端封装
socket_FWD::~socket_FWD()
{
	close(sock);	close(sockfd);
}

socket_FWD::socket_FWD()
{
	sock = 0;	sockfd = 0;
}

bool socket_FWD::CJ(int port)
{
if((sock = socket(AF_INET,SOCK_STREAM,0)) <= 0)
{
	printf("socket错误！\n");       return false;
}

	sockaddr_in addr_in;
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(port); 
	addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	//addr_in.sin_addr.s_addr_in = inet_addr("192.168.226.128");

	if(bind(sock,(struct sockaddr *)&addr_in, sizeof(addr_in)) != 0)
	{
		printf("bind错误\n");   return false;
	}
	if(listen(sock, 5) != 0)
	{
		printf("listen错误\n"); close(sock);    return false;
	}

	return true;

}

bool socket_FWD::LJ()
{
	sockaddr_in addr;
	memset(&addr,0,sizeof(struct sockaddr_in));
	int add = sizeof(struct sockaddr_in);

	if((sockfd = accept(sock, (struct sockaddr *)&addr, (socklen_t *)&add)) == -1)
	{
		printf("accpet错误\n"); return false;
	}
        printf("客户端《%s》以连接\n", inet_ntoa(addr.sin_addr));
        return true;
}

//socket客户端封装
socket_KHD::~socket_KHD()
{
        close(sockfd);
}

socket_KHD::socket_KHD()
{
        sockfd = 0;
}

bool socket_KHD::CJ(const char* IP, int port)
{
        if((sockfd = socket(AF_INET,SOCK_STREAM,0)) <= 0)
        {
                printf("socket错误\n"); return false;
        }

        sockaddr_in addr_in;
        hostent* h;

        if((h = gethostbyname(IP)) == 0)
        {
                printf("gethostbyname错误\n");  close(sockfd);  return false;
        }

        memset(&addr_in,0,sizeof(addr_in));

        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(port);

        memcpy(&addr_in.sin_addr, h->h_addr, h->h_length);

        if(connect(sockfd, (struct sockaddr *)&addr_in, sizeof(addr_in)) < 0)
        {
                printf("connect错误\n");        close(sockfd);  return false;
        }

        return true;
}

