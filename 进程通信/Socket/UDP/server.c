#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main() {
    //�����׽���
    int sock;
    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        return 0;
    }

    //���׽��ֺ�IP���˿ڰ�
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

    //���տͻ�������
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    //��ͻ��˷�������
    char buffer[1024]={0};
    ssize_t ret;
    if((ret = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size)) == -1) {
        perror("recvfrom");
        return 0;
    }
    printf("==%s\n",buffer);
    //�ر��׽���
    close(sock);

    return 0;
}
