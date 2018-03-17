#include <fcntl.h>//open

int main()
{
    /* ��FIFO */
    int fd;
    if ((fd = open("demo.fifo", O_RDWR|O_NONBLOCK)) == -1) {
        perror("open");
        return 0;
    }
    
    /* дFIFO */
    ssize_t bytes;
    if((bytes = write(fd, "hello", sizeof("hello"))) == -1) {
        perror("write");
        return 0;
    }
    
    /* �ر�FIFO */
    close(fd);
    
    return 0;
}
