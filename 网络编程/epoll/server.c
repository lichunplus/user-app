#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    //创建套接字
    int sock1,sock2;
    if((sock1 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        return 0;
    }
    if((sock2 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        return 0;
    }

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);
    if(bind(sock1, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        return 0;
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(2345);
    if(bind(sock2, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        return 0;
    }
/*----------------------------------------------------------------*/
    #define MAX_EVENTS 10
    struct epoll_event ev, events[MAX_EVENTS];
    int nfds, epollfd;
    if ((epollfd = epoll_create(MAX_EVENTS)) == -1) {
        perror("epoll_create");
        return 0;
    }
    ev.events = EPOLLIN;
    ev.data.fd = sock1;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock1, &ev) == -1) {
        perror("epoll_ctl");
        return 0;
    }
    ev.events = EPOLLIN;
    ev.data.fd = sock2;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock2, &ev) == -1) {
        perror("epoll_ctl");
        return 0;
    }
    for (;;) {
        int i;
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_pwait");
            return 0;
        }
        for (i = 0; i < nfds; i++) {
            char buffer[16]={0};
            
            if (events[i].data.fd == sock1) {
                read(sock1, buffer, sizeof(buffer));
                printf("===from sock1: %s\n", buffer);
            }
            if (events[i].data.fd == sock2) {
                read(sock2, buffer, sizeof(buffer));
                printf("===from sock2: %s\n", buffer);
            }
        }
    }
/*----------------------------------------------------------------*/
    //关闭套接字
    close(epollfd);
    close(sock1);
    close(sock2);

    return 0;
}
