#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

typedef struct node
{
    int data;
    struct node* next;
}NODE;

NODE* head = NULL;

// 定义一把锁
pthread_mutex_t mutex;

// 定义条件变量
pthread_cond_t cond;

void* producer_fn(void* arg)
{
    NODE *pNode = NULL;
    while (1)
    {
        pNode = (NODE*)malloc(sizeof(NODE));
        if (pNode == NULL)
        {
            perror("malloc error");
            exit(-1);
        }
        pNode->data = rand()%100;

        printf("Producer:  %d\n", pNode->data);

        pthread_mutex_lock(&mutex);

        pNode->next = head;
        head = pNode;

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);

        sleep(1);
    }
    
}

void* consumer_fn(void* arg)
{
    NODE *pNode = NULL;

    int thread_idx = *(int*)arg;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (head == NULL)
        {
            // 若条件不满足，需要阻塞等待并解锁
            // 若条件满足（被pthread_cond_signal函数通知)，加锁，解除阻塞
            pthread_cond_wait(&cond, &mutex);
        }

        // 多个消费者时，if判断必须要有
        // 如果没有，由于会唤醒多个线程，可能会导致 
        // 有线程已经消费了空间，head指向NULL了还有线程去访问产生段错误
        if ( head == NULL)
        {
            pthread_mutex_unlock(&mutex);
            continue;
        }
        
        printf("Consumer[%d]:  %d\n", thread_idx, head->data);
        pNode = head; 
        head = head->next;

        pthread_mutex_unlock(&mutex);


        free(pNode);
        pNode = NULL;

        sleep(rand()%5);
    }
    
}

int main(int argc, char const *argv[])
{
    pthread_t producer;

    // 初始化互斥化锁
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    int ret = pthread_create(&producer,NULL,producer_fn,NULL);
    if (ret != 0)
    {
        printf("pthread_create error,%s\n",strerror(ret));
        return -1;
    }

    pthread_t consumer[5];
    int i;
    int arr[i];
    for ( i = 0; i < 5; i++)
    {
        arr[i] = i;
        ret = pthread_create(&consumer[i],NULL,consumer_fn,(void *)&arr[i]);
        if (ret != 0)
        {
            printf("pthread_create error,%s\n",strerror(ret));
            return -1;
        }
    }
    
    pthread_join(producer, NULL);
    
    for ( i = 0; i < 5; i++)
    {
        pthread_join(consumer[i], NULL);        
    }

    // 释放互斥锁
    pthread_mutex_destroy(&mutex);

    pthread_cond_destroy(&cond);

    return 0;
}
