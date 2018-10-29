#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int *oof_random()
{
    int *p = malloc(4);
    int devrand;
    if( (devrand = open("/dev/random", O_RDONLY)) == -1 ) {
        printf("#### ERROR ACCESSING /dev/random ####\n%s\n",
                strerror(errno));
        return NULL;
    }
    read( devrand, p, 4);
    if( close(devrand) ) {
        printf("#### ERROR CLOSING /dev/random ####\n%s\n",
                strerror(errno));
        return NULL;
    }
    return p;
}

int main()
{
    int *p;
    int i = 10;
    while( i-- ) {
        p = oof_random();
        printf("OOF! %08X\n", *p);
        free(p);
    }
    return 0;
}
