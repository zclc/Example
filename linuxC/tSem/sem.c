#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
 #include <semaphore.h>

// 使用信号量实现生产者消费者模型

typedef struct node
{
    int data;
    struct node* next;
}NODE;

NODE* head = NULL;

// 定义一把锁
pthread_mutex_t mutex;

// 定义信号量
sem_t sem_producer;
sem_t sem_consumer;


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

        // sem_producer--
        sem_wait(&sem_producer); 

        pNode->next = head;
        head = pNode;

        // sem_consumer++
        sem_post(&sem_consumer);
 
        sleep(rand()%3);
    }
    
}

void* consumer_fn(void* arg)
{
    NODE *pNode = NULL;
    while (1)
    {
        // sem_consumer == 0 阻塞， 
        // sem_consumer > 0 ==》 sem_consumer -- than continue run
        sem_wait(&sem_consumer);
        
        printf("Consumer:  %d\n", head->data);
        pNode = head; 
        head = head->next;

        sem_post(&sem_producer);

        free(pNode);
        pNode = NULL;

        sleep(rand()%3);
    }
    
}

int main(int argc, char const *argv[])
{
    pthread_t producer, consumer;

    // 初始化信号量
    sem_init(&sem_producer, 0, 5);
    sem_init(&sem_consumer, 0, 0);
    
    int ret = pthread_create(&producer,NULL,producer_fn,NULL);
    if (ret != 0)
    {
        printf("pthread_create error,%s\n",strerror(ret));
        return -1;
    }

    ret = pthread_create(&consumer,NULL,consumer_fn,NULL);
    if (ret != 0)
    {
        printf("pthread_create error,%s\n",strerror(ret));
        return -1;
    }

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
 

   sem_destroy(&sem_producer);
   sem_destroy(&sem_consumer);

    return 0;
}
