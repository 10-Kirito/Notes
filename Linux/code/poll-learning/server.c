#include <asm-generic/errno-base.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define IPADDRESS "127.0.0.1"
#define PORT 8787
#define MAXLINE 1024
#define LISTENQ 5
#define OPEN_MAX 1000
#define INFTIM -1

// 创建套接字并进行绑定
static int socket_bind(const char *ip, int port);
// IO多路复用poll
static void do_poll(int listenfd);
// 处理多个连接
static void handle_connection(struct pollfd *connfds, int num);

int main(int argc, char *argv[]) {
    int listenfd, connfd, sockfd;
    struct sockaddr_in servaddr;
    socklen_t   cliaddrlen;
    listenfd = socket_bind(IPADDRESS, PORT);
    listen(listenfd, LISTENQ);
    do_poll(listenfd);
    return 0;
}

static int socket_bind(const char *ip, int port) {
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1) {
        perror("socket error");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind error:");
        exit(1);
    }
    return listenfd;
}

static void do_poll(int listenfd) {
    int connfd, sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    /**
     struct pollfd {
        int fd;             -> file descriptor
        short events;       ->requested events
        short revents;      ->returned events
     }; 
     */
    struct pollfd cliendfds[OPEN_MAX];
    int maxi;
    int i;
    int nready;
    // 添加监听描述符
    cliendfds[0].fd = listenfd;
    cliendfds[0].events = POLLIN;

    // 初始化客户端连接描述符
    for(i = 1; i < OPEN_MAX; i++) {
        cliendfds[i].fd = -1;
    }
    maxi = 0;

    for(;;) {
        // 获取可用描述符的个数
        nready = poll(cliendfds, maxi + 1, INFTIM);
        if(nready == -1) {
            perror("poll error:");
            exit(1);
        }

        // 测试监听描述符是否准备好, 如果监听描述符没有事件发生，则说明是来自其他的客户端的消息
        if(cliendfds[0].revents & POLLIN) {
            // 监听描述符上面有新的连接请求
            cliaddrlen = sizeof(cliaddr);
            // 接收新的连接, 如果有错误发生
            if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen)) == -1) {
                if(errno == EINTR) {
                    continue;
                }else {
                    perror("accept error");
                    exit(1);
                }
            }

            fprintf(stdout, "accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);

            // 将新的连接描述符添加到数组当中
            for(i = 1; i < OPEN_MAX; i++) {
                // if cliendfds[i].fd < 0, it displays there is a position
                if(cliendfds[i].fd < 0) {
                    cliendfds[i].fd = connfd;
                    break;
                }
            }

            // 如果数组存储满了，也就是说服务器最多监听这么多客户端的连接
            if(i == OPEN_MAX){
                fprintf(stderr, "too many clients.\n");
                exit(1);
            }

            // 将新的描述符添加到读描述符集合当中
            cliendfds[i].events = POLLIN;
            // 记录客户端连接套接字的个数:
            maxi = (i > maxi ? i : maxi);

            // 如果--nready之后小于等于0，说明只有
            if(--nready <= 0) {
                continue;
            }
            
        }
        // 处理客户端的的消息的读写
        handle_connection(cliendfds, maxi);
    }
}

static void handle_connection(struct pollfd *connfds, int num) {
    int i, n;
    char buf[MAXLINE];
    memset(buf, 0, MAXLINE);
    for(i = 1; i <= num; i++) {
        if(connfds[i].fd < 0) {
            continue;
        }
        // 测试客户端是否有对应的事件发生
        if(connfds[i].revents & POLLIN) {
            // 接收来自客户端发送的信息
            n = read(connfds[i].fd, buf, MAXLINE);
            if(n == 0) {
                close(connfds[i].fd);
                connfds[i].fd = -1;
                continue;
            }
            // 往标准输出打印接收的信息
            write(STDOUT_FILENO, buf, n);
            // 往客户端发送buf
            write(connfds[i].fd, buf, n);
        }
    }
}
