#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

// 使用pipe 实现父子进程间传递数据
/*
    1 父进程创建pipe
    2 父进程调用fork函数创建子进程
    3 父进程关闭一端
    4 子进程关闭一端
    5 父进程和子进程分别执行read或write操作
*/

int main(int argc, char const *argv[])
{
    int fd[2];
    int ret = pipe(fd);
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return -1;
    }
    else if (pid > 0) // 父进程
    {
        // 父进程写，关闭管道读端
        close(fd[0]);
        sleep(2);
        write(fd[1],"hello world",11);
        wait(NULL);
    }
    else if (pid == 0)
    {
        // 子进程读，关闭管道写端
        close(fd[1]);
        char buf[1024];
        memset(buf,0,sizeof(buf));
        read(fd[0],buf,sizeof(buf));
        printf("buf = %s\n",buf);
    }
    else 
    {
        printf("impossible \n");
        return -1;
    }

    return 0;
}