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
    
    // write file
    write(fd,"hello world",strlen("hello world"));

    // lseek file pointer
    off_t  lret = lseek(fd,0,SEEK_SET);

    // read file
    char buf[1024];
    memset(buf,0x00,sizeof(buf));

    int ret = read(fd,buf,sizeof(buf));
    printf("ret == [%d], buf = [%s]\n",ret,buf);

    // close file
    close(fd);

    return 0;
}