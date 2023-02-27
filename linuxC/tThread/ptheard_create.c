#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

void* func(void* arg)
{
    int n = *(int*)arg;
    printf("hello thread!,pid = %d, phtread id = %lu\n",
        getpid(),pthread_self());
    printf("n = %d \n",n);
}

int main(int argc, char const *argv[])
{
    int arg = 99;
    pthread_t thread;
    int ret = pthread_create(&thread,NULL,func,(void*)&arg);
    if (ret != 0)
    {
        printf("pthread_create error,%s\n",strerror(ret));
        return -1;
    }
    printf("main thread!, pid = %d, phtread id = %lu\n",
        getpid(),pthread_self());

    sleep(2);
    return 0;
}
