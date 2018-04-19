#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>

//gcc main.c -lpthread，内核维护，通过IPCS可查
//线程1自增变量1，线程2自增变量2
//两者相差不能大于5，初始信号量为5

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
/* union semun is defined by including <sys/sem.h> */
#else
/* according to X/OPEN we have to define it ourselves */
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};
#endif

int sem1,sem2;
static struct sembuf sops[2] = {
    {0, -1, SEM_UNDO},
    {0, +1, SEM_UNDO}
};
#define  SMrdn(sem_id)  semop(sem_id, &sops[0], 1)
#define  SMrup(sem_id)  semop(sem_id, &sops[1], 1)

void *thread1_handler()
{
    int i;
    for(i = 1; i <= 100; i++) 
    {
        if (SMrdn(sem1) == -1) {
            perror("SMrdn");
            break;
        }
        printf("number in thread1 is %d\n",i);
        if (SMrup(sem2) == -1) {
            perror("SMrup");
            break;
        }
    }
}

void *thread2_handler()
{
    int i;
    for(i = 1; i <= 100; i++)
    {
        if (SMrdn(sem2) == -1) {
            perror("SMrdn");
            break;
        }
        printf("number in thread2 is %d\n",i);
        if (SMrup(sem1) == -1) {
            perror("SMrup");
            break;
        }
    }
}

int main(void)
{
    union semun arg;
    arg.val = 5;
    
    /*创建或获取信号量，返回标识符semid，IPCS可查看*/
    if((sem1 = semget((key_t) 1234, 5, IPC_CREAT|0666)) == -1) {
        perror("semget");
        return 0;
    }
    if((sem2 = semget((key_t) 4321, 5, IPC_CREAT|0666)) == -1) {
        perror("semget");
        return 0;
    }
    if (semctl(sem1, 0, SETVAL, arg) == -1) {
        perror("semctl SETVAL");
        return 0;
    }
    if (semctl(sem2, 0, SETVAL, arg) == -1) {
        perror("semctl SETVAL");
        return 0;
    }
    /*创建线程*/
    pthread_t thread[2];
    int err;
    if((err = pthread_create(&thread[0], NULL, thread1_handler, NULL)) != 0) {
        perror("pthread_create");
        return 0;
    }
    if((err = pthread_create(&thread[1], NULL, thread2_handler, NULL)) != 0) {
        perror("pthread_create");
        return 0;
    }
    /*等待线程退出*/
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    /*销毁信号量*/
    semctl(sem1, 0, IPC_RMID, 0);
    semctl(sem2, 0, IPC_RMID, 0);
    
    return 0;
}
