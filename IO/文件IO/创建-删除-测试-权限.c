#include <fcntl.h>//open
#include <unistd.h>//read write close unlink
#include <stdio.h>
#include <sys/stat.h>//umask

int main(int argc, char *argv[])
{
    char *filename = "./demo.txt";
    mode_t old_umask;

    if (access(filename, F_OK) == 0) {
        printf("file exists!\n");
        return 0;
    } else {
        /* 创建文件 */
        old_umask = umask(0000);
        if(creat(filename, 0777) < 0) {
            perror("creat");
            return 0;
        }
        umask(old_umask);
    }
    /* 删除文件 */
    if(unlink(filename) == -1) {
        perror("unlink");
        return 0;
    }
    return 0;
}
