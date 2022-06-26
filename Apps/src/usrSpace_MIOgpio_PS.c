#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BYTE2READ 8*3
#define FILTER_N  10

int to_distance_cm (long long int time)
{
    long long int distance;

    distance = time*0.01715;

    if ( (distance > 500) || (distance < 0) )
        distance = 500;

    return (int)distance;
}


int main (int argc, char *argv[])
{
    int fd, i, err;
    int rb_MIOgpio_PS[BYTE2READ];
    int mean_rightSensor, mean_centerSensor, mean_leftSensor;
    int accum_rightSensor, accum_centerSensor, accum_leftSensor;
    
    // Measure time
    struct timespec begin, end; 

    if ( (fd = open("/dev/chardev_MIOgpio_PS", O_RDWR)) == -1){
        printf("Error abriendo chardev_MIOgpio_PS\n");
        return -1;
    }

    while(1){
        accum_rightSensor  = 0;
        accum_centerSensor = 0;
        accum_leftSensor   = 0;

        // Start measuring time 
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);

        for(i=FILTER_N;i>0;i--){
            if ( read(fd, rb_MIOgpio_PS, BYTE2READ) == -1)
            {
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
        printf("Distancia = Left: %d cms, Center: %d cms, Right: %d cms \n", mean_leftSensor, mean_centerSensor, mean_rightSensor);

        // Stop measuring time and calculate the elapsed time
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;
        printf("Time executing.. %f \n", elapsed);

        //err = usleep(100000);
        //printf("err is: %d\n", err);

    }

    close(fd);
    return 0;
}
