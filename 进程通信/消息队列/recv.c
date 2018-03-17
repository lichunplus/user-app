#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct msgbuf
{
   long mtype;
   char mtext[2048];
};

int main()
{
    ssize_t ret;
    int msgid;
    struct msgbuf msg;

    /* 获取消息队列ID */
    if((msgid = msgget((key_t)1234, IPC_EXCL)) == -1) {
        perror("msgget");
        return 0;
    }

    /* 读取消息 */
    if ((ret = msgrcv(msgid, &msg, sizeof(msg), 0, IPC_NOWAIT)) == -1) {
        perror("msgrcv");
        return 0;
    }
    printf("mtype:%ld  mtext:%s\n", msg.mtype, msg.mtext);
    return 0;
}
