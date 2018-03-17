#include <pthread.h>
#include <stdio.h>
//gcc main.c -lpthread

int number=0;
pthread_t thread[2];
static pthread_mutex_t mut;

void *thread1_handler()
{
    int i;
    for (i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&mut);
        printf("thread1 : number = %d\n",number);
        number++;
        pthread_mutex_unlock(&mut);
    }
}

void *thread2_handler()
{
    int i;
    for (i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&mut);
        printf("thread2 : number = %d\n",number);
        number++;
        pthread_mutex_unlock(&mut);
    }
}

int main()
{
    pthread_mutex_init(&mut,NULL);

    /*创建线程*/
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

    pthread_mutex_destroy(&mut);
    return 0;
}