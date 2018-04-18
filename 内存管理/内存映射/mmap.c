#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

static int psize;
static char *memory;

int main()
{
    int fd;
    fd = open("/dev/zero", O_RDONLY);
    psize = getpagesize(); //mmap必须以PAGE_SIZE()为单位映射
    printf("psize:%d\n", psize);
    //可以在两个进程都映射该文件时实现共享内存
    memory = mmap(NULL, psize*10, PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);
    
    memory[0] = 1;
    //设置内存为不可访问，禁止访问memory所指内存
    //mprotect(memory, psize*10, PROT_NONE);
    memory[0] = 0;/* Segmentation fault */
    
    printf("all done\n");
    munmap(memory, psize*10);
    
    return 0;
}
