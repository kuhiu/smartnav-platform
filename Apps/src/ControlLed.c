#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define BYTE2READ 1*4


int main (int argc, char *argv[])
{
    printf("Llegue \n");
    int fd;
    int ubuff[BYTE2READ];
    uint32_t buff_send[BYTE2READ];

    *buff_send = atoi(argv[1]) ;

    if(argc!=2 || ( *buff_send >15 )) {
        printf("Ha olvidado el valor de los leds o el numero es muy grande ej. 01 para 1\n");
        exit(1);
    }

    if ( (fd = open("/dev/leds_control_chardev", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo leds_control_chardev\n");
        return -1;
    }

    if ( ( read(fd, ubuff, BYTE2READ)) == -1)
    {
        //perror("close"):
        printf("Error leyendo leds_control_chardev\n");
        return -1;
    }
    printf("Lei los leds = %08X \n", *ubuff);

    printf("buffsend %d \n", *buff_send);

    if ( ( write(fd, buff_send, BYTE2READ)) == -1)
    {
        //perror("close"):
        printf("Error escribiendo leds_control_chardev\n");
        return -1;
    }


    if ( ( read(fd, ubuff, BYTE2READ)) == -1)
    {
        //perror("close"):
        printf("Error leyendo leds_control_chardev\n");
        return -1;
    }
    printf("Lei los leds = %08X \n", *ubuff);

    close(fd);
    return 0;
}
