#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// 测试孤儿进程
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
        printf("father: childpid = %d, pid = %d, fpid = %d\n",
         pid,getpid(),getppid());
        sleep(1);
    }
    else if (pid == 0)
    {
        printf("child pid : %d, fpid = %d\n",getpid(),getppid());
        sleep(10);
        printf("child pid : %d, fpid = %d\n",getpid(),getppid());
    }
    
    return 0;
}