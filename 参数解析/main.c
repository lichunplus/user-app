#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int opt;
    static const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"name", required_argument, NULL, 'n'},
        {"man", optional_argument, NULL, 'm'},
        {0, 0, 0, 0}
    };

    while((opt = getopt_long(argc, argv, "hn:m::",long_options, NULL)) != -1) {
        switch(opt) {
            case 'h':
                printf("====using:./a.out -n lichun\n");
                break;
            case 'n':
                printf("====required, %s\n", optarg);//./a.out -n=lichun
                break;                               //./a.out -n lichun
            case 'm':
                printf("====optional, %s\n", optarg);//./a.out -m=man
                break;
        }
    }

    return 0;
}