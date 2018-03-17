#include <time.h>
#include <stdio.h>

int main(void)
{
    /* ��ȡ����ʱ�� => string */
    time_t sec = time(NULL);
    printf("%s", ctime(&sec));
    
    /* ����ʱ��=>����ʱ�� */
    struct tm *local;
    local = localtime(&sec);
    printf("local hour is :%d\n",local->tm_hour);
    
    /* ����ʱ��=>UTC */
    struct tm *utc;
    utc = gmtime(&sec);
    printf("utc hour is :%d\n",utc->tm_hour);

    return 0;
}
