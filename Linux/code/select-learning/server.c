#include <asm-generic/errno-base.h>
#include <asm-generic/socket.h>
#include <assert.h>
#include <bits/types/struct_timeval.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#define IPADDR "127.0.0.1"
#define PORT 8787
#define MAXLINE 1024
#define LISTENQ 5
#define SIZE 10

typedef struct server_context_st {
    // the number of clients
    int cli_cnt; 
    // store the file descriptor of clients
    int clidfs[SIZE];
    // the fd we need to monitor
    fd_set allfds;  
    // the max fd
    int maxfd;
}server_context_st;

static server_context_st* s_srv_ctx = NULL;

static int create_server_proc(const char* ip, int port) {
    int fd;
    struct sockaddr_in servaddr; 
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        fprintf(stderr, "create socket fail, erron:%n, reason:%s\n", errno, strerror(errno));
        return -1;
    }
    // 一个端口释放之后会等待两分钟之后才可以再次被使用，SO_REUSEADDR是让端口释放之后立即就可以被再次使用
    int reuse = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        return -1;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);
    if(bind(fd, (struct sockaddr*)&servaddr,sizeof(servaddr)) == -1) {
        perror("bind error");
        return -1;
    }
    listen(fd, LISTENQ);
    return fd;
}

static int accept_client_proc(int srvfd) {
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    int clifd = -1;
    printf("accept client proc is called\n");
ACCEPT:
    clifd = accept(srvfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
    if(clifd == -1){ 
        if(errno == EINTR) {
            goto ACCEPT;
        }else {
            fprintf(stderr, "accept fail, error:%s\n", strerror(errno));
            return -1;
        }
    }
    fprintf(stdout, "accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
    // add the new connection fd into array
    // 寻找一个空位置存储该建立连接的客户端socket
    int i = 0;
    for(i = 0; i < SIZE; i++) {
        if(s_srv_ctx->clidfs[i] < 0) {
            s_srv_ctx->clidfs[i] = clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }
    if(i == SIZE) {
        fprintf(stderr, "too many clients\n");
        return -1;
    }
    return 0;
}

static int handle_client_msg(int fd, char *buf) {
    assert(buf);
    printf("recv buf is: %s\n", buf);
    write(fd, buf, strlen(buf));
    return 0;
}

static void recv_client_msg(fd_set *readfds) {
    int i = 0, n = 0;
    int clifd;
    char buf[MAXLINE] = {0};
    for(i = 0; i <= s_srv_ctx->cli_cnt; i++) {
        clifd = s_srv_ctx->clidfs[i];
        if(clifd < 0) {
            continue;
        }
        // 这里检查服务端存储的客户端套接字是否位于readfds里面，如果存在的话，就接收相应的数据
        if(FD_ISSET(clifd, readfds)) {
            // reveive the message from client
            n = read(clifd, buf, MAXLINE);
            if(n <= 0) {
                // n == 0, finish read, client close the fd
                FD_CLR(clifd, &s_srv_ctx->allfds);
                close(clifd);
                s_srv_ctx->clidfs[i] = -1;
                continue;
            }
            handle_client_msg(clifd, buf);
        }
    }
}


static void handle_client_proc(int srvfd) {
    int clifd = -1;
    int retval = 0;
    fd_set *readfds = &s_srv_ctx->allfds;
    struct timeval tv;
    int i = 0;

    while (1) {
        // 每一次调用select之前我们都需要重新设置文件描述符以及时间，因为时间发生之后，文件描述符和时间都被内核修改了
        // 如何重新设置文件描述符，首先第一步调用FD_ZERO宏函数，来清空set，之后我们再将clients的文件描述符放进来即可
        FD_ZERO(readfds);
        // 将服务器端的监听套接字添加到readfds当中
        FD_SET(srvfd, readfds);
        s_srv_ctx->maxfd = srvfd;
        tv.tv_sec = 30;
        tv.tv_usec = 0;

        // add client socket
        for(i = 0; i < s_srv_ctx->cli_cnt; i++) {
            clifd = s_srv_ctx->clidfs[i];
            if(clifd != -1){
                FD_SET(clifd, readfds);
            }
            // 因为select底层是使用bitmap来存储相应的数据的，所以说我们需要记录已经建立连接的客户端socket以及服务端的socket当中最大的socket
            // 之后select会监视从0到nfds - 1的所有文件描述符
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd: s_srv_ctx->maxfd);
        }

        // 开始轮询接收处理服务器端和客户端套接字
        retval = select(s_srv_ctx->maxfd  + 1, readfds, NULL, NULL, &tv);
        // some errors ocured
        if(retval == -1) {
            fprintf(stderr, "select error:%s.\n", strerror(errno));
            return;
        }
        // timeout is over
        if(retval == 0) {
            fprintf(stdout, "select is timeout\n");
            continue;
        }
        // 调用FD_ISSET()函数检查对应的socket是否位于这个集合当中，因为在select函数将会更新这个集合，将其中不可读的socket去掉
        // 只保留符合条件的套接字在这个集合当中, 在一开始初始化readfds的时候，我们都会将srvfd即服务端的socket添加到该集合当中
        // 以及将所有的已经建立连接的客户端socket添加到readfds当中，当select的时候内核会将其中不可读的套接字去掉，只保留符合条件的套接字在这个集合当中.
        if(FD_ISSET(srvfd, readfds)) {
            // 监听客户端请求
            accept_client_proc(srvfd); 
        }else {
            recv_client_msg(readfds);
        }
    }
}


static void server_uninit() {
    if(s_srv_ctx) {
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
}

static int server_init() {
    s_srv_ctx = (server_context_st *)malloc(sizeof(server_context_st));
    if(s_srv_ctx == NULL) {
        return -1;
    }

    memset(s_srv_ctx, 0, sizeof(server_context_st));

    // 将服务器端所存储的客户端套接字全部设置为-1
    int i = 0;
    for(; i < SIZE; i++) {
        s_srv_ctx->clidfs[i] = -1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int srvfd;
    // 初始化服务端context
    if(server_init() < 0) {
        return -1;
    }
    // 创建服务，开始监听客户端请求
    srvfd = create_server_proc(IPADDR, PORT);
    if(srvfd < 0) {
        fprintf(stderr, "socket create or bind fail.\n");
        goto err;
    }
    // 开始接收并处理客户端请求
    handle_client_proc(srvfd);
    server_uninit();
    return 0;
err:
    server_uninit();
    return -1;
}