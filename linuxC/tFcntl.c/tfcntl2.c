#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// 使用fcntl 修改文件描述符的flag属性

int main(int argc, char const *argv[])
{
    int fd = open("a.txt",O_RDWR);
    if (fd < 0)
    {
        perror("open a error");
        return -1;
    }

    // 获得fd的flag属性
    int flags = fcntl(fd,F_GETFL,0);
    flags |= O_APPEND;
    fcntl(fd,F_SETFL,flags);

    write(fd,"hello world2\n",12);

    close(fd);

    return 0;
}