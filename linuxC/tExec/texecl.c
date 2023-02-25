#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// execl 函数测试

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
        
    }
    else if (pid == 0)
    {
        execl("/bin/ls","ls","-l",NULL);
        perror("execl error");// execl执行成功，后面都不执行
        printf("----"); 
    }
    else
    {
        printf("other possible");
    }

    return 0;
}