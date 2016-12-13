#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<sys/types.h>
#include <fcntl.h>
#include<sys/wait.h>
#include"make_log.h"


int main()
{
	int ret = 0;
	char buf[1024]={0};
	pid_t pid=0;
	int pfd[2];
	ret = pipe(pfd);
	if(ret==-1)
	{
		printf("func pipe() err:%d\n",ret);
		return ret;
	}
	pid=fork();
	
	//子进程
	if(pid==0)
	{
		//关闭读端
		close(pfd[0]);
		dup2(pfd[1],STDOUT_FILENO);
		execlp("fdfs_upload_file","fdfs_upload_file","/etc/fdfs/client.conf","/home/itheima/aaa.txt",NULL);
	}
	else if(pid>0)
	{
		//关闭写端
		close(pfd[1]);
		read(pfd[0],buf,1024);
		LOG("lcj", "1", buf);
		wait(NULL);
	}
	
	return 0;
}
