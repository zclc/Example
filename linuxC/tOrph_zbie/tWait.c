#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

// 父进程调用wait函数完成对子进程的回收

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
        
        int status;
        pid_t wpid = wait(&status);
        printf("wpid = %d\n",wpid);
        if (WIFEXITED(status)) // man 2 wait 查询使用
        {
            printf("child noraml exit, status == [%d]\n",
                WEXITSTATUS(status));
        }
        else
        {
            printf("child unnoraml exit, status == [%d]\n",
                WEXITSTATUS(status));
        }
    }
    else if (pid == 0)
    {
        printf("child pid : %d, fpid = %d\n",getpid(),getppid());
        sleep(5);
    }
    
    return 0;
}