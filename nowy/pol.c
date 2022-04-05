#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
int main(int argc, char *argv[])
{
        FILE *fp;
        int  retcode;

        if (argc != 2) {
                fprintf(stderr, "Usage: %s <filename>\n",
                        argv[0]);
                exit(EINVAL);
        }
        if ( (fp = fopen(argv[1], "r")) == NULL ) {
                retcode = errno;  /* perror() may alter */ 
                perror("Open");   /* errno :-(          */ 
                exit(retcode);
        }
        return 0;
}