#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// 循环创建n个子进程
int main(int argc, char const *argv[])
{
    int i = 0;
    for ( i = 0; i < 3; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork error");
            return -1;
        }
        else if (pid > 0)
        {
            printf("father : pid == %d, fpid == %d\n",getpid(),getppid());
        }
        else if (pid == 0)
        {
            printf("child: pid == %d, fpid == %d\n",getpid(),getppid());
            break; // 子进程都是兄弟关系,只有3个子进程
        }
        else
        {
            printf("other possible");
        }
    }

    if (i == 0)
    {
        printf("[i == %d] : pid == %d\n",i,getpid());
    }
    if (i == 1)
    {
        printf("[i == %d] : pid == %d\n",i,getpid());
    }
    if (i == 2)
    {
        printf("[i == %d] : pid == %d\n",i,getpid());
    }

    return 0;
}