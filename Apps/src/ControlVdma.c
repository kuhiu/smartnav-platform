#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int main (void)
{ 
    int fd;
    printf("llegue \n");
    if ( (fd = open("/dev/vdma_control_chardev", O_RDWR)) == -1){
        printf("Error abriendo vdma_control_chardev! %s\n", strerror(errno));
        return -1;
    }

    close(fd);
    return 0;
}