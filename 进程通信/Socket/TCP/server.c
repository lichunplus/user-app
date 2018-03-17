#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    //�����׽���
    int serv_sock;
    if((serv_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 0;
    }

    //����Ϊ���ظ�ʹ��
    int yes = 1;
    if(setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) == -1){
        perror("setsockopt");
        return 0;
    }

    //���׽��ֺ�IP���˿ڰ�
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        return 0;
    }

    //�������״̬���ȴ��û���������
    if(listen(serv_sock, 20) == -1) {
        perror("listen");
        return 0;
    }

    //���տͻ�������
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock;
    if((clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size)) == -1) {
        perror("accept");
        return 0;
    }

    //��ͻ��˷�������
    char str[] = "Hello World!";
    write(clnt_sock, str, sizeof(str));
   
    //�ر��׽���
    close(clnt_sock);
    close(serv_sock);

    return 0;
}
