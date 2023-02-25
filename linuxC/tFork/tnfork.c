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
    // f(N) = 1 + f(N-1); f(1) = 2, f(0) = 1;
    // f(3) = 1 + f(2) = 1 + 1 + f(1) = 4
    // 每次创建的子进程个数 2^(n-1)
    // 一共创建的子进程数：2^(n) - 1 ,n为创建的次数
    // 总共进程总数 2^(n)
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
        }
        else
        {
            printf("other possible");
        }
    }
    
    return 0;
}