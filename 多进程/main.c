#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid = fork();
    if(pid == -1)
        perror("fork");
    else if(pid == 0) {
        /* Child */
        printf("Child\n");

    } else if(pid > 0) {
        /* Father */
        printf("Father\n");
    }
    /* Master */
    printf("Master\n");
    return 0;
}
