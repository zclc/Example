// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <event2/event.h>


int main(int argc, char const *argv[])
{
    // 获取当前系统支持的多路io复用方法
    const char** p = event_get_supported_methods();
    int i = 0;
    while (p[i] != NULL)
    {
        printf("%s ", p[i++]);
    }
    printf("\n");

    // 获取地基结点
    struct event_base *base = event_base_new();
    if (base == NULL)
    {
        printf("base new error\n");
        return -1;
    }
    
    // 获取当前libevent使用的io多路复用
    const char* pp = event_base_get_method(base);
    printf("%s\n",pp);

    // 释放地基结点
    event_base_free(base);

    return 0;
}