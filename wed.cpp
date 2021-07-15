#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include"public.h"
#include<signal.h>

#define MAX 100
socket_FWD fwd;
void EXIT(int sig);

int main()
{
	for(int i=0; i<100; i++)
	{
		signal(i,SIG_IGN);
	}

	signal(SIGINT,EXIT);	signal(SIGTERM,EXIT);

	if(fwd.CJ(5051) == false)	return 0;

	int fd = epoll_create(1);			//创建描述符

	struct epoll_event ev;
	ev.data.fd = fwd.sock;
	ev.events = EPOLLIN;
	
	epoll_ctl(fd,EPOLL_CTL_ADD,fwd.sock,&ev);		//把监听的sock加入句柄中
	struct epoll_event epoll_fd[MAX];

	while(1)
	{
		int sum = epoll_wait(fd,epoll_fd,MAX,-1);
		int i = 0;

		while(i< sum)
		{
			if(epoll_fd[i].data.fd == fwd.sock)
			{
				int sockfd = 0;	struct sockaddr_in add;
				socklen_t len = sizeof(add);
				if((sockfd = accept(fwd.sock,(sockaddr*)&add,&len)) == 0)
				{
					printf("accept失败\n");		return -1;
				}

				memset(&ev,0,sizeof(epoll_event));
				//ev.data.fd = sockfd;
				//ev.events = EPOLLIN;
				//把新的sock添加到数组中
				//epoll_ctl(fd,EPOLL_CTL_ADD,sockfd,&ev);
				//printf("客户端< %d >以连接\n", sockfd);

				FILE *fp;	char buf[1024];

				memset(buf,0,sizeof(buf));
				strcat(buf,"HTTP/1.1 200 ok\r\n");
				strcat(buf,"Connection: close\r\n");
				strcat(buf,"\r\n");

				if((fp = fopen("wed2.txt","r")) == 0)
				{
					printf("文件打开失败\n");	return -1;
				}
\
				char buff[102];
				memset(buff,0,sizeof(buff));

				while(fgets(buff,sizeof(buff),fp))	//读取整行的数据
				{
					strcat(buf,buff);	//printf("%s\n", buff);
					memset(buff,0,sizeof(buff));
				}
				fclose(fp);

				send(sockfd,&buf,strlen(buf),0);
				close(sockfd);

				//ev.data.fd = epoll_fd[i].data.fd;
				//printf("以关闭连接！\n");
				//发送完毕后删除客户端
				//epoll_ctl(fd,EPOLL_CTL_DEL,epoll_fd[i].data.fd,&ev);
			}
			i++;
		}
		
	}

	return 0;
}

void EXIT(int sig)
{
	close(fwd.sock);
	printf("释放资源完毕\n");
	exit(0);
}
