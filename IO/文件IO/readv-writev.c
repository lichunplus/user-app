#include <sys/uio.h>//readv writev preadv pwritev
#include <unistd.h>//STDOUT_FILENO

int main(int argc, char *argv[])
{
    static char buf1[10];
    static char buf2[20];
    struct iovec iv[2];
    iv[0].iov_base = buf1;
    iv[0].iov_len  = 10;
    iv[1].iov_base = buf2;
    iv[1].iov_len  = 20;
    
    /* 读到离散的缓存区 */
    ssize_t bytes;
    if((bytes = readv(STDIN_FILENO, iv, 2)) == -1) {
        perror("readv");
        return 0;
    }
    
    /* 离散缓存区一次写 */
    if((bytes = writev(STDOUT_FILENO, iv, 2)) == -1) {
        perror("write");
        return 0;
    }

    return 0;
}