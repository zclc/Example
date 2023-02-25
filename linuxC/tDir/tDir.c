#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

// 测试目录操作函数：opendir readdir closedir

int main(int argc, char const *argv[])
{
    // 打开目录
    DIR *pDir = opendir(argv[1]);
    if (pDir == NULL)
    {
        perror("opendir error:");
        return -1;
    }
    

    // 循环读取目录项（目录里的内容）
    struct dirent* pDent = NULL;
    while ( (pDent = readdir(pDir)) != NULL)
    {
        printf("[]: %s \n",pDent->d_name);

        // 判断文件类型
        switch (pDent->d_type)
        {
            case DT_CHR : printf("This is a character device.\n"); break;     

            case DT_DIR : printf("This is a directory.\n"); break;     

            case DT_LNK :  printf(" This is a symbolic link.\n");  break;   

            case DT_REG  : printf("This is a regular file.\n");   break; 

            default:  printf("The file type could not be determined.\n"); 
        }


    }
    

    // 关闭目录

    closedir(pDir);

    return 0;
}