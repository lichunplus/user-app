#include <stdio.h>
/*   x86-64����
    char  1�ֽ�
    shor  2�ֽ�
    int   4�ֽ�
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

#pragma pack (2)  /*ָ����2�ֽڶ���*/
    struct C {    /* a-bb */
        char a;   /* bbcc */
        int b;    /* so, size of C: 8 */
        short c;
    };
#pragma pack ()  /*ȡ��ָ�����룬�ָ�ȱʡ����*/
    printf("size of C: %d\n",sizeof(struct C));

#pragma pack (1)  /*ָ����1�ֽڶ���*/  
    struct D {    /* abbb */
        char a;   /* bcc  */
        int b;    /* so, size of D: 7 */
        short c;
    };
#pragma pack ()   /*ȡ��ָ�����룬�ָ�ȱʡ����*/
    printf("size of D: %d\n",sizeof(struct D));
    
    return 0;
}