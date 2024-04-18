#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <sys/poll.h>
#include <sys/socket.h>
#define MAXLINE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8787

#define max(a, b) (a > b) ? a : b

static void handle_connection(int sockfd);

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);
    
    
    int result = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(result == -1) {
        fprintf(stdout, "connect the server failed");
        return -1;
    }

    handle_connection(sockfd);
    return 0;
}

static void handle_connection(int sockfd) {
    char sendline[MAXLINE], recvline[MAXLINE];
    int maxfdp, stdineof;
    struct pollfd pfds[2];
    int n;
    // 添加连接描述符`
    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN; 
    // 添加标准输入描述符
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;

    for(;;) {
        poll(pfds, 2, -1);
        if(pfds[0].revents & POLLIN) {
            printf("from server's message\n");
            n = read(sockfd, recvline, MAXLINE);
            if(n == 0){
                fprintf(stderr, "client: server is closed.\n");
                close(sockfd);
            }
            printf("write(STDOUT_FILENOm recvline, n)\n");
            write(STDOUT_FILENO, recvline, n);
        }

        // 测试标准输入是否准备好
        if(pfds[1].revents & POLLIN) {
            n = read(STDIN_FILENO, sendline, MAXLINE);
            if(n == 0) {
                shutdown(sockfd, SHUT_WR);
                continue;
            }
            printf("send the input data to server\n");
            write(sockfd, sendline, n);
        }
    }
}

