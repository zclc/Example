#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// 使用dup2函数实现文件重定向
int main(int argc, char const *argv[])
{
    int fd = open(argv[1],O_RDWR | O_CREAT,0777);
    if (fd < 0)
    {
        perror("open error");
        return -1;
    }
    dup2(fd,STDOUT_FILENO);
    // STDOUT_FILENO 为 0 指向/dev/tty

    printf("dup2 hello!\n");

    return 0;
}