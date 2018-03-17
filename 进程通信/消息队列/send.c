#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>

struct msgbuf
{
   long mtype;
   char mtext[2048];
};

int main()
{
    int ret;
    int msqid;
    struct msgbuf msg;

    /* ������Ϣ���� */
    if ((msqid = msgget(1234, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        return 0;
    }

     /* ������Ϣ���� */
    msg.mtype = 1;
    strcpy(msg.mtext, "abc");

    if ((ret = msgsnd(msqid, &msg, sizeof(msg), IPC_NOWAIT)) == -1) {
        perror("msgsnd");
        return 0;
    }

    return 0;
}