#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    //�����׽���
    int sock;
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 0;
    }

    //����������ض���IP�Ͷ˿ڣ���������
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    if((connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)) {
        perror("connect");
        return 0;
    }

    //��ȡ���������ص�����
    char buffer[40];
    read(sock, buffer, sizeof(buffer)-1);
   
    printf("Message form server: %s\n", buffer);
   
    //�ر��׽���
    close(sock);

    return 0;
}
