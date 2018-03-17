#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd1,fd2;
    char buffer[1024];

    if ((fd1 = open("./src.txt", O_RDONLY)) == -1) {
        perror("open");
        return 0;
    }

    if ((fd2 = open("./dst.txt", O_CREAT|O_WRONLY|O_TRUNC, 0666)) == -1) {
        perror("open");
        return 0;
    }
    
    ssize_t bytes;
    while ((bytes = read(fd1, buffer, sizeof(buffer))) > 0) {
        if(write(fd2, buffer, bytes) != bytes)
            perror("write");
    }
    if(bytes == -1)
        perror("read");
   
    
    close(fd1);
    close(fd2);
    return 0;
}
