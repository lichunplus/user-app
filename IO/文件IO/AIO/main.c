/* ���뷽���� gcc main.c -laio */
#include <unistd.h>//sysconf
#include <stdio.h>//printf
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libaio.h>
#include <string.h>//strlen

#define MAX_NR_EVENTS 1000
#ifndef O_DIRECT
#define O_DIRECT O_DSYNC
#endif

char *str1 = "hello,summer!\n";
char *str2 = "hello,winter!\n";
char *str3 = "hello,spring!\n";

int main(){
    io_context_t ctx_id1;
    struct iocb iocb[3];//һ��iocb�������Ϊһ��IO����
    struct iocb *iop[3];
    
    /* �ļ��� */
    int fd;
    if((fd = open("demo.txt", O_CREAT|O_RDWR|O_TRUNC|O_DIRECT, 0644)) == -1) {
        perror("open");
        return 0;
    }
    
    /* ����AIO �����ģ�������ΪMAX_NR_EVENTS*/
    memset(&ctx_id1, 0, sizeof(ctx_id1));//�����ʼ��
    if(io_setup(MAX_NR_EVENTS, &ctx_id1) != 0){
        printf("io_setup error\n");
        return 0;
    }
    
    /* ��������iocb����ʾ����д���� */
    io_prep_pwrite(&iocb[0], fd, str1, strlen(str1), (off_t)0);
    iop[0] = &iocb[0];
    io_prep_pwrite(&iocb[1], fd, str2, strlen(str2), (off_t)100);
    iop[1] = &iocb[1];
    io_prep_pwrite(&iocb[2], fd, str3, strlen(str3), (off_t)200);
    iop[2] = &iocb[2];
    /* �ύ���������ύ���������� */
    if(io_submit(ctx_id1, 3, iop) != 3) {
        printf("io_submit error\n");
        goto out;
    }
    
    /* ������ȡ3��3��events��Null��ʾ����ʱ */
    struct io_event events[10];
    if(io_getevents(ctx_id1, 3, 3, events, NULL) != 3) {
        printf("io_getevents error\n");
        goto out;
    }
    int i;
    for(i=1; i<=3; i++) {
        if(events[i].res == -1) {
            printf("can't write str%d\n", i);
        }
    }
    
out:
    io_destroy(ctx_id1);
    close(fd);
    
    return 0;
}