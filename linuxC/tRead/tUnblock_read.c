#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// 验证read函数读普通文件是否阻塞

int main(int argc, char const *argv[])
{
    // open file
    int fd = open(argv[1],O_RDWR);
    if (fd < 0)
    {
        perror("open error");
        return -1;
    }
    
    // read file
    char buf[1024];
    memset(buf,0x00,sizeof(buf));
    int n = read(fd,buf,sizeof(buf));
    printf("FIRST: n == [%d], buf == [%s]\n",n,buf);

    // 再次读文件，验证read函数是否阻塞
    memset(buf,0x00,sizeof(buf));
    n = read(fd,buf,sizeof(buf));
    printf("SECOND: n == [%d], buf == [%s]\n",n,buf);

    // 通过读普通文件测试可知：read函数在读完文件内容之后，再次read则read函数会立刻返回
    // read函数读普通文件是非阻塞的
    close(fd);
    return 0;
}