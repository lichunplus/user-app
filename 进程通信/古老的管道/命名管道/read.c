#include <sys/types.h>//mkfifo
#include <sys/stat.h>//mkfifo
#include <fcntl.h>//open
#include <stdio.h>

int main()
{
    /* 创建一个FIFO */
    if(mkfifo("demo.fifo", 0644) == -1) {
        perror("mkfifo");
        return 0;
    }

    /* 打开FIFO */
    int fd;
    if ((fd = open("demo.fifo", O_RDONLY)) == -1) {
        perror("open");
        close(fd);
        return 0;
    }
    
    /* 读FIFO */
    ssize_t bytes;
    char buffer[10]={0};
    if((bytes = read(fd, buffer, sizeof(buffer))) == -1) {
        perror("read");
        close(fd);
        return 0;
    }
    printf("%s",buffer);
    
    /* 关闭FIFO */
    close(fd);
    
    return 0;
}
