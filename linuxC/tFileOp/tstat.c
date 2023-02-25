#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define S_IFMT  00170000
#define S_IFSOCK 0140000
#define S_IFLNK	 0120000
#define S_IFREG  0100000
#define S_IFBLK  0060000
#define S_IFDIR  0040000
#define S_IFCHR  0020000
#define S_IFIFO  0010000
#define S_ISUID  0004000
#define S_ISGID  0002000
#define S_ISVTX  0001000
// 测试st_mode用法，判断文件类型
// 对于软链接文件 lstat获取的是链接文件本身的属性，
// stat输出的文件类型为链接文件指向的文件类型 

int main(int argc, char const *argv[])
{
    struct stat st;
    stat(argv[1],&st);
    printf("    file size = %lu\n \
    ino = %lu\n \
    last change = %ld\n",
        st.st_size,
        st.st_ino,
        st.st_mtime);

    // 判断文件类型
    switch (S_IFMT & st.st_mode) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }

    return 0;
}