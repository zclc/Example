#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysmacros.h>

// 测试st_mode用法，判断文件类型
// 对于链接文件 lstat输出的文件类型为链接文件，stat输出的文件类型为链接文件指向的文件类型 

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