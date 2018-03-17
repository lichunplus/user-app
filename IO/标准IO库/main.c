#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /* 文件打开 */
    FILE *fp;
    if((fp = fopen("demo.txt", "w+")) == NULL){
        perror("fopen");
        return 0;
    }
/* -------------------字节 stdin > fp */
    int ch;
    while(scanf("%c", &ch) != EOF) {
        if(fputc(ch, fp) == EOF) {
            perror("fputc");
            fclose(fp);
            return 0;
        }
    }
    rewind(fp);
/* -------------------字节 fp > stdout */
    //int ch;
    while( (ch = fgetc(fp)) != EOF){
        if(putchar(ch) == EOF) {
            perror("putchar");
            fclose(fp);
            return 0;
        }
    }
    rewind(fp);
/* ===================字符串 stdin > fp */
    char str[10];
    while(scanf("%s", &str) != EOF) {
        if(fputs(str, fp) == EOF) {
            perror("fputs");
            fclose(fp);
            return 0;
        }
    }
    fseek(fp,0,SEEK_SET);
/* ===================字符串 fp > stdout */
    //char str[10]={0};
    memset(str, 0 ,sizeof(str));
    while(fgets(str, sizeof(str), fp) != NULL) {
        if(puts(str) == EOF) {
            perror("puts");
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);

    return 0;
}
