#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define BYTE2READ 1*4

#define ADELANTE    (0x1<<0) | (0x0<<1) | (0x1<<2) | (0x0<<3) 
#define FRENAR      (0x0<<0) | (0x0<<1) | (0x0<<2) | (0x0<<3)
#define DERECHA     (0x1<<0) | (0x0<<1) | (0x0<<2) | (0x1<<3)
#define IZQUIERDA   (0x0<<0) | (0x1<<1) | (0x1<<2) | (0x0<<3) 
#define ATRAS       (0x0<<0) | (0x1<<1) | (0x0<<2) | (0x1<<3) 

int main (int argc, char *argv[])
{
    int fd;
    uint32_t buff_send;

    buff_send = atoi(argv[1]) ;

    switch (buff_send)
    {
        case 0:
            buff_send = FRENAR;
            break;
        case 1:
            buff_send = ADELANTE;
            break;
        case 2:
            buff_send = IZQUIERDA;
            break;
        case 3:
            buff_send = DERECHA;
            break;
        case 4:
            buff_send = ATRAS;
            break;
        default:
            buff_send = FRENAR;
            break;
    }

    if ( (fd = open("/dev/chardev_EMIOgpio_PL", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo chardev_EMIOgpio_PL\n");
        return -1;
    }

    if ( ( write(fd, &buff_send, BYTE2READ)) == -1)
    {
        //perror("close"):
        printf("Error escribiendo leds_control_chardev\n");
        return -1;
    }

    close(fd);
    return 0;
}
