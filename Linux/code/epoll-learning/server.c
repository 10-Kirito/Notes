#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define IPADDRESS "127.0.0.1"
#define PORT 8789
#define MAXSIZE 1024
#define LISTENQ 5
#define FDSIZE 1000
#define EPOLLEVENTS 100

//添加事件
static void add_event(int epollfd,int fd,int state);
//修改事件
static void modify_event(int epollfd,int fd,int state);
//删除事件
static void delete_event(int epollfd,int fd,int state);
static void handle_events(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf);
static int socket_bind(const char*ip, int port);
static void do_epoll(int listenfd);

int main(int argc, char *argv[]) {
    int listenfd;
    listenfd = socket_bind(IPADDRESS, PORT); 
    listen(listenfd, LISTENQ);
    do_epoll(listenfd);
    return 0;
}
// 创建并绑定监听套接字
static int socket_bind(const char*ip, int port) {
    int listenfd;
    struct sockaddr_in serveraddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(listenfd == -1) {
        perror("socket error");
        exit(1);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serveraddr.sin_addr);
    serveraddr.sin_port = htons(port);
    if(bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1) {
        perror("bind error");
        exit(1);
    }
    return listenfd;
}

static void do_epoll(int listenfd) {
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    int ret;
    char buf[MAXSIZE];
    memset(buf, 0, MAXSIZE);
    epollfd = epoll_create(FDSIZE);

    // 添加监听描述符事件
    add_event(epollfd, listenfd, EPOLLIN);    
    for(;;) {
        // 获取已经准备好的描述符事件
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        handle_events(epollfd, events, ret, listenfd, buf);        
    }
    // 当我们结束的时候一定要记得将epoll对应的文件描述符关闭
    close(epollfd); 
}

static void handle_accpet(int epollfd,int listenfd);
static void do_read(int epollfd,int fd,char *buf);
static void do_write(int epollfd,int fd,char *buf);

static void handle_events(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf) {
    int i;
    int fd;
    // 进行遍历
    printf("the count of events is %d\n", num);
    for(i = 0; i < num; i++) {
        fd = events[i].data.fd;
        // 根据描述符的类型和事件类型进行处理
        if((fd == listenfd) && (events[i].events & EPOLLIN)) {
            handle_accpet(epollfd, listenfd);
            printf("hande accept\n");
        }else if(events[i].events & EPOLLIN) {
            do_read(epollfd, fd, buf);
            printf("hande read\n");
        }else if(events[i].events & EPOLLOUT) {
            do_write(epollfd, fd, buf);
            printf("hande write\n");
        }
    }
}

static void handle_accpet(int epollfd,int listenfd) {
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    clifd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen);

    if(clifd == -1) {
        perror("accept error:");
    }else {
        printf("accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        add_event(epollfd, clifd, EPOLLIN);
    }
}

static void do_read(int epollfd,int fd,char *buf) {
    int nread;
    
    nread = read(fd, buf, MAXSIZE);

    if(nread == -1) {
        perror("read error");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }else if(nread == 0){
        // if the client close the connection
        fprintf(stderr, "client close.\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }else {
        printf("read message is : %s", buf);
        // 服务端数据完毕，将对应的状态修改为可写, 使得服务端可以回应客户端
        // 修改描述符所对应的事件，由读改为写
        modify_event(epollfd, fd, EPOLLOUT);
    }
}
static void do_write(int epollfd,int fd,char *buf) {
    int nwrite;
    nwrite = write(fd, buf, strlen(buf));
    if(nwrite == -1) {
        perror("write error");
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    }else {
        // 服务端发送完数据，将对应的状态修改为可写
        modify_event(epollfd, fd, EPOLLIN);
    }
    memset(buf, 0, MAXSIZE);
}

static void add_event(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}