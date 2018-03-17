#include <stdio.h>
/*   x86-64环境
    char  1字节
    shor  2字节
    int   4字节
*/
int main()
{
    struct A {    /* aaaa */
        int a;    /* b-cc */
        char b;   /* so, size of A: 8 */
        short c;
    };
    printf("size of A: %d\n",sizeof(struct A));
    
    struct B {    /* a--- */
        char a;   /* bbbb */
        int b;    /* cc-- */
        short c;  /* so, size of B: 12 */
    };
    printf("size of B: %d\n",sizeof(struct B));

#pragma pack (2)  /*指定按2字节对齐*/
    struct C {    /* a-bb */
        char a;   /* bbcc */
        int b;    /* so, size of C: 8 */
        short c;
    };
#pragma pack ()  /*取消指定对齐，恢复缺省对齐*/
    printf("size of C: %d\n",sizeof(struct C));

#pragma pack (1)  /*指定按1字节对齐*/  
    struct D {    /* abbb */
        char a;   /* bcc  */
        int b;    /* so, size of D: 7 */
        short c;
    };
#pragma pack ()   /*取消指定对齐，恢复缺省对齐*/
    printf("size of D: %d\n",sizeof(struct D));
    
    return 0;
}