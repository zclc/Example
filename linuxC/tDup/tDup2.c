#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
    函数原型：int dup2(int oldfd, int newfd)
    函数描述：将newfd 指向oldfd 的文件，若newfd原来已经打开了一个文件
    则先关闭这个文件，然后指向oldfd 的文件
 */

int main(int argc, char const *argv[])
{
    int oldfd = open("a.txt",O_RDWR);
    if (oldfd < 0)
    {
        perror("open a error");
        return -1;
    }

    int newfd = open("b.txt",O_RDWR);
    if (newfd < 0)
    {
        perror("open b error");
        return -1;
    }

    printf("oldfd = %d,newfd = %d\n",oldfd,newfd);

    dup2(oldfd, newfd);

    printf("---- dup2 ----\n");
    printf("oldfd = %d,newfd = %d\n",oldfd,newfd);

    write(newfd,"hello world",11);
    lseek(newfd,0,SEEK_SET);

    char buf[1024];
    memset(buf,0,sizeof(buf));
    int n = read(newfd,buf,sizeof(buf));
    printf("read over: n = [%d],buf=[%s]\n",n,buf);

    close(oldfd);
    close(newfd);
    return 0;
}