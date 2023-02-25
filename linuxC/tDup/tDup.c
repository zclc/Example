#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// dup 复制文件描述符
int main(int argc, char const *argv[])
{
    /* 调用dup函数之后，newfd 和 fd都指向了同一个文件
    内核会在维护一个文件引用计数为2，当close一个文件描述符
    后，这个引用计数减一，当引用计数为0时，文件才会被真正关闭
    */
    int fd = open("a.txt",O_RDWR);
    if (fd < 0)
    {
        perror("open error");
        return -1;
    }
    printf("[fd] = %d\n",fd);

    write(fd,"hello world",11);

    int newfd = dup(fd);
    printf("[newfd] = %d\n",newfd);

    char buf[1024];
    memset(buf,0,sizeof(buf));
    lseek(fd,0,SEEK_SET);
    int n = read(newfd,buf,sizeof(buf));
    printf("read over: n = [%d],buf=[%s]\n",n,buf);

    close(fd);
    close(newfd);
    return 0;
}