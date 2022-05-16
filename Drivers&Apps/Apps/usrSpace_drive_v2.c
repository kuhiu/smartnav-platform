#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/ipc.h>
#include <math.h>
#include <sys/sem.h>
#include <string.h>
//#include <time.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Drive Control */
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define BYTE2READ_drive 1*4
#define BYTE2READ_speed 1*4

#define ADELANTE    (0x1<<0) | (0x0<<1) | (0x1<<2) | (0x0<<3) 
#define FRENAR      (0x0<<0) | (0x0<<1) | (0x0<<2) | (0x0<<3)
#define DERECHA     (0x1<<0) | (0x0<<1) | (0x0<<2) | (0x1<<3)
#define IZQUIERDA   (0x0<<0) | (0x1<<1) | (0x1<<2) | (0x0<<3) 
#define ATRAS       (0x0<<0) | (0x1<<1) | (0x0<<2) | (0x1<<3) 

int initsem(key_t key, int nsems);

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};


int main (int argc, char* argv[])
{
    /* Driver Control */
    int fd_drive, fd_speed;
    uint32_t buff_send[BYTE2READ_drive];
    uint32_t speed, start_speed=40;

    // File
    FILE* fdd_State;
    ssize_t lread;
    char readed[10], readed2[10];
    char * line = NULL;
    size_t len = 0;  

    // Semaforo
    key_t key;              
    int semid, fdp;
    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = -1; /* set to allocate resource */
    sb.sem_flg = SEM_UNDO;

    // Fuzzy control output and more
    float theta, W, heading;

    // Posicion actual y la del target
    float x_target, y_target;
    float x_actual=0, y_actual=0;

    // Para saber la distancia y el angulo anterior indicados en STATE.txt
    float delta_dist=0, delta_ang=0, past_dist=0, actual_dist=0, past_ang=0, actual_ang=0;
    float delta_ang_xy=0, past_ang_xy=0, actual_ang_xy=0;

    // Actual distancia y angulo al target
    float actual_dist2target=0, ang2target=0, actual_ang2target=0, start_ang=0;

    // Para buscar
    ssize_t loffset;
    int lineNro;
    char dir_send[10];

    // Medir el tiempo 
    //struct timespec begin, end; 

    // Chequeo argumentos de main
    if (argc != 3){
        printf("Espero una coordenada: x y ej. 1 2\n");
        return -1;
    }

    x_target = atof(argv[1]);
    y_target = atof(argv[2]);

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////   State TXT  //////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( (fdd_State = fopen("/home/root/Tesis/Apps/state.txt", "r+")) == NULL)
    {
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
    if ( (fd_drive = open("/dev/chardev_EMIOgpio_PL", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo chardev_EMIOgpio_PL\n");
        return -1;
    }
    if ( (fd_speed = open("/dev/chardev_pwm_EMIOgpio_PL", O_RDWR)) == -1)
    {
        //perror("open");
        printf("Error abriendo leds_control_chardev\n");
        return -1;
    }

    speed = 37;
    if ( ( write(fd_speed, &speed, BYTE2READ_speed)) == -1)
    {
        //perror("close"):
        printf("Error escribiendo leds_control_chardev\n");
        return -1;
    }

    // Antes de empezar el ciclo, veo cual es el angulo absoluto
    fseek(fdd_State, 0, SEEK_SET);
    // Leo el archivo buscando las entradas
    while ( (lread=getline(&line, &len, fdd_State )) != -1)
    {
        switch (sscanf(line, "Brujula, Angulo = %s\n", readed ))
        {
        case EOF:       // Error
            perror("sscanf");
            exit(1);
            break;
        case 0:         // No encontro
            //printf("No se encontro la linea: Sensores, rightSensor \n");
            break;
        default:        // Encontro
            past_ang = atof(readed);
            break;
        }
        switch (sscanf(line, "Encoder, Distancia REAL = %s - %s\n", readed, readed2 ))
        {
        case EOF:       // Error
            perror("sscanf");
            exit(1);
            break;
        case 0:         // No encontro
            //printf("No se encontro la linea: Sensores, rightSensor \n");
            break;
        default:        // Encontro
            past_dist = atof(readed);
            break;
        }
        switch (sscanf(line, "Pwm, Velocidad = %s\n", readed ))
        {
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
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    actual_ang2target = atan(x_target/y_target);
    actual_ang2target = actual_ang2target*180/M_PI;

    if (x_target>0 && y_target>0)
        actual_ang2target = actual_ang2target;
    else if (x_target<0 && y_target>0)
        actual_ang2target = actual_ang2target;
    else if (x_target>0 && y_target<0)    
        actual_ang2target = 180 + actual_ang2target;
    else if (x_target<0 && y_target<0)
        actual_ang2target = actual_ang2target - 180; 

    ang2target = actual_ang2target;
    start_ang = past_ang;
    past_ang_xy = actual_ang2target;
    actual_ang_xy = past_ang_xy;

    printf("x_target %f, y_target %f \n", x_target, y_target);
    actual_dist2target = (pow(x_target,2) + pow(y_target,2));
    actual_dist2target = pow(actual_dist2target, 0.5);

    printf("Primera impresion de actual_ang2target %f y actual_dist2target %f \n", actual_ang2target, actual_dist2target);
    printf("Primera impresion de past_dist %f y past_ang %f \n", past_dist, past_ang);

    while(1)
    {
        // Leo STATE.txt 
        
        //printf("Trying to lock...\n");
        sb.sem_op = -1;         /* Asignar recurso */
        if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
            perror("semop");
            exit(1);
        }
        //printf("Locked.\n");

            fseek(fdd_State, 0, SEEK_SET);
            // Leo el archivo buscando las entradas
            while ( (lread=getline(&line, &len, fdd_State )) != -1)
            {
                switch (sscanf(line, "Angulo requerido = %s\n", readed ))
                {
                case EOF:       // Error
                    perror("sscanf");
                    exit(1);
                    break;
                case 0:         // No encontro
                    //printf("No se encontro la linea: Sensores, rightSensor \n");
                    break;
                default:        // Encontro
                    theta = atof(readed);
                    break;
                }

                switch (sscanf(line, "W = %s\n", readed ))
                {
                case EOF:       // Error
                    perror("sscanf");
                    exit(1);
                    break;
                case 0:         // No encontro
                    //printf("No se encontro la linea: Sensores, rightSensor \n");
                    break;
                default:        // Encontro
                    W = atof(readed);
                    break;
                }

                switch (sscanf(line, "Encoder, Distancia REAL = %s\n", readed ))
                {
                case EOF:       // Error
                    perror("sscanf");
                    exit(1);
                    break;
                case 0:         // No encontro
                    //printf("No se encontro la linea: Sensores, rightSensor \n");
                    break;
                default:        // Encontro
                    actual_dist = atof(readed);
                    delta_dist = actual_dist - past_dist;
                    break;
                }
                switch (sscanf(line, "Brujula, Angulo = %s\n", readed ))
                {
                case EOF:       // Error
                    perror("sscanf");
                    exit(1);
                    break;
                case 0:         // No encontro
                    //printf("No se encontro la linea: Sensores, rightSensor \n");
                    break;
                default:        // Encontro
                    actual_ang = atoi(readed);
                    delta_ang = actual_ang - past_ang;
                    break;
                }

                switch (sscanf(line, "Pwm, Velocidad = %s\n", readed ))
                {
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

        // Funcion
        heading = (W)*(heading-theta) + (1-W)*actual_ang2target;        // Ojo, heading es relativo al (1,0)

        // Ahora veo
        actual_ang_xy = atan((x_target-x_actual)/(y_target-y_actual));
        actual_ang_xy = actual_ang_xy*180/M_PI;                   // Relativo al (0,1)

        if (x_target>0 && y_target>0)
            actual_ang2target = actual_ang2target;
        else if (x_target<0 && y_target>0)
            actual_ang2target = actual_ang2target;
        else if (x_target>0 && y_target<0)    
            actual_ang2target = 180 + actual_ang2target;
        else if (x_target<0 && y_target<0)
            actual_ang2target = actual_ang2target - 180; 

        delta_ang_xy = past_ang_xy - actual_ang_xy; 
        printf("actual_ang_xy %f, past_ang_xy %f, delta_ang_xy %f\n", actual_ang_xy, past_ang_xy, delta_ang_xy);

        // Actualizo la distancia al target
        actual_dist2target = (pow((x_target-x_actual),2) + pow((y_target-y_actual),2));
        actual_dist2target = pow(actual_dist2target, 0.5);

        // Accion a realizar, si estoy girando actualizo el angulo al target con la brujula, sino con x e y actual
        if (heading > 15){
            *buff_send = IZQUIERDA;
            strcpy(dir_send, "IZQUIERDA");
            actual_ang2target -= delta_ang;
        }
        else if (heading < -15) {
            *buff_send = DERECHA;
            strcpy(dir_send, "DERECHA  ");
            actual_ang2target -= delta_ang;
        }
        else{
            *buff_send = ADELANTE;
            strcpy(dir_send, "ADELANTE ");
            actual_ang2target += delta_ang_xy;

            // Actualizo la posicion del robot
            y_actual += delta_dist * cos(heading*M_PI/180); 
            x_actual += delta_dist * sin(heading*M_PI/180); 
        }

        // Envio la accion
        if ( ( write(fd_drive, buff_send, BYTE2READ_drive)) == -1)
        {
            //perror("close"):
            printf("Error escribiendo leds_control_chardev\n");
            return -1;
        }

        // En caso de llegar al target finalizo
        if ( abs(actual_dist2target) < 15){
            speed = 0;
            // Send speed
            if ( ( write(fd_speed, &speed, BYTE2READ_speed)) == -1)
            {
                //perror("close"):
                printf("Error escribiendo leds_control_chardev\n");
                return -1;
            }
            return 0;
        }

        printf("actual_dist2target %f, actual_ang2target es %f, theta es %f, w es %f, speed es %d, heading %f, xey_actual %f - %f\n", actual_dist2target, actual_ang2target, theta, W, speed, heading, x_actual, y_actual);

        past_dist = actual_dist;
        past_ang  = actual_ang;
        past_ang_xy = actual_ang_xy;
        usleep(10000);

    }

    close(fd_speed);
    close(fd_drive);
    fclose(fdd_State);
    
    return 0;
}




        // if (heading > 10){
        //     *buff_send = IZQUIERDA;
        //     strcpy(dir_send, "IZQUIERDA");
        // }
        // else if (heading < -10) {
        //     *buff_send = DERECHA;
        //     strcpy(dir_send, "DERECHA  ");
        // }
        // else{
        //     *buff_send = ADELANTE;
        //     strcpy(dir_send, "ADELANTE ");
        // }
        // // Actualizo la posicion actual del robot
        // //printf("delta_dist, delta_ang es %f %f \n", delta_dist, delta_ang);
        // y_actual += delta_dist * cos(delta_ang*M_PI/180); 
        // x_actual += delta_dist * sin(delta_ang*M_PI/180); 

        // actual_dist2target = (pow((x_target-x_actual),2) + pow((y_target-y_actual),2));
        // actual_dist2target = pow(actual_dist2target, 0.5);
        // printf("x_actual, y_actual es %f %f, delta_dist es %f, delta_ang %f \n", x_actual, y_actual, delta_dist, delta_ang);
        // //actual_dist2target -= delta_dist;

        // actual_ang2target_2 = atan((x_actual-x_target)/(y_actual-y_target));
        // actual_ang2target_2 = actual_ang2target_2*180/M_PI;
        // actual_ang2target -= (actual_ang - past_ang);  
        // printf("actual_dist2target %f, actual_ang2target es %f - %f, theta es %f, w es %f, speed es %d, heading %f \n", actual_dist2target, actual_ang2target, actual_ang2target_2, theta, W, speed, heading);

        // if ( abs(actual_dist2target) < 15){
        //     speed = 0;
        //     // Send speed
        //     if ( ( write(fd_speed, &speed, BYTE2READ_speed)) == -1)
        //     {
        //         //perror("close"):
        //         printf("Error escribiendo leds_control_chardev\n");
        //         return -1;
        //     }
        //     return 0;
        // }

        // /* Busco a lo largo del archivo */
        // lineNro = 0;
        // loffset = 0;
        // fseek(fdd_State, 0, SEEK_SET);
        // while ( (lread=getline(&line, &len, fdd_State )) != -1)
        // {
        //     lineNro++;
        //     loffset = loffset + lread;
        //     //printf("lineNro: %d \n", lineNro);
        //     //printf("line %s \n", line); 
        //     // Write direction in save.txt
        //     switch (sscanf(line, "Desplazamiento = %s", readed ))
        //     {
        //         case EOF:       // Error
        //             perror("sscanf");
        //             exit(1);
        //             break;
        //         case 0:         // No encontro
        //             //printf("No se encontro: Brujula, Angulo\n");
        //             break;
        //         default:        // Encontro
        //             sprintf(line, "Desplazamiento = %s", dir_send); 
        //             fseek(fdd_State, (loffset-lread), SEEK_SET);
        //             if ( ( fwrite(line, sizeof(char), strlen(line), fdd_State)) != strlen(line))
        //             {
        //                 printf("Error escribiendo\n");
        //                 return -1;
        //             }
        //             fseek(fdd_State, (loffset), SEEK_SET);
        //             break;
        //     }

        // }

        // if (speed <= 25){
        //     // Send start speed
        //     if ( ( write(fd_speed, &start_speed, BYTE2READ_speed)) == -1)
        //     {
        //         //perror("close"):
        //         printf("Error escribiendo leds_control_chardev\n");
        //         return -1;
        //     }
        //     usleep(10000);
        // }


        // // Send speed
        // if ( ( write(fd_speed, &speed, BYTE2READ_speed)) == -1)
        // {
        //     //perror("close"):
        //     printf("Error escribiendo leds_control_chardev\n");
        //     return -1;
        // }

        // // Send direction
        // if ( ( write(fd_drive, buff_send, BYTE2READ_drive)) == -1)
        // {
        //     //perror("close"):
        //     printf("Error escribiendo leds_control_chardev\n");
        //     return -1;
        // }

        // past_dist = actual_dist;
        // past_ang  = actual_ang;
        // usleep(10000);

        // // Stop measuring time and calculate the elapsed time
        // // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        // // long seconds = end.tv_sec - begin.tv_sec;
        // // long nanoseconds = end.tv_nsec - begin.tv_nsec;
        // // double elapsed = seconds + nanoseconds*1e-9;
        // // printf("Time executing.. %f \n", elapsed);