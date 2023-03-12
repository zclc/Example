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



int main(int argc, char const *argv[])
{
    // 创建socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    // 设置端口复用
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    // 绑定
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(lfd, (struct sockaddr*)&serv, sizeof(serv));

    // 监听
    listen(lfd, 128);

    // 定义fd_set类型的变量
    fd_set readfds;
    fd_set tmpfds;

    // 清空readfds和tmpfds集合
    FD_ZERO(&readfds);
    FD_ZERO(&tmpfds);

    // 将lfd加入到readfs中，委托内核监控
    FD_SET(lfd, &readfds);

    int maxfd = lfd;
    int nready;
    int cfd;
    int i;
    char buf[1024];

    while (1)
    {
        tmpfds = readfds;
        // tmpfds是输入输出参数
        // 输入：告诉内核要检测哪些文件描述符
        // 输出：内核告诉应用程序哪些文件描述符发生了变化
        nready = select(maxfd+1, &tmpfds, NULL, NULL, NULL);
        if (nready < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            break;
        }
        
        // 有客户端连接请求
        if (FD_ISSET(lfd, &tmpfds))
        {
            cfd = accept(lfd, NULL, NULL);

            // 将cfd加入到readfds中
            FD_SET(cfd, &readfds);

            // 修改内核的监控范围
            if(maxfd < cfd)
            {
                maxfd = cfd;
            }

            if (--nready == 0)
            {
                continue;
            }
        }

        int sockfd;
        int n;
        // 有数据发来的情况
        for ( i = lfd+1; i <= maxfd; i++)
        {
            sockfd = i;
            if (FD_ISSET(i, &tmpfds))
            {
                // 读数据
                memset(buf, 0, sizeof(buf));
                n = read(sockfd, buf, sizeof(buf));
                if (n<=0)
                {
                    close(sockfd);

                    // 将sockfd从fds中删除
                    FD_CLR(sockfd, &readfds);
                }
                else
                {
                    printf("n == [%d],  buf == [%s]\n", n, buf);
                    
                    write(sockfd, buf, n);
                }

                if (--nready == 0)
                {
                    break;
                }
            }
        }
    }
    close(lfd);

    return 0;
}


