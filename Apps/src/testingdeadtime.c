#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BYTE2READ 4

#define ADELANTE    (uint32_t) ((0x1<<0) | (0x0<<1) | (0x1<<2) | (0x0<<3))
#define FRENAR      (uint32_t) ((0x0<<0) | (0x0<<1) | (0x0<<2) | (0x0<<3))
#define DERECHA     (uint32_t) ((0x1<<0) | (0x0<<1) | (0x0<<2) | (0x1<<3))
#define IZQUIERDA   (uint32_t) ((0x0<<0) | (0x1<<1) | (0x1<<2) | (0x0<<3))
#define ATRAS       (uint32_t) ((0x0<<0) | (0x1<<1) | (0x0<<2) | (0x1<<3))

int main (void)
{
    int fd_pwm, fd_dir;
    char *p, s[100];
    int n;
    uint32_t buff_send;

    if ( (fd_pwm = open("/dev/chardev_pwm_EMIOgpio_PL", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo leds_control_chardev\n");
        return -1;
    }

    if ( (fd_dir = open("/dev/chardev_EMIOgpio_PL", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo chardev_EMIOgpio_PL\n");
        return -1;
    }

    while(1)
    {


        printf("Ingrese la direccion \n");
        while (fgets(s, sizeof(s), stdin)) {
            n = strtol(s, &p, 10);
            if (p == s || *p != '\n') {
                printf("Por favor ingrese un entero \n ");
            } else break;
        }
        printf("Escribiste: %d\n", n);

        switch (n)
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
        printf("buff_send %d\n", buff_send);

        if ( ( write(fd_dir, &buff_send, BYTE2READ)) == -1){
            printf("Error escribiendo leds_control_chardev\n");
            return -1;
        }
        
        printf("Ingrese el porcentaje de velocidad \n");
        while (fgets(s, sizeof(s), stdin)) {
            n = strtol(s, &p, 10);
            if (p == s || *p != '\n') {
                printf("Por favor ingrese un entero \n ");
            } else break;
        }
        printf("Escribiste: %d\n", n);

       if ( ( write(fd_pwm, &n, BYTE2READ)) == -1){
           printf("Error escribiendo leds_control_chardev\n");
           return -1;
       }

    }
    close(fd_dir);
    close(fd_pwm);
    return 0;
}
