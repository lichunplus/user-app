#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();
    if(pid == -1)
        perror("fork");
    else if(pid == 0) {
        /* Child */
        printf("Child: %d\n", getpid());

    } else if(pid > 0) {
        /* Father */
        printf("Father: %d\n", getpid());
    }
    /* Common text segment */
    printf("Common: %d\n", getpid());
    
    return 0;
}
