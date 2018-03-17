#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int fd[2];
    char buffer[1024];
    char *str = "hello";
    ssize_t bytes;
    
    if(pipe(fd) == -1)
    {
        perror("pipe");
        return 0;
    }

    pid_t pid = fork();
    if(pid == -1) {
        /* Error */
        perror("fork");
        return 0;
    } else if(pid == 0) {
        /* Child */
        bytes = read(fd[0], buffer, sizeof(buffer));
        close(fd[0]);
        printf("Read %d bytes: %s\n", bytes, buffer);
        return 0;
    } else if(pid > 0) {
        /* Father */
        bytes = write(fd[1], str, strlen(str));
        close(fd[1]);
        printf("Wrote %d bytes: %s\n", bytes, str);
        return 0;
    }
    /* Master */
    printf("Master\n");
    return 0;
}
