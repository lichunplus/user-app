#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <poll.h>//poll

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
    struct pollfd pfd[2];
    pfd[0].fd = sock1;
    pfd[0].events = POLLIN;
    pfd[0].revents = 0;
    pfd[1].fd = sock2;
    pfd[1].events = POLLIN; /* Waiting for eventfd to go positive */
    pfd[1].revents = 0;
    
    while(pfd[0].events || pfd[1].events)
    {
        if (poll(pfd, 2, -1 /* ms; Wait forever */) == -1) {
            perror("poll");
            return 0;
        }
        
        if (pfd[0].revents) {
            char buffer[16]={0};
            read(pfd[0].fd, buffer, sizeof(buffer));
            printf("===from sock1: %s\n", buffer);
            pfd[0].revents = 0;
        }
        
        if (pfd[1].revents) {
            char buffer[16]={0};
            read(pfd[1].fd, buffer, sizeof(buffer));
            printf("===from sock2: %s\n", buffer);
            pfd[1].revents = 0;
        }
    }
/*----------------------------------------------------------------*/
    //关闭套接字
    close(sock1);
    close(sock2);

    return 0;
}
