#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <sys/epoll.h>

// 测试ET和LT的区别

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

    int epfd = epoll_create(5);
    if (epfd < 0)
    {
        perror("epfd");
        return -1;
    }
    
    // lfd 添加到 epfd 上
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);

    int nready;
    struct epoll_event events[1024];
    while (1)
    {
        nready = epoll_wait(epfd, events, 1024, -1);
        if (nready < 0)
        {
            perror("epoll err");
            if (errno == EINTR)
            {
                continue;
            }
            break;
        }

        int i;
        char buf[1024];
        for ( i = 0; i < nready; i++)
        {
            // 有客户端连接请求
            int sockfd = events[i].data.fd;
            if (sockfd == lfd)
            {
                int cfd = accept(lfd, NULL, NULL);

                ev.data.fd = cfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
                continue;
            }
            
            // 有客户端发送数据
            memset(buf, 0x00, sizeof(buf));
            // 发送10个，只读两个测试ET和LT区别
            int n = read(sockfd, buf, 2);
            if (n <= 0)
            {
                close(sockfd);

                epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);

            }
            else
            {
                printf("n = [%d], buf = [%s]\n", n, buf);
                
                write(sockfd, buf, n);
            }
            
        }
           
    }
    
    close(lfd);

    return 0;
}