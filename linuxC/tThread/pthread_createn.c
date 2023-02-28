#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

// 循环创建子进程，并且打印自己是第几个创建的子进程
/*
    以下程序全部打印5：
    原因：主线程和子线程共同访问i,
        创建的5个子进程没来得及获得i的值，i的值已经到5了
 */
// void* func(void* arg)
// {
//     int n = *(int*)arg;
//     printf("hello thread!,pid = %d, phtread id = %ld, i = %d\n",
//         getpid(),pthread_self(),n);
// }

// int main(int argc, char const *argv[])
// {
//     int arg = 99;
//     pthread_t thread;
//     int i;
//     for ( i = 0; i < 5; i++)
//     {
//         int ret = pthread_create(&thread,NULL,func,(void*)&i);
//         if (ret != 0)
//         {
//             printf("pthread_create error,%s\n",strerror(ret));
//             return -1;
//         }
//     }

//     printf("main thread!, pid = %d, phtread id = %lu\n",
//         getpid(),pthread_self());

//     sleep(2);
//     return 0;
// }
void* func(void* arg)
{
    int n = *(int*)arg;
    printf("hello thread!,pid = %d, phtread id = %ld, i = %d\n",
        getpid(),pthread_self(),n);
}

int main(int argc, char const *argv[])
{
    int arg = 99;
    pthread_t thread;
    int i;
    int a[5];
    for ( i = 0; i < 5; i++)
    {
        a[i] = i;
        int ret = pthread_create(&thread,NULL,func,(void*)&(a[i]));
        if (ret != 0)
        {
            printf("pthread_create error,%s\n",strerror(ret));
            return -1;
        }
    }

    printf("main thread!, pid = %d, phtread id = %lu\n",
        getpid(),pthread_self());

    sleep(2);
    return 0;
}