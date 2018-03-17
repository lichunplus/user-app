#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    /*获取或创建共享内存*/
    int shmid;
    if((shmid = shmget((key_t)25, 1024, IPC_CREAT|IPC_EXCL | 0600)) == -1) {
        perror("shmget");
        return 0;
    }

    /*映射共享内存*/
    char *shmptr;
    if((shmptr = shmat(shmid, 0, 0)) == (void *)-1) {
        perror("shmat");
        return 0;
    }

    sprintf(shmptr, "==========");

    /*取消映射*/
    if(shmdt(shmptr) == -1) {
        perror("shmdt");
        return 0;
    }

    return 0;
}
