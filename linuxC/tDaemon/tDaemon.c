#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

// 创建守护进程，每隔两秒种获取一次系统时间，并将这个时间写入磁盘
void myfunc(int signo)
{
    int fd = open("daemon.log",O_RDWR | O_CREAT | O_APPEND,0755);
    if (fd < 0)
    {
        return;
    }
    
    // 获取当前系统时间
    time_t t;
    time(&t);
    char* p = ctime(&t);
    write(fd,p,strlen(p));
    
    close(fd);

    return;
}

int main(int argc, char const *argv[])
{
    // 创建子进程
    pid_t pid = fork();
	if(pid<0 || pid>0)
	{
		exit(1);
	}
    
    // 子进程调用setsid 函数创建会话
    setsid();
    
    // 改变当前的工作目录
    chdir("/home/zcl/log");

    // 改变文件掩码
    umask(0000); // 不限制文件的操作权限

    // 关闭标准输入，输出和错误文件描述符
    close(STDIN_FILENO);
    close(STDERR_FILENO);
    close(STDOUT_FILENO);

    // // 核心操作
    // // 注册信号处理函数
    struct sigaction act;
    act.sa_handler = myfunc;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);

    // struct itimerval tm;
    // tm.it_interval.tv_sec = 2;
    // tm.it_interval.tv_usec = 0;
    // tm.it_value.tv_sec = 3;
    // tm.it_interval.tv_usec = 0;
    // setitimer(ITIMER_REAL, &tm, NULL);



    while(1)
    {
        sleep(1);
    }
    return 0;
}
