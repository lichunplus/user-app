#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>

int  main()
{
    /*��ȡ�򴴽������ڴ�*/
    int shmid;
    if((shmid = shmget((key_t)25, 1024, 0)) == -1) {
        perror("shmget");
        return 0;
    }

    /*ӳ�乲���ڴ�*/
    char *shmptr;
    if((shmptr = shmat(shmid, 0, 0)) == (void *)-1) {
        perror("shmat");
        return 0;
    }

    printf("string :%s\n",shmptr);

    /*ȡ��ӳ��*/
    if(shmdt(shmptr) == -1) {
        perror("shmdt");
        return 0;
    }

    /*ɾ������Ĺ����ڴ�*/
    if(shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("shmctl");
        return 0;
    }

    return 0;
}
