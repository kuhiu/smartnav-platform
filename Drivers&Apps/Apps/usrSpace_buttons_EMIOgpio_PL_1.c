#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

#define BYTE2READ 4

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

int main (void)
{
    int fd;
    int ubuff;

    if ( (fd = open("/dev/chardev_buttons_EMIOgpio_PL_1", O_RDWR)) == -1){
        printf("Error abriendo chardev_buttons_EMIOgpio_PL_1\n");
        return -1;
    }

    signal(SIGINT, intHandler);
    
    while(keepRunning){
        if ( ( read(fd, &ubuff, BYTE2READ)) == -1){
            printf("Error leyendo leds_control_chardev\n");
            return -1;
        } 
        printf("El boton apretado fue %d\n", ubuff);   

        switch (ubuff)
        {
        case 1:
            system("/home/root/Tesis/Apps/usrSpace_drive_v3 100 0");
            break;
        case 2:
            system("/home/root/Tesis/Apps/usrSpace_drive_v3 200 0");
            break;
        case 3:
            system("/home/root/Tesis/Apps/usrSpace_drive_v3 100 100");
            break;
        case 4:
            system("/home/root/Tesis/Apps/usrSpace_drive");
            break;
        default:
            printf("Error, el boton no existe\n"); 
            break;
        }
    }

    printf("Sali del while\n");  
    close(fd);
    return 0;
}
