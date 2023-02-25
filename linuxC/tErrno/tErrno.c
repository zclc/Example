#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


// 测试perror 和 errno的用法
int main(int argc, char const *argv[])
{
    // open file
    int fd  = open("argv[1]",O_RDWR);
    if (fd < 0)
    {
        perror("open error"); // open error： errno 对应的错误原因 \n
        return -1;
    }
    
    // read file
    char buf[1024];
    memset(buf,0x00,sizeof(buf));

    int ret = read(fd,buf,sizeof(buf));
    printf("ret == [%d], buf = [%s]\n",ret,buf);

    // close file
    close(fd);

    return 0;
}