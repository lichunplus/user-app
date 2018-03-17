#include <fcntl.h>//open

int main()
{
    /* ´ò¿ªFIFO */
    int fd;
    if ((fd = open("demo.fifo", O_RDWR|O_NONBLOCK)) == -1) {
        perror("open");
        return 0;
    }
    
    /* Ð´FIFO */
    ssize_t bytes;
    if((bytes = write(fd, "hello", sizeof("hello"))) == -1) {
        perror("write");
        return 0;
    }
    
    /* ¹Ø±ÕFIFO */
    close(fd);
    
    return 0;
}
