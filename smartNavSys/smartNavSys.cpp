#include "smartNavSys.hpp"

#define CONTROL_PERIOD      0.5

volatile int is_running = 1;

void sigquitHandler(int signal_number){
    is_running = 0;
}

int main() {
    distanceSensor myDistanceSensor;
    common myCommon;
    std::vector<int> vDistances;
    struct timeval begin;
    struct timeval end;
    long seconds;
    long microseconds;
    double elapsed;

    signal(SIGQUIT, sigquitHandler);
    while(is_running) {
        gettimeofday(&begin, 0);

        vDistances = myDistanceSensor.getDistances();
        myCommon.saveToState(vDistances[0], common::dataType::Sensor1);
        myCommon.saveToState(vDistances[1], common::dataType::Sensor2);
        myCommon.saveToState(vDistances[2], common::dataType::Sensor3);

        //std::cout << myCommon.readFromState(common::dataType::Sensor1) << std::endl;

        // Stop measuring time and calculate the elapsed time
        gettimeofday(&end, 0);
        seconds = end.tv_sec - begin.tv_sec;
        microseconds = end.tv_usec - begin.tv_usec;
        elapsed = seconds + microseconds*1e-6;

        if ( (CONTROL_PERIOD-elapsed) < 0 )
            is_running = 0;
        sleep(CONTROL_PERIOD-(elapsed));

        DEBUG_PRINT(("Elapsed: %f \n", elapsed));
        DEBUG_PRINT(("Sensores %d %d %d \n", vDistances[0], vDistances[1],  vDistances[2]));
    }
    return 0;
}