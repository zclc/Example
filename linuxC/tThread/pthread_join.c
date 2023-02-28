#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

int g_var = 9;
void* func(void* arg)
{
    printf("hello thread!,pid = %d, phtread id = %ld, i = %d\n",
        getpid(),pthread_self());

    printf("thread gvar = %p\n",&g_var);
    pthread_exit(&g_var);
}

int main(int argc, char const *argv[])
{
    pthread_t thread;
    int ret = pthread_create(&thread,NULL,func,NULL);
    if (ret != 0)
    {
        printf("pthread_create error,%s\n",strerror(ret));
        return -1;
    }

    void *p = NULL;
    pthread_join(thread, &p);
    printf("address of p = %p\n",p);

    return 0;
}
