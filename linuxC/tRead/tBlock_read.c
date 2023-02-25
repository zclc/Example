#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// 测试read 设备文件是否阻塞

int main(int argc, char const *argv[])
{
    // open file
    int fd = open("/dev/tty",O_RDWR);
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

    close(fd);   

    return 0;
}
// 阻塞和非阻塞不是read函数的属性，而是文件本身的属性
// socket 文件， pipe 文件 默认都是阻塞的
