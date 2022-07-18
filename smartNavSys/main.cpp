#include <main.hpp>

volatile int is_running = 1;

void sigquitHandler(int signal_number){
    is_running = 0;
}

int main() {
    /* Measure elapsed time */
    struct timeval begin;
    struct timeval end;
    long seconds;
    long microseconds;
    double elapsed;
    /* smartNavSys */
    smartNavSys smartNavSys;

    signal(SIGQUIT, sigquitHandler);

    while(is_running) {
        /* Start measure time */
        gettimeofday(&begin, 0);

        /* Run smartNavSys */
        smartNavSys.run();

        // Stop measuring time and calculate the elapsed time
        gettimeofday(&end, 0);
        seconds = end.tv_sec - begin.tv_sec;
        microseconds = end.tv_usec - begin.tv_usec;
        elapsed = seconds + microseconds*1e-6;

        /* Debug */
        DEBUG_PRINT(("main:: elapsed: %f \n", elapsed));

        if ( (CONTROL_PERIOD-elapsed) < 0 )
            is_running = 0;
        sleep(CONTROL_PERIOD-(elapsed));
    }
    return 0;
}