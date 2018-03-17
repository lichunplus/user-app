#include <time.h>
#include <stdio.h>

int main(void)
{
    /* 获取日历时间 => string */
    time_t sec = time(NULL);
    printf("%s", ctime(&sec));
    
    /* 日历时间=>本地时间 */
    struct tm *local;
    local = localtime(&sec);
    printf("local hour is :%d\n",local->tm_hour);
    
    /* 日历时间=>UTC */
    struct tm *utc;
    utc = gmtime(&sec);
    printf("utc hour is :%d\n",utc->tm_hour);

    return 0;
}
