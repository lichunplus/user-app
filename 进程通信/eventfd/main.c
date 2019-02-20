#include <sys/eventfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)
/*
eventfd是一个内核维护的uint64_t变量，通过fd访问
1. 每次write都会累加值
2. read可获取最终值
Usage: ./a.out <num>...
[root@CentOS eventfd]# ./a.out 1 2 4
Child writing 1 to efd
Child writing 2 to efd
Child writing 4 to efd
Child completed write loop
Parent about to read
Parent read 7 (0x7) from efd
*/
int
main(int argc, char *argv[])
{
   int efd, j;
   uint64_t u;
   ssize_t s;

   if (argc < 2) {
       fprintf(stderr, "Usage: %s <num>...\n", argv[0]);
       exit(EXIT_FAILURE);
   }

   efd = eventfd(0, 0);
   if (efd == -1)
       handle_error("eventfd");

   switch (fork()) {
   case 0: /*parent*/
       for (j = 1; j < argc; j++) {
           /* strtoull() allows various bases */
           u = strtoull(argv[j], NULL, 0);
           printf("Child writing %lu to efd\n", u);
           s = write(efd, &u, sizeof(uint64_t));
           if (s != sizeof(uint64_t))
               handle_error("write");
       }
       printf("Child completed write loop\n");

       exit(EXIT_SUCCESS);

   default:/*child*/
       sleep(2);

       printf("Parent about to read\n");
       s = read(efd, &u, sizeof(uint64_t));
       if (s != sizeof(uint64_t))
           handle_error("read");
       printf("Parent read %llu (0x%llx) from efd\n",
               (unsigned long long) u, (unsigned long long) u);
       exit(EXIT_SUCCESS);

   case -1:
       handle_error("fork");
   }
}