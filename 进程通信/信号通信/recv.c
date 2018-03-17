#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void signal_handler(int signum)
{
    printf("====Signal ID:%d\n", signum);
}

int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    
    for(;;)
        usleep(10);

    return 0;
}
