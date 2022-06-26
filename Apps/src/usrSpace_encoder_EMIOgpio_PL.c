#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define BYTE2READ 16

int main (void)
{
    int fd;
    int ubuff[BYTE2READ];

    if ( (fd = open("/dev/chardev_encoder_EMIOgpio_PL", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo chardev_encoder_EMIOgpio_PL\n");
        return -1;
    }

    if ( ( read(fd, ubuff, BYTE2READ)) == -1)
    {
        //perror("close"):
        printf("Error leyendo leds_control_chardev\n");
        return -1;
    }
    printf(" Revoluciones: %f - %f rpm \n", (60*10*1000000/( (float)ubuff[0])), (60*10*1000000/( (float)ubuff[1])) );
    
    close(fd);
    return 0;
}
