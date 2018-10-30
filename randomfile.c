#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int oof_random()
{
    int *p = malloc(4);
    int devrand;
    if( (devrand = open("/dev/random", O_RDONLY)) == -1 ) {
        printf("#### ERROR ACCESSING /dev/random ####\n%s\n",
                strerror(errno));
        return 0;
    }
    read( devrand, p, 4);
    if( close(devrand) ) {
        printf("#### ERROR CLOSING /dev/random ####\n%s\n",
                strerror(errno));
        return 0;
    }
    int out = *p;
    free(p);
    return out;
}

int main()
{
    int arr[10];
    int i;
    int file;
    printf("\n\n\nGenerating values...\n");
    for( i = 0; i < 10; ++i )
        printf("OOF! %08X\n", arr[i] = oof_random());

    printf("\n\n\nWriting values...\n");
    if( (file = open("file", O_WRONLY ^ O_CREAT, 0755)) == -1 ) {
        printf("#### ERROR READING FILE ####\n%s\n",
                strerror(errno));
        return 0;
    }
    write( file, arr, sizeof(arr) );
    close( file );

    int rarr[10];
    printf("\n\n\nReading values...\n");
    if( (file = open("file", O_RDONLY, 0755)) == -1 ) {
        printf("#### ERROR READING FILE ####\n%s\n",
                strerror(errno));
        return 0;
    }
    read( file, rarr, sizeof(arr) );

    printf("\n\n\nPrinting values...\n");
    for( i = 0; i < 10; ++i )
        printf("OOF! %08X\n", rarr[i]);

    return 0;
}
