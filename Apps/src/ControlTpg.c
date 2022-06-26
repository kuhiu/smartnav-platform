#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>


int main (void)
{ 
    int fd;

    if ( (fd = open("/dev/xlnx,v-tpg-8.0", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo xlnx,v-tpg-8.0\n");
        return -1;
    }
    printf("Cierro el fd \n");
    close(fd);
    return 0;
}