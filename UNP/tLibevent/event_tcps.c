#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <event2/event.h>


void readcb(evutil_socket_t fd, short events, void* arg)
{
    int n;
    char buf[1024];
    struct event *connev = (struct event *)arg;
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        n = read(fd, buf, sizeof(buf));
        if (n <= 0)
        {
            // 将通信文件描述符对应的事件从base上删除
            event_del(connev);

            close(fd);
            printf("client disconnect\n");
            break; 
        }
        else 
        {
            write(fd, buf, n);
            break;
        }
    }

}

void conncb(evutil_socket_t fd, short events, void* arg)
{
    struct event_base *base = (struct event_base *)arg;

    int cfd = accept(fd, NULL, NULL);
    if (cfd > 0)
    {
        // 创建通信文件描述符对应的事件并设置回调函数为readcb
        struct event *connev = event_new(base, cfd, EV_READ|EV_PERSIST, readcb, connev);
        if (connev == NULL)
        {
            exit(0);
        }
        
        printf("accept : %d\n", cfd);
        // 将通信文件描述符对应的事件上event_base
        event_add(connev, NULL);
    }
    
}

int main(int argc, char const *argv[])
{
    // 创建listen socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    // 设置端口复用
    int opt = 1;
    setsockopt(lfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(lfd, (struct sockaddr*)&serv, sizeof(serv));

    // 监听
    listen(lfd, 128);

    // 创建地基
    struct event_base *base = event_base_new();
    if (base == NULL)
    {
        printf("event_base_new error\n");
        return -1;
    }

    // 创建监听文件描述符对应的事件
    struct event *ev = event_new(base,lfd, EV_READ|EV_PERSIST, conncb, base);


    // 将新的事件结点添加到base
    event_add(ev, NULL);

    // 进入到事件循环等待
    event_base_dispatch(base);

    // 释放资源
    event_base_free(base);
    event_free(ev);

    close(lfd);

    return 0;
}