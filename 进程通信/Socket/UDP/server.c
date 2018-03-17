#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main() {
    //创建套接字
    int sock;
    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
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
    if(bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        return 0;
    }

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    //向客户端发送数据
    char buffer[1024]={0};
    ssize_t ret;
    if((ret = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size)) == -1) {
        perror("recvfrom");
        return 0;
    }
    printf("==%s\n",buffer);
    //关闭套接字
    close(sock);

    return 0;
}
