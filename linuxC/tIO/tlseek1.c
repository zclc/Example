// 实现文件扩展
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    // open file
    int fd = open("test.log",O_RDWR | O_CREAT,0777);
    if (fd < 0)
    {
        perror("open error");
        return -1;
    }
    
    // parm1: fd
    // parm2: 受parm3控制，parm3 为  
    //          SEEK_SET 文件偏移量设置为parm2
    //          SEEK_CUR 文件偏移量设置为 当前偏移+parm2
    //          SEEK_END 文件偏移量设置为 文件长度+parm2
    // parm3:
    // 移动文件指针到第100个字节处
    int len = lseek(fd,100,SEEK_SET);
    
    // 进行一次写入操作
    write(fd,"h",1);

    // close file
    close(fd);

    return 0;
}