#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// fork 子进程测试

int main(int argc, char const *argv[])
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
        //sleep(2);
    }
    else if (pid == 0)
    {
        printf("child: pid == %d, fpid == %d\n",getpid(),getppid());
        sleep(2);  // 子进程后退出
    }
    else
    {
        printf("other possible");
    }

    printf("after fork, my pid == %d, my fpid == %d\n",getpid(),getppid());

    return 0;
}