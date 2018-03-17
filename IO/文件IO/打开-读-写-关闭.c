#include <fcntl.h>//open
#include <unistd.h>//read write close

int main(int argc, char *argv[])
{
    /* �ļ��� */
    int fd;
    if((fd = open("demo.txt", O_CREAT|O_RDWR|O_TRUNC, 0644)) == -1) {
        perror("open");
        return 0;
    }
    /* д�ļ� */
    ssize_t bytes;
    if((bytes = write(fd, "hello", sizeof("hello"))) == -1) {
        perror("write");
        return 0;
    }
    fdatasync(fd);//�������ļ�modified����Ϊst_atime��st_mtime���Ǻ���Ҫ
    fsync(fd);//ͬ�������ļ�
    
    lseek(fd, (off_t)0, SEEK_SET);
    
    /* ���ļ� */
    //ssize_t bytes;
    char buffer[16]={0};
    if((bytes = read(fd, buffer, sizeof(buffer))) == -1) {
        perror("read");
        return 0;
    }
    //fd = dup(1);
    dup2(1, fd);//�ر�fd,����Դfdӳ�䵽��׼�����
    if((bytes = write(fd, "hello", sizeof("hello"))) == -1) {
        perror("write");
        return 0;
    }
    //���ļ���СΪ1G
    if (ftruncate(fd, 1*1024*1024*1024) == -1) {
        perror("ftruncate");
        return 0;
    }
    close(fd);

    return 0;
}