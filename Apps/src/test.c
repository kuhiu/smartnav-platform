#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#define BYTE2READ 1*4

int main (void)
{ 
    int fd, leds;
    int lectura[BYTE2READ];

    printf("Test empieza\n");
    
    if ( (fd = open("/dev/chardev_leds_EMIOgpio_PL", O_RDWR)) == -1){
        //perror("open");
        printf("Error abriendo/dev/chardev_leds_EMIOgpio_PL %d\n", fd);
        return -1;
    }

    printf("Voy a leer \n"); 
    if ( ( read(fd, &lectura, BYTE2READ)) == -1){
        perror("read");
        return -1;
    }

    printf("Lei los leds y son %d\n", *lectura);

    leds = 0x03;
    if ( ( write(fd, &leds, BYTE2READ)) == -1){
        printf("Error escribiendo\n");
        return -1;
    }

    printf("Test termina\n"); 
    //close(fd);
    
    return 0;
}