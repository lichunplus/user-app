#include <fcntl.h>//open
#include <unistd.h>//read write close

int main(int argc, char *argv[])
{
    /* 文件打开 */
    int fd;
    if((fd = open("demo.txt", O_CREAT|O_RDWR|O_TRUNC, 0644)) == -1) {
        perror("open");
        return 0;
    }
    /* 写文件 */
    ssize_t bytes;
    if((bytes = write(fd, "hello", sizeof("hello"))) == -1) {
        perror("write");
        return 0;
    }
    fdatasync(fd);//不包含文件modified，因为st_atime、st_mtime不是很重要
    fsync(fd);//同步整个文件
    
    lseek(fd, (off_t)0, SEEK_SET);
    
    /* 读文件 */
    //ssize_t bytes;
    char buffer[16]={0};
    if((bytes = read(fd, buffer, sizeof(buffer))) == -1) {
        perror("read");
        return 0;
    }
    //fd = dup(1);
    dup2(1, fd);//关闭fd,并将源fd映射到标准输出上
    if((bytes = write(fd, "hello", sizeof("hello"))) == -1) {
        perror("write");
        return 0;
    }
    //改文件大小为1G
    if (ftruncate(fd, 1*1024*1024*1024) == -1) {
        perror("ftruncate");
        return 0;
    }
    close(fd);

    return 0;
}