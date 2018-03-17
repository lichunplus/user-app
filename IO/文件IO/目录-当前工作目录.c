#include <unistd.h>
#include <stdio.h>//printf
#include <limits.h>//MAXPATH
#include <sys/stat.h>//stat

int main(int argc, char *argv[])
{
    char *ret;
    char buffer[PATH_MAX];
    /* 获取进程当前工作目录 */
    ret = getcwd(buffer,PATH_MAX);
    if (ret == NULL) {
        perror("getcwd");
        return 0;
    }
    printf("PWD:%s\n",buffer);
    
    /* Make dir1 directory if needed. */
    /* 目录dir1不存在，则创建 */
    struct stat stat_buf;
    if (stat("dir1", &stat_buf) != 0) {
        if(mkdir("dir1", 0755) != 0) {
            perror("mkdir");
        }
    }
    
    /* 修改根目录 */
    const char *basedir = ".";
    if (chroot(basedir) == -1) {
        perror("chroot");
        return 0;
    }

    /* Change to dir1 directory. */
    //切换工作目录
    if (chdir("dir1") != 0)
        perror("getcwd");
    
    /* 再次获取进程当前工作目录 */
    ret = getcwd(buffer,PATH_MAX);
    if (ret == NULL) {
        perror("getcwd");
        return 0;
    }
    printf("PWD:%s\n",buffer);
    rmdir("/dir1");
}