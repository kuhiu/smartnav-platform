#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Drive Control */
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define BYTE2READ_drive 1*4
#define BYTE2READ_speed 1*4

//#define SPEED_MIN       25

#define ADELANTE    (0x1<<0) | (0x0<<1) | (0x1<<2) | (0x0<<3) 
#define FRENAR      (0x0<<0) | (0x0<<1) | (0x0<<2) | (0x0<<3)
//#define DERECHA     (0x1<<0) | (0x0<<1) | (0x0<<2) | (0x1<<3)
//#define IZQUIERDA   (0x0<<0) | (0x1<<1) | (0x1<<2) | (0x0<<3) 
//#define ATRAS       (0x0<<0) | (0x1<<1) | (0x0<<2) | (0x1<<3) 

int initsem(key_t key, int nsems);

int is_running = 1;

union semun {
    int val;
    struct semid_ds *buf;
    short *array;
};

void sigintHandler(int signal_number){
    is_running = 0;
}

int main (void)
{
    /* Driver Control */
    int fd_drive, fd_pwm1, fd_pwm2;
    uint32_t buff_send[BYTE2READ_drive];

    // File
    FILE* fdd_State;
    ssize_t lread;
    char readed[10];
    char * line = NULL;
    size_t len = 0;  

    // Semaforo
    key_t key;              
    int semid, fdp;
    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = -1; /* set to allocate resource */
    sb.sem_flg = SEM_UNDO;

    int heading, speed, speed_1, speed_2, dirr;

    signal(SIGINT, sigintHandler);

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////   State TXT  //////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( (fdd_State = fopen("state.txt", "r+")) == NULL){
        printf("Error abriendo state.txt\n");
        return -1;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////// Inicializar semaforo  /////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if((fdp=open("SemFile", O_RDONLY | O_CREAT, 0777))==-1){
        perror(" Open");
        exit(1);
    }
    if((key = ftok("SemFile", 'E'))==-1){
        perror(" ftok ");
        close(fdp);
        exit(1);
    }
    if ((semid = initsem(key, 1)) == -1) {      /* Configura el semaforo */
        perror("initsem");
        close(fdp);
        exit(1);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////  Driver Control  //////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( (fd_drive = open("/dev/chardev_EMIOgpio_PL", O_RDWR)) == -1){
        printf("Error abriendo chardev_EMIOgpio_PL\n");
        return -1;
    }

    if ( (fd_pwm1 = open("/dev/chardev_pwm_EMIOgpio_PL_1", O_RDWR)) == -1){
        printf("Error abriendo chardev_pwm_EMIOgpio_PL_1\n");
        return -1;
    }

    if ( (fd_pwm2 = open("/dev/chardev_pwm_EMIOgpio_PL_2", O_RDWR)) == -1){
        printf("Error abriendo chardev_pwm_EMIOgpio_PL_2\n");
        return -1;
    }

    speed_1 = 0;
    speed_2 = 0;
    if ( ( write(fd_pwm1, &speed_1, BYTE2READ_speed)) == -1){
        printf("Error escribiendo leds_control_chardev\n");
        return -1;
    }

    if ( ( write(fd_pwm2, &speed_2, BYTE2READ_speed)) == -1){
        printf("Error escribiendo leds_control_chardev\n");
        return -1;
    }
    
    while(is_running){

        sb.sem_op = -1;         /* Asignar recurso */
        if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
            perror("semop");
            exit(1);
        }

        fseek(fdd_State, 0, SEEK_SET);
        // Leo el archivo buscando las entradas
        while ( (lread=getline(&line, &len, fdd_State )) != -1){
            switch (sscanf(line, "Angulo requerido = %s\n", readed )){
                case EOF:       // Error
                    perror("sscanf");
                    exit(1);
                    break;
                case 0:         // No encontro
                    //printf("No se encontro la linea: Sensores, rightSensor \n");
                    break;
                default:        // Encontro
                    heading = atof(readed);
                    break;
            }
            switch (sscanf(line, "ImgProc, Direccion = %s\n", readed )){
                case EOF:       // Error
                    perror("sscanf");
                    exit(1);
                    break;
                case 0:         // No encontro
                    //printf("No se encontro la linea: Sensores, rightSensor \n");
                    break;
                default:        // Encontro
                    dirr = atoi(readed);
                    break;
            }
            switch (sscanf(line, "Pwm, Velocidad = %s\n", readed )){
                case EOF:       // Error
                    perror("sscanf");
                    exit(1);
                    break;
                case 0:         // No encontro
                    //printf("No se encontro la linea: Sensores, rightSensor \n");
                    break;
                default:        // Encontro
                    speed = atoi(readed);
                    break;
            }
        }

        sb.sem_op = 1;          /* Libera el recurso */
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(1);
        }
        
        if(dirr>0){           // goTo right
            speed_1 = speed - heading;
            speed_2 = speed + heading;
            if (*buff_send != ADELANTE){
                *buff_send = ADELANTE;
                if ( ( write(fd_drive, buff_send, BYTE2READ_drive)) == -1){
                    printf("Error escribiendo leds_control_chardev\n");
                    return -1;
                }
            }
        }
        else{
            if (*buff_send != FRENAR){
                *buff_send = FRENAR;
                if ( ( write(fd_drive, buff_send, BYTE2READ_drive)) == -1){
                    printf("Error escribiendo leds_control_chardev\n");
                    return -1;
                }
            }
        } 

        if ( ( write(fd_pwm1, &speed_1, BYTE2READ_speed)) == -1){
            printf("Error escribiendo leds_control_chardev\n");
            return -1;
        }

        if ( ( write(fd_pwm2, &speed_2, BYTE2READ_speed)) == -1){
            printf("Error escribiendo leds_control_chardev\n");
            return -1;
        }

        sleep(0.1);
    }

    *buff_send = FRENAR;
    if ( ( write(fd_drive, buff_send, BYTE2READ_drive)) == -1){
        printf("Error escribiendo leds_control_chardev\n");
        return -1;
    }
    
    close(fd_pwm1);
    close(fd_pwm2);
    close(fd_drive);
    fclose(fdd_State);
    return 0;
}
