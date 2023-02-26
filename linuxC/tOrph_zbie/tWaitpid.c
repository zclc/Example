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
        // pid_t wpid = waitpid(-1,&status,0); // 等于 wait
        pid_t wpid;
        // an:wpid = waitpid(-1,&status,WNOHANG);
        // printf("wpid = %d\n",wpid);
        // if (wpid > 0)
        // {
        //     if (WIFEXITED(status)) // man 2 wait 查询使用
        //     {
        //         printf("child noraml exit, status == [%d]\n",
        //             WEXITSTATUS(status));
        //     }
        //     else
        //     {
        //         printf("child unnoraml exit, status == [%d]\n",
        //             WEXITSTATUS(status));
        //     }            
        // }
        // else if (wpid == 0)
        // {
        //     printf("child is living\n");
        //     goto an;
        // }
        // else if (wpid == -1)
        // {
        //     printf("no child is living,wpid == [%d]\n",wpid);
        // }    
        while (1)
        {
            wpid = waitpid(-1,&status,WNOHANG);
            if (wpid > 0)
            {
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
            else if (wpid == 0)
            {
                
            }
            else if (wpid == -1)
            {
                printf("no child is living,wpid == [%d]\n",wpid);
                break;
            }  
        }
        

    }
    else if (pid == 0)
    {
        printf("child pid : %d, fpid = %d\n",getpid(),getppid());
        sleep(2);
    }
    
    return 0;
}