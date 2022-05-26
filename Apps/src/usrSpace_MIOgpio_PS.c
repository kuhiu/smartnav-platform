#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define BYTE2READ 6*4

int main (int argc, char *argv[])
{
    int fd;
    long long int ubuff[BYTE2READ];
    long long int rightSensor=-1, centerSensor=-1, leftSensor=-1;

    if ( (fd = open("/dev/chardev_MIOgpio_PS", O_RDWR)) == -1)
    {
        printf("Error abriendo chardev_MIOgpio_PS\n");
        return -1;
    }

    if ( ( read(fd, ubuff, BYTE2READ)) == -1)
    {
        printf("Error leyendo leds_control_chardev\n");
        return -1;
    }

    rightSensor  = ubuff[0]*0.01715;
    centerSensor = ubuff[1]*0.01715;
    leftSensor   = ubuff[2]*0.01715;

    if ( (rightSensor > (long long int)500) || (rightSensor < (long long int)0) )
        rightSensor = -1;
    if ( (centerSensor > (long long int)500) || (centerSensor < (long long int)0) )
        centerSensor = -1;  
    if ( (leftSensor > (long long int)500) || (leftSensor < (long long int)0) )
        leftSensor = -1;

    printf("Distancia = Left: %lld cms, Center: %lld cms, Right: %lld cms \n", leftSensor, centerSensor, rightSensor);

    close(fd);
    return 0;
}
