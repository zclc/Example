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
#include <poll.h>

int main(int argc, char const *argv[])
{
    // 创建用于 listen 的 socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    // 设置地址复用
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

    struct pollfd pclient[1024];
    int i;
    for ( i = 0; i < 1024; i++)
    {
        pclient[i].fd = -1;
    }
    
    // 将监听文件描述符委托给内核监控
    pclient[0].fd = lfd;
    pclient[0].events = POLLIN;

    /// maxi 表示内核监控的范围
    int maxi = 0;

    int nready;
    int cfd;
    while (1)
    {
        nready = poll(pclient, maxi+1, -1);
        if (nready < 0)
        {
            perror("poll error");
            exit(1);
        }
        
        // 有客户端连接
        if (pclient[0].revents == POLLIN)
        {
            cfd = accept(lfd, NULL, NULL);
            
            // 把cfd放在数组中
            for ( i = 1; i < 1024; i++)
            {
                if (pclient[i].fd == -1)
                {
                    pclient[i].fd = cfd;
                    pclient[i].events = POLLIN;
                    break;
                }
                
            }
            
            if (i==1024)
            {
                close(cfd);
                continue;
            }
            
            if(maxi < i)
            {
                maxi = i;
            }

            if (--nready == 0)
            {
                continue;
            }
        }
        
        // 有客户端发数据
        int clientfd;
        char buf[1024];
        for ( i = 1; i <= maxi; i++)
        {
            if (pclient[i].fd == -1)
            {
                continue;
            }
            // 必须需要这个判断
            if (pclient[i].revents == POLLIN)
            {
                clientfd = pclient[i].fd;
                memset(buf, 0x00, sizeof(buf));
                int n = read(clientfd, buf, sizeof(buf));
                if(n <= 0)
                {
                    close(clientfd);
                    
                    pclient[i].fd = -1;
                }
                else
                {
                    printf("clientfd == %d\n", clientfd);
                    printf("n == %d,  buf == %s\n", n, buf);
                    
                    write(clientfd, buf, n);
                }

                if(--nready == 0)
                {
                    break;
                }

            }
        }
        
    }
    
    close(lfd);

    return 0;
}