#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BYTE2READ 1*4


int main (void)
{
    int fd;
    char *p, s[100];
    int n;
    uint32_t start=100;

    printf("Abro el pwm\n");
    if ( (fd = open("/dev/chardev_pwm_EMIOgpio_PL", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo leds_control_chardev\n");
        return -1;
    }
    printf("Cierro el pwm \n");
    while(1)
    {
        printf("Ingrese el porcentaje de velocidad \n");
        while (fgets(s, sizeof(s), stdin)) {
            n = strtol(s, &p, 10);
            if (p == s || *p != '\n') {
                printf("Por favor ingrese un entero \n ");
            } else break;
        }
        printf("Escribiste: %d\n", n);
        // if ( ( write(fd, &start, BYTE2READ)) == -1)
        // {
        //     //perror("close"):
        //     printf("Error escribiendo leds_control_chardev\n");
        //     return -1;
        // }
        // usleep(100000);
        //n = rand();
        //n = n%100;
        //n += 1;
        printf("Escribiste: %d\n", n);
        if ( ( write(fd, &n, BYTE2READ)) == -1)
        {
            //perror("close"):
            printf("Error escribiendo leds_control_chardev\n");
            return -1;
        }
        usleep(100000);
    }
    close(fd);
    return 0;
}
