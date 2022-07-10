#include "distanceSensors.hpp"

#define TIME_SLEEPING_S       0.50  /* Wake up each 500 mseg */
#define FILTER_N                 1
#define N_MIOgpio_PS             3  /* 3 int args from driver */
#define DEBUG           1           /* Comment if arent debugging */

volatile int is_running = 1;

int to_distance_cm (long long int time){
    long long int distance;

    distance = time*0.01715;

    if ( (distance > 500) || (distance < 0) )
        distance = 500;

    return distance;
}

void sigquitHandler(int signal_number){
    is_running = 0;
}

int saveInSTATE(struct sembuf *sb, int semid, FILE *fdd_State, long long int rightSensor, long long int centerSensor, long long int leftSensor){
    ssize_t loffset, lread;
    char *line = NULL;
    size_t len = 0;  
    int lineNro;
    char read[10];

    // Tomo el recurso
    sb->sem_op = -1;         
    if (semop(semid, sb, 1) == -1) {          
        perror("semop");
        exit(1);
    }

    /* Busco a lo largo del archivo "Sensores, rightSensor =" */
    lineNro = 0;
    loffset = 0;
    fseek(fdd_State, 0, SEEK_SET);
    while ( (lread=getline(&line, &len, fdd_State )) != -1)
    {
        lineNro++;
        loffset = loffset + lread;
        //printf("lineNro: %d \n", lineNro);
        //printf("line %s \n", line); 
        switch (sscanf(line, "Sensores, rightSensor = %s\n", read ))
        {
            case EOF:       // Error
                perror("sscanf");
                exit(1);
                break;
            case 0:         // No encontro
                //printf("No se encontro la linea: Sensores, rightSensor \n");
                break;
            default:        // Encontro
                //printf("La linea es la nro: %d, offset: %d \n", lineNro, loffset); 
                //printf("line %s \n", line); 
                sprintf(line, "Sensores, rightSensor = %03lld", rightSensor);
                fseek(fdd_State, (loffset-lread), SEEK_SET);
                if ( ( fwrite(line, sizeof(char), strlen(line), fdd_State)) != strlen(line)){
                    printf("Error escribiendo\n");
                    return -1;
                }
                fseek(fdd_State, (loffset), SEEK_SET);
                break;
        }

        switch (sscanf(line, "Sensores, centerSensor = %s\n", read ))
        {
            case EOF:       // Error
                perror("sscanf");
                exit(1);
                break;
            case 0:         // No encontro
                break;
            default:        // Encontro
                sprintf(line, "Sensores, centerSensor = %03lld", centerSensor); 
                fseek(fdd_State, (loffset-lread), SEEK_SET);
                if ( ( fwrite(line, sizeof(char), strlen(line), fdd_State)) != strlen(line))
                {
                    printf("Error escribiendo\n");
                    return -1;
                }
                fseek(fdd_State, (loffset), SEEK_SET);
                break;
        }

        switch (sscanf(line, "Sensores, leftSensor = %s\n", read ))
        {
            case EOF:       // Error
                perror("sscanf");
                exit(1);
                break;
            case 0:         // No encontro
                break;
            default:        // Encontro
                sprintf(line, "Sensores, leftSensor = %03lld", leftSensor); 
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
    // Libero el recurso
    sb->sem_op = 1;          
    if (semop(semid, sb, 1) == -1) {
        perror("semop");
        exit(1);
    }
    free(line); 
    return 0;
}

int main(){
    FILE* fdd_State = NULL;

    int fd_MIOgpio_PS;

    struct timeval begin, end;

    int mean_rightSensor, mean_centerSensor, mean_leftSensor;
    int accum_rightSensor, accum_centerSensor, accum_leftSensor;

    int rb_MIOgpio_PS[N_MIOgpio_PS];

    int i;

    long seconds, microseconds;
    double elapsed;

    key_t key;              
    int semid, fd_sem;
    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = -1; /* set to allocate resource */
    sb.sem_flg = SEM_UNDO;
    
    if ( (fdd_State = fopen("state.txt", "r+")) == NULL){
        printf("Error abriendo state.txt\n");
        return -1;
    }

    if ( (fd_MIOgpio_PS = open("/dev/chardev_MIOgpio_PS", O_RDONLY)) == -1){
        printf("Error abriendo chardev_MIOgpio_PS\n");
        return -1;
    }

    if((fd_sem=open("SemFile", O_RDONLY | O_CREAT, 0777))==-1){
        perror(" Open");
        exit(1);
    }

    if((key = ftok("SemFile", 'E'))==-1){
        perror(" ftok ");
        close(fd_sem);
        exit(1);
    }

    if ((semid = initsem(key, 1)) == -1) {      /* Configura el semaforo */
        perror("initsem");
        close(fd_sem);
        exit(1);
    }

    signal(SIGQUIT, sigquitHandler);

    while(is_running){
        // Start measuring time
        gettimeofday(&begin, 0);

        accum_rightSensor  = 0;
        accum_centerSensor = 0;
        accum_leftSensor   = 0;

        // Sensores de dist  
        for(i=FILTER_N;i>0;i--){

            /* This APi try each 100 mseg read each one sensor => 300 mseg */
            if ( read(fd_MIOgpio_PS, rb_MIOgpio_PS, N_MIOgpio_PS*sizeof(int)) == -1){
                printf("Error leyendo chardev_MIOgpio_PS\n");
                return -1;
            }
            accum_rightSensor  += to_distance_cm(rb_MIOgpio_PS[0]);
            accum_centerSensor += to_distance_cm(rb_MIOgpio_PS[1]);
            accum_leftSensor   += to_distance_cm(rb_MIOgpio_PS[2]);
        }
        mean_rightSensor  = accum_rightSensor / FILTER_N;
        mean_centerSensor = accum_centerSensor / FILTER_N;
        mean_leftSensor   = accum_leftSensor / FILTER_N;

        // Stop measuring time and calculate the elapsed time
        gettimeofday(&end, 0);
        seconds = end.tv_sec - begin.tv_sec;
        microseconds = end.tv_usec - begin.tv_usec;
        elapsed = seconds + microseconds*1e-6;

        saveInSTATE(&sb, semid, fdd_State, mean_rightSensor, mean_centerSensor, mean_leftSensor);

        DEBUG_PRINT(("elapsed %f, time 2 sleep seg %f\n", elapsed, (TIME_SLEEPING_S-elapsed) ));
        DEBUG_PRINT(("Distancia = Left: %d cms, Center: %d cms, Right: %d cms \n", mean_leftSensor, mean_centerSensor, mean_rightSensor));

        sleep(TIME_SLEEPING_S-(elapsed));
    }

    fclose(fdd_State);
    close(fd_MIOgpio_PS);
    close(fd_sem);
    return EXIT_SUCCESS;
}