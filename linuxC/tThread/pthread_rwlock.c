// 读写锁测试
// 3个线程不定时写一全局资源，5个线程不定时读一个全局资源

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

pthread_rwlock_t rwlock;

int number = 0;

void *thread_write(void* arg)
{
    int i = *(int*)arg;

    int cur;
    while (1)
    {
        // 加写锁
        pthread_rwlock_wrlock(&rwlock);
        cur = number; 
        cur++;
        number = cur;
        printf("[%d]-W:[%d]\n",i,cur);

        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
    
}

void *thread_read(void* arg)
{
    int i = *(int*)arg;
    int cur;
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        cur = number;
        printf("[%d]-R:[%d]\n",i,cur);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
    
}

int main(int argc, char const *argv[])
{
    //创建子线程
    int n = 8;
    int i = 0;
    pthread_t thread[8]; 
    int arr[8];

    pthread_rwlock_init(&rwlock,NULL);

    // 3个写线程
    for ( i = 0; i < 3; i++)
    {
        arr[i] =i;
        pthread_create(&thread[i],NULL,thread_write,&arr[i]);
    }
    
    
    for ( i = 3; i < n; i++)
    {
        arr[i] =i;
        pthread_create(&thread[i],NULL,thread_read,&arr[i]);
    }

    int j;    
    for ( j = 0; j < 8; j++)
    {
        pthread_join(thread[j],NULL);
    }
    
    pthread_rwlock_destroy(&rwlock);

    return 0;
}