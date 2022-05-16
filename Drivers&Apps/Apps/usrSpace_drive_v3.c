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
#define BYTE2READ_leds  1*4

#define ADELANTE    (0x1<<0) | (0x0<<1) | (0x1<<2) | (0x0<<3) 
#define FRENAR      (0x0<<0) | (0x0<<1) | (0x0<<2) | (0x0<<3)
#define DERECHA     (0x1<<0) | (0x0<<1) | (0x0<<2) | (0x1<<3)
#define IZQUIERDA   (0x0<<0) | (0x1<<1) | (0x1<<2) | (0x0<<3) 
#define ATRAS       (0x0<<0) | (0x1<<1) | (0x0<<2) | (0x1<<3) 

#define MAX_HEADING_ERROR        5
#define MAX_DIST2TARGET_ERROR   20

int initsem(key_t key, int nsems);
float go2abs_angle(FILE* fdd_State, float abs_angle2target, struct sembuf *sb, int semid, int fd_drive, int fd_speed, uint32_t *speed);
float read_from_state(FILE* fdd_State, char recurso[], struct sembuf *sb, int semid);
float from_rel_2_abs(float rel_angle2target, float start_angle);
int write_to_state(FILE* fdd_State, char recurso[], struct sembuf *sb, int semid);
uint32_t soft_start_pwm(uint32_t speed, uint32_t prevous_speed);
void read_from_state_string(FILE* fdd_State, char recurso[], struct sembuf *sb, int semid, char *readed);

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

uint32_t soft_start_pwm(uint32_t speed, uint32_t prevous_speed){
    uint32_t delta_speed;

    delta_speed = speed - prevous_speed;

    if(delta_speed > 10)
        return (prevous_speed + 10);
    else if(delta_speed < 10)
        return (prevous_speed - 10); 
    else
        return (prevous_speed + delta_speed);
}

float from_rel_2_abs(float rel_angle2target, float start_angle){
    float abs_angle2target=0;

    // Angulo absoluto 
    abs_angle2target = rel_angle2target + start_angle;
    if(abs_angle2target > 360)
        abs_angle2target = (int)abs_angle2target % 360; 
    
    return abs_angle2target;
}

int write_to_state(FILE* fdd_State, char dir_send[], struct sembuf *sb, int semid){
    
    char * line = NULL;
    size_t len = 0, lread;  
    ssize_t loffset;
    int lineNro;
    char readed[10];

    // Tomo el recurso
    sb->sem_op = -1;         
    if (semop(semid, sb, 1) == -1) {          
        perror("semop");
        exit(1);
    }

    /* Busco a lo largo del archivo */
    lineNro = 0;
    loffset = 0;
    fseek(fdd_State, 0, SEEK_SET);
    while ( (lread=getline(&line, &len, fdd_State )) != -1)
    {
        lineNro++;
        loffset = loffset + lread;
        //printf("lineNro: %d \n", lineNro);
        //printf("line %s \n", line); 
        // Write direction in save.txt
        switch (sscanf(line, "Desplazamiento = %s", readed ))
        {
            case EOF:       // Error
                perror("sscanf");
                exit(1);
                break;
            case 0:         // No encontro
                //printf("No se encontro: Brujula, Angulo\n");
                break;
            default:        // Encontro
                sprintf(line, "Desplazamiento = %s", dir_send); 
                fseek(fdd_State, (loffset-lread), SEEK_SET);
                if ( ( fwrite(line, sizeof(char), strlen(line), fdd_State)) != strlen(line))
                {
                    printf("Error escribiendo\n");
                    return -1;
                }
                fseek(fdd_State, (loffset), SEEK_SET);
                break;
        }
    }
    free(line);
    // Libero el recurso
    sb->sem_op = 1;          
    if (semop(semid, sb, 1) == -1) {
        perror("semop");
        exit(1);
    }

    return 0;
}


float read_from_state(FILE* fdd_State, char recurso[], struct sembuf *sb, int semid){
    float value;
    ssize_t lread;
    char readed[10];
    char * line = NULL;
    size_t len = 0;  

    // Tomo el recurso
    sb->sem_op = -1;         
    if (semop(semid, sb, 1) == -1) {          
        perror("semop");
        exit(1);
    }

    // Leo el state.txt
    // Antes de empezar el ciclo, veo cual es el angulo absoluto del robot y la distancia que ya recorrio
    fseek(fdd_State, 0, SEEK_SET);
    while ( (lread=getline(&line, &len, fdd_State )) != -1)
    {
        switch (sscanf(line, recurso, readed ))
        {
        case EOF:       // Error
            perror("sscanf");
            exit(1);
            break;
        case 0:         // No encontro
            //printf("No se encontro la linea: Sensores, rightSensor \n");
            break;
        default:        // Encontro
            value = atof(readed);
            break;
        }
    }
    free(line);

    // Libero el recurso
    sb->sem_op = 1;          
    if (semop(semid, sb, 1) == -1) {
        perror("semop");
        exit(1);
    }

    return value;
}

int go2abs_angle_save(FILE* fdd_State, float abs_angle2target, struct sembuf *sb, int semid, int fd_drive, int fd_speed, uint32_t *speed){
    float absolue, heading;
    uint32_t buff_send;
    const uint32_t zero_speed=0;
    char recurso[50];
    char recurso2[50] = "Brujula, Angulo = %s\n";
    char dir_send[50], readed[50], desplazamiento_state[10];

    absolue = read_from_state(fdd_State, recurso2, sb, semid);
    heading = abs_angle2target - absolue;

    if(heading > MAX_HEADING_ERROR || heading < -MAX_HEADING_ERROR){
        while (1) {
            absolue = read_from_state(fdd_State, recurso2, sb, semid);
            heading = abs_angle2target - absolue;

            if ((heading > 180) || (heading < (-180)))
                heading = (int)heading % 360;

            //printf("absolue %f, abs_angle2target %f \n", absolue, abs_angle2target);
            if (heading > MAX_HEADING_ERROR){
                // Leo la direccion actual            
                strcpy(recurso,"Desplazamiento = %s\n");
                read_from_state_string(fdd_State, recurso, sb, semid, readed);
                strcpy(desplazamiento_state, readed);

                //printf("en heading positivo desplazamiento_state : %s\n",desplazamiento_state);

                if ( strcmp(desplazamiento_state, "IZQUIERDA") != 0){ // Si no es igual, hubo un cambio de direccion
                    //printf("Cambio de direccion izq\n");
                    // Dead time para evitar tanto consumo de energia
                    if ( ( write(fd_speed, &zero_speed, BYTE2READ_speed)) == -1){
                        printf("Error escribiendo leds_control_chardev\n");
                        return -1;
                    }
                    // Espero que se detenga para no gastar tanta energia
                    usleep(500000); 
                    // Cambio la direccion
                    buff_send = IZQUIERDA;
                    if ( ( write(fd_drive, &buff_send, BYTE2READ_drive)) == -1){
                        printf("Error escribiendo leds_control_chardev\n");
                        return -1;
                    }
                    // Actualizo la direccion en state
                    strcpy(dir_send, "IZQUIERDA");
                    write_to_state(fdd_State, dir_send, sb, semid);
                    usleep(20000);
                    // Restauro velocidad
                    if ( ( write(fd_speed, speed, BYTE2READ_speed)) == -1){
                        printf("Error escribiendo leds_control_chardev\n");
                        return -1;
                    }
                }
            }
            else if (heading < -MAX_HEADING_ERROR) {
                strcpy(recurso,"Desplazamiento = %s\n");
                read_from_state_string(fdd_State, recurso, sb, semid, readed);
                strcpy(desplazamiento_state, readed);
                //printf("en heading negativo desplazamiento_state : %s\n",desplazamiento_state);
                if ( strcmp(desplazamiento_state, "DERECHA") != 0){ // Si no es igual, hubo un cambio de direccion
                    //printf("Cambio de direccion der\n");
                    // Dead time para evitar tanto consumo de energia
                    if ( ( write(fd_speed, &zero_speed, BYTE2READ_speed)) == -1){
                        printf("Error escribiendo leds_control_chardev\n");
                        return -1;
                    }
                    // Espero que se detenga para no gastar tanta energia
                    usleep(500000); 
                    // Cambio la direccion
                    buff_send = DERECHA;
                    if ( ( write(fd_drive, &buff_send, BYTE2READ_drive)) == -1){
                        printf("Error escribiendo leds_control_chardev\n");
                        return -1;
                    }
                    // Actualizo la direccion en state
                    strcpy(dir_send, "DERECHA  ");
                    write_to_state(fdd_State, dir_send, sb, semid);
                    usleep(20000);
                    // Restauro velocidad
                    if ( ( write(fd_speed, speed, BYTE2READ_speed)) == -1){
                        printf("Error escribiendo leds_control_chardev\n");
                        return -1;
                    }
                }
            }
            else{
                buff_send = FRENAR;
                if ( ( write(fd_drive, &buff_send, BYTE2READ_drive)) == -1)
                {
                    //perror("close"):
                    printf("Error escribiendo leds_control_chardev\n");
                    return -1;
                }
                strcpy(dir_send, "FRENAR   ");
                write_to_state(fdd_State, dir_send, sb, semid);
                break;
            }
        }
    }

    absolue = read_from_state(fdd_State, recurso2, sb, semid);
    return absolue;
}

float go2abs_angle(FILE* fdd_State, float abs_angle2target, struct sembuf *sb, int semid, int fd_drive, int fd_speed, uint32_t *speed){
    float absolue, heading;
    int speed2heading = 23;
    uint32_t buff_send;
    char recurso2[50] = "Brujula, Angulo = %s\n";
    char dir_send[50];

    absolue = read_from_state(fdd_State, recurso2, sb, semid);
    heading = abs_angle2target - absolue;

    if(heading > MAX_HEADING_ERROR || heading < -MAX_HEADING_ERROR){
        while (1) {
            absolue = read_from_state(fdd_State, recurso2, sb, semid);
            heading = abs_angle2target - absolue;

            if ((heading > 180) || (heading < (-180)))
                heading = (int)heading % 360;

            if ( ( write(fd_speed, &speed2heading, BYTE2READ_speed)) == -1){
                printf("Error escribiendo leds_control_chardev\n");
                return -1;
            }
            //printf("absolue %f, abs_angle2target %f \n", absolue, abs_angle2target);
            if (heading > MAX_HEADING_ERROR){
                buff_send = IZQUIERDA;      /* Cambio la direccion */
                if ( ( write(fd_drive, &buff_send, BYTE2READ_drive)) == -1){
                    printf("Error escribiendo leds_control_chardev\n");
                    return -1;
                }
                strcpy(dir_send, "IZQUIERDA");      /* Actualizo la direccion en state */
                write_to_state(fdd_State, dir_send, sb, semid);
            }
            else if (heading < -MAX_HEADING_ERROR) { 
                buff_send = DERECHA;    /* Cambio la direccion */
                if ( ( write(fd_drive, &buff_send, BYTE2READ_drive)) == -1){
                    printf("Error escribiendo leds_control_chardev\n");
                    return -1;
                }
                strcpy(dir_send, "DERECHA  ");      /* Actualizo la direccion en state */
                write_to_state(fdd_State, dir_send, sb, semid);
            }
            else
                break;
        }
    }

    //absolue = read_from_state(fdd_State, recurso2, sb, semid);
    return heading;
}

void read_from_state_string(FILE* fdd_State, char recurso[], struct sembuf *sb, int semid, char *readed){
    ssize_t lread;
    char * line = NULL;
    size_t len = 0;  

    // Tomo el recurso
    sb->sem_op = -1;         
    if (semop(semid, sb, 1) == -1) {          
        perror("semop");
        exit(1);
    }

    // Leo el state.txt
    // Antes de empezar el ciclo, veo cual es el angulo absoluto del robot y la distancia que ya recorrio
    fseek(fdd_State, 0, SEEK_SET);
    while ( (lread=getline(&line, &len, fdd_State )) != -1)
    {
        switch (sscanf(line, recurso, readed ))
        {
        case EOF:       // Error
            perror("sscanf");
            exit(1);
            break;
        case 0:         // No encontro
            //printf("No se encontro la linea: Sensores, rightSensor \n");
            break;
        default:        // Encontro
            break;
        }
    }
    free(line);
    // Libero el recurso
    sb->sem_op = 1;          
    if (semop(semid, sb, 1) == -1) {
        perror("semop");
        exit(1);
    }

    return;
}


int main (int argc, char* argv[])
{
    // Driver Control 
    int fd_drive, fd_speed;
    uint32_t speed, previous_speed=0; 
    const uint32_t zero_speed=0;
    uint32_t buff_send;

    // File
    FILE* fdd_State;

    // Semaforo
    key_t key;              
    int semid, fdp;
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1; /* set to allocate resource */
    sb.sem_flg = SEM_UNDO;

    // Fuzzy control output and more
    float theta, W;

    // Angulo absoluto al target
    float x_target, y_target;
    float abs_ang_robot=0, rel_ang_robot=0;   // Angulo al target, absoluto y relativo
    float start_angle=0;

    // Angulo al target
    float ang2target, dist2target;
    float x_robot=0, y_robot=0;
    float dx=0, dy=0;

    // Para saber la distancia recorrida 
    float actual_dist, past_dist, delta_dist;

    // Para leer state
    char recurso[50], dir_send[50];

    // Control de leds
    uint32_t leds;
    int fd_leds;

    // Medir el tiempo 
    //struct timespec begin, end; 

    float heading=0;

    // Chequeo argumentos de main
    if (argc != 3){
        printf("Espero una coordenada: x y ej. 1 2\n");
        return -1;
    }

    /* Leds driver fd */
    if ( (fd_leds = open("/dev/chardev_leds_EMIOgpio_PL", O_RDWR)) == -1){
        printf("Error abriendo/dev/chardev_leds_EMIOgpio_PL %d\n", fd_leds);
        return -1;
    }

    // Apago el led de meta
    if ( read(fd_leds, &leds, BYTE2READ_leds) == -1){
        perror("read");
        return -1;
    }
    leds = leds & ~(uint32_t)0x02;    /* Borro el leds[0] */
    printf("Voy a escribir leds = %d\n", leds);
    if ( ( write(fd_leds, &leds, BYTE2READ_leds)) == -1){
        printf("Error escribiendo\n");
        return -1;
    }

    // Argumentos de main, coordenadas x e y deseadas (TARGET)
    x_target = atof(argv[1]);
    y_target = atof(argv[2]);

    // Abro state.txt
    if ( (fdd_State = fopen("/home/root/Tesis/Apps/state.txt", "r+")) == NULL)
    {
        printf("Error abriendo state.txt\n");
        return -1;
    }
    // Mutex init
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
    // Drivers
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

    strcpy(recurso,"Brujula, Angulo = %s\n");
    start_angle = read_from_state(fdd_State, recurso, &sb, semid);

    // Seteo la velocidad de comienzo para el robot
    speed = 18;
    // if ( ( write(fd_speed, &speed, BYTE2READ_speed)) == -1){
    //     printf("Error escribiendo leds_control_chardev\n");
    //     return -1;
    // }

    // Angulo relativo al comienzo del target
    //rel_ang_robot = atan2(y_target,x_target)*180/M_PI;
    //printf("rel_angle2target: %f \n", rel_angle2target);

    // Pasar de relativo a absoluto
    //abs_ang_robot = from_rel_2_abs(rel_ang_robot, start_angle);

    //printf("abs_angle2target: %f \n", abs_angle2target);
    //abs_ang_robot = go2abs_angle(fdd_State, abs_ang_robot, &sb, semid, fd_drive, fd_speed, &speed);
    //printf("Con este angulo comienza la evasion abs_angle2target: %f \n", abs_ang_robot);

    // Para saber la distancia anterior
    strcpy(recurso,"Encoder, Distancia REAL = %s\n");
    past_dist = read_from_state(fdd_State, recurso, &sb, semid);

    while(1){   // Cada pasada es un delta
        // Leo theta, el angulo de evasion
        strcpy(recurso,"Angulo requerido = %s\n");
        theta = read_from_state(fdd_State, recurso, &sb, semid);

        // Leo W, el parametrod de decision
        strcpy(recurso,"W = %s\n");
        W = read_from_state(fdd_State, recurso, &sb, semid);

        // Funcion de decision (target/evasion)
        rel_ang_robot = (W)*(rel_ang_robot - theta) + (1-W)*ang2target;

        // Actualizo el angulo del robot
        abs_ang_robot = from_rel_2_abs( rel_ang_robot , start_angle);
        heading = go2abs_angle(fdd_State, abs_ang_robot, &sb, semid, fd_drive, fd_speed, &speed); 

        if ( ( write(fd_speed, &speed, BYTE2READ_speed)) == -1){
            printf("Error escribiendo leds_control_chardev\n");
            return -1;
        }

        // Avanzo ,Envio la accion
        buff_send = ADELANTE;
        if ( ( write(fd_drive, &buff_send, BYTE2READ_drive)) == -1){
            printf("Error escribiendo leds_control_chardev\n");
            return -1;
        }
        strcpy(dir_send, "ADELANTE ");
        write_to_state(fdd_State, dir_send, &sb, semid);

        // Duermo 1 segundo 
        sleep(1);

        // // Leo la velocidad de la salida del sistema difuso
        // strcpy(recurso,"Pwm, Velocidad = %s\n");
        // speed = (uint32_t)read_from_state(fdd_State, recurso, &sb, semid);
        // //speed = soft_start_pwm(speed, previous_speed);

        // // Envio la velocidad del robot
        // if ( ( write(fd_speed, (int*)&speed, BYTE2READ_speed)) == -1){
        //     printf("Error escribiendo leds_control_chardev\n");
        //     return -1;
        // }

        // Leo la distancia recorrida 
        strcpy(recurso,"Encoder, Distancia REAL = %s\n");
        actual_dist = read_from_state(fdd_State, recurso, &sb, semid);
        delta_dist = actual_dist - past_dist;
        
        // Actualizo la posicion del robot, a partir del delta de distancia y el heading utilizado en el ciclo anterior
        x_robot += delta_dist * cos(rel_ang_robot*M_PI/180); 
        y_robot += delta_dist * sin(rel_ang_robot*M_PI/180); 

        //Busco saber donde esta el target todo el tiempo
        dx = x_target-x_robot;
        dy = y_target-y_robot;
        dist2target = pow(dx,2) + pow(dy,2);
        dist2target = pow(dist2target,0.5);
        ang2target = atan2(dy,dx)*180/M_PI;  	// ang al target from +x (1,0)

        //Para debuggear
        printf("ang2target %f, W %f, rel_ang_robot %f, theta %f, (x_robot,y_robot) = (%f,%f), speed = %d, heading = %f, delta_dist = %f\n", 
        ang2target, W, rel_ang_robot, theta, x_robot, y_robot, speed, heading, delta_dist);

        // Actualizo la distancia anterior
        past_dist = actual_dist;

        // Actualizo la velocidad anterior
        previous_speed = speed;

        // Salgo si llegue al target
        if( dist2target < MAX_DIST2TARGET_ERROR ){
            printf("Llegue a mi destino!!\n");
            buff_send = FRENAR;
            if ( ( write(fd_drive, &buff_send, BYTE2READ_drive)) == -1){
                printf("Error escribiendo leds_control_chardev\n");
                return -1;
            }
            strcpy(dir_send, "FRENAR  ");
            write_to_state(fdd_State, dir_send, &sb, semid);

            // Enciendo el led de la meta
            if ( read(fd_leds, &leds, BYTE2READ_leds) == -1){
                perror("read");
                return -1;
            }
            leds = leds | 0x02;    /* Seteo el leds[0] */
            printf("Voy a escribir leds = %d\n", leds);
            if ( ( write(fd_leds, &leds, BYTE2READ_leds)) == -1){
                printf("Error escribiendo\n");
                return -1;
            }
            //Para debuggear
            printf("ang2target %f, W %f, rel_ang_robot %f, theta %f, (x_robot,y_robot) = (%f,%f), speed = %d, heading = %f, delta_dist = %f\n", 
            ang2target, W, rel_ang_robot, theta, x_robot, y_robot, speed, heading, delta_dist);
            break;
        }

        if ( ( write(fd_speed, &zero_speed, BYTE2READ_speed)) == -1){
            printf("Error escribiendo leds_control_chardev\n");
            return -1;
        }

        printf("Press Enter to Continue");
        while( getchar() != '\n' );
    }
    return 0;
}
