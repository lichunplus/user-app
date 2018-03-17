#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

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
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);

    //��ͻ��˷�������
    int ret;
    char *str = "Hello,World!";
    if((ret = sendto(sock, str, strlen(str), 0, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr))) == -1) {
        perror("sendto");
        return 0;
    }

    //�ر��׽���
    close(sock);

    return 0;
}
