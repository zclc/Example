#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

// ps -Lf pid 查看进程号为pid下的线程
void* func(void* arg)
{
    int n = *(int*)arg;
    printf("hello thread!,pid = %d, phtread id = %ld, i = %d\n",
        getpid(),pthread_self(),n);
    sleep(15);
    pthread_exit(NULL);
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

    sleep(20);
    return 0;
}