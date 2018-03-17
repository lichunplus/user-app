#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
//gcc main.c -lpthread

sem_t sem1,sem2;
void *thread1_handler()
{
    int i;
    for(i = 1; i <= 100; i++) 
    {
        if(sem_wait(&sem1) == -1) {
            perror("sem_wait");
            break;
        }
        printf("number in thread1 is %d\n",i);
        if(sem_post(&sem2) == -1) {
            perror("sem_post");
            break;
        }
    }
}

void *thread2_handler()
{
    int i;
    for(i = 1; i <= 100; i++)
    {
        if(sem_wait(&sem2) == -1) {
            perror("sem_wait");
            break;
        }
        printf("number in thread2 is %d\n",i);
        if(sem_post(&sem1) == -1) {
            perror("sem_post");
            break;
        }
    }
}

int main(void)
{
    /*初始化信号量*/
    if(sem_init(&sem1, 0, 5) == -1) {
        perror("sem_init");
        return 0;
    }
    if(sem_init(&sem2, 0, 5) == -1) {
        perror("sem_init");
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
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
