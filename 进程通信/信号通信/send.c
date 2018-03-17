#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Usage:\n""\t%s PID SignalID\n",argv[0]);
        return 0;
    }

    /* 给某个进程发送信号 */
    if(kill((pid_t)atoi(argv[1]), atoi(argv[2])) == -1) {
        perror("kill");
        return 0;
    }
    return 0;
}