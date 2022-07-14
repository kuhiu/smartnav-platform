#include "smartNavSys.hpp"

#define CONTROL_PERIOD      0.5

volatile int is_running = 1;

void sigquitHandler(int signal_number){
    is_running = 0;
}

int main() {
    distanceSensor myDistanceSensor;
    common myCommon;
    std::vector<int> vSensorData;
    struct timeval begin;
    struct timeval end;
    long seconds;
    long microseconds;
    double elapsed;

    std::vector<struct RULE> RULE_VECTOR;
    RULE_VECTOR.push_back(RULE23);
    RULE_VECTOR.push_back(RULE22);
    RULE_VECTOR.push_back(RULE21);
    RULE_VECTOR.push_back(RULE20);
    RULE_VECTOR.push_back(RULE19);
    RULE_VECTOR.push_back(RULE18);
    RULE_VECTOR.push_back(RULE17);
    RULE_VECTOR.push_back(RULE16);
    RULE_VECTOR.push_back(RULE15);
    RULE_VECTOR.push_back(RULE14);
    RULE_VECTOR.push_back(RULE13);
    RULE_VECTOR.push_back(RULE12);
    RULE_VECTOR.push_back(RULE11);
    RULE_VECTOR.push_back(RULE10);
    RULE_VECTOR.push_back(RULE9);
    RULE_VECTOR.push_back(RULE8);
    RULE_VECTOR.push_back(RULE7);
    RULE_VECTOR.push_back(RULE6);
    RULE_VECTOR.push_back(RULE5);
    RULE_VECTOR.push_back(RULE4);
    RULE_VECTOR.push_back(RULE3);
    RULE_VECTOR.push_back(RULE2);
    RULE_VECTOR.push_back(RULE1);
    RULE_VECTOR.push_back(RULE0);
    std::vector<fuzzyMembership> membershipsSensor1;
    std::vector<fuzzyInput> inputs;
    std::vector<fuzzyOutput> outputs;
    std::vector<fuzzyRule> rules;
    /* Create Fuzzy Input */
    membershipsSensor1.push_back(fuzzyMembership(   in_sensor1::membership1::MEMBERSHIP_LEJOS,
                                                    in_sensor1::membership1::point1,
                                                    in_sensor1::membership1::point2,
                                                    in_sensor1::membership1::slope1,
                                                    in_sensor1::membership1::slope2) );
    membershipsSensor1.push_back(fuzzyMembership(   in_sensor1::membership2::MEMBERSHIP_CERCA,
                                                    in_sensor1::membership2::point1,
                                                    in_sensor1::membership2::point2,
                                                    in_sensor1::membership2::slope1,
                                                    in_sensor1::membership2::slope2) );                                             
    fuzzyInput inputSensor1(in_sensor1::NAME, membershipsSensor1);
    /* Create Fuzzy Input */
    std::vector<fuzzyMembership> membershipsSensor2;
    membershipsSensor2.push_back(fuzzyMembership(   in_sensor2::membership1::MEMBERSHIP_LEJOS,
                                                    in_sensor2::membership1::point1,
                                                    in_sensor2::membership1::point2,
                                                    in_sensor2::membership1::slope1,
                                                    in_sensor2::membership1::slope2) );
    membershipsSensor2.push_back(fuzzyMembership(   in_sensor2::membership2::MEMBERSHIP_CERCA,
                                                    in_sensor2::membership2::point1,
                                                    in_sensor2::membership2::point2,
                                                    in_sensor2::membership2::slope1,
                                                    in_sensor2::membership2::slope2) );                                             
    fuzzyInput inputSensor2(in_sensor2::NAME, membershipsSensor2);
    /* Create Fuzzy Input */
    std::vector<fuzzyMembership> membershipsSensor3;
    membershipsSensor3.push_back(fuzzyMembership(   in_sensor3::membership1::MEMBERSHIP_LEJOS,
                                                    in_sensor3::membership1::point1,
                                                    in_sensor3::membership1::point2,
                                                    in_sensor3::membership1::slope1,
                                                    in_sensor3::membership1::slope2) );
    membershipsSensor3.push_back(fuzzyMembership(   in_sensor3::membership2::MEMBERSHIP_CERCA,
                                                    in_sensor3::membership2::point1,
                                                    in_sensor3::membership2::point2,
                                                    in_sensor3::membership2::slope1,
                                                    in_sensor3::membership2::slope2) );                                             
    fuzzyInput inputSensor3(in_sensor3::NAME, membershipsSensor3);
    /* Create Fuzzy Input */
    std::vector<fuzzyMembership> membershipsCamera;
    membershipsCamera.push_back(fuzzyMembership(    in_ov7670::membership1::MEMBERSHIP_DERECHA,
                                                    in_ov7670::membership1::point1,
                                                    in_ov7670::membership1::point2,
                                                    in_ov7670::membership1::slope1,
                                                    in_ov7670::membership1::slope2) );
    membershipsCamera.push_back(fuzzyMembership(    in_ov7670::membership2::MEMBERSHIP_CENTRO,
                                                    in_ov7670::membership2::point1,
                                                    in_ov7670::membership2::point2,
                                                    in_ov7670::membership2::slope1,
                                                    in_ov7670::membership2::slope2) );  
    membershipsCamera.push_back(fuzzyMembership(    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
                                                    in_ov7670::membership3::point1,
                                                    in_ov7670::membership3::point2,
                                                    in_ov7670::membership3::slope1,
                                                    in_ov7670::membership3::slope2) );                                             
    fuzzyInput inputCamera(in_ov7670::NAME, membershipsCamera);
    /* Create Fuzzy output */
    std::vector<fuzzyMembership> membershipsSpeed;
    membershipsSpeed.push_back(fuzzyMembership( out_speed::membership1::MEMBERSHIP_AUMENTAR,
                                                out_speed::membership1::point1,
                                                out_speed::membership1::point2,
                                                out_speed::membership1::slope1,
                                                out_speed::membership1::slope2) );
    membershipsSpeed.push_back(fuzzyMembership( out_speed::membership2::MEMBERSHIP_MANTENER,
                                                out_speed::membership2::point1,
                                                out_speed::membership2::point2,
                                                out_speed::membership2::slope1,
                                                out_speed::membership2::slope2) );  
    membershipsSpeed.push_back(fuzzyMembership( out_speed::membership3::MEMBERSHIP_REDUCIR,
                                                out_speed::membership3::point1,
                                                out_speed::membership3::point2,
                                                out_speed::membership3::slope1,
                                                out_speed::membership3::slope2) );                                             
    fuzzyOutput outputSpeed(out_speed::NAME, membershipsSpeed);
    /* Create Fuzzy output */
    std::vector<fuzzyMembership> membershipsHeading;
    membershipsHeading.push_back(fuzzyMembership(   out_heading::membership1::MEMBERSHIP_DERECHA,
                                                    out_heading::membership1::point1,
                                                    out_heading::membership1::point2,
                                                    out_heading::membership1::slope1,
                                                    out_heading::membership1::slope2) );
    membershipsHeading.push_back(fuzzyMembership(   out_heading::membership2::MEMBERSHIP_CENTRO,
                                                    out_heading::membership2::point1,
                                                    out_heading::membership2::point2,
                                                    out_heading::membership2::slope1,
                                                    out_heading::membership2::slope2) );  
    membershipsHeading.push_back(fuzzyMembership(   out_heading::membership3::MEMBERSHIP_IZQUIERDA,
                                                    out_heading::membership3::point1,
                                                    out_heading::membership3::point2,
                                                    out_heading::membership3::slope1,
                                                    out_heading::membership3::slope2) );                                             
    fuzzyOutput outputHeading(out_heading::NAME, membershipsHeading);

    /* Add RULES */
    for ( auto rule_to_add : RULE_VECTOR) {
        std::vector <fuzzyElement> if_vector;
        fuzzyElement if1(rule_to_add.RULE_SENSOR1, rule_to_add.RULE_SENSOR1_MEMBERSHIP);
        fuzzyElement if2(rule_to_add.RULE_SENSOR2, rule_to_add.RULE_SENSOR2_MEMBERSHIP);
        fuzzyElement if3(rule_to_add.RULE_SENSOR3, rule_to_add.RULE_SENSOR3_MEMBERSHIP); 
        fuzzyElement if4(rule_to_add.RULE_CAMARA,  rule_to_add.RULE_CAMARA_MEMBERSHIP);
        if_vector.push_back(if1);
        if_vector.push_back(if2);
        if_vector.push_back(if3);
        if_vector.push_back(if4);
        fuzzyRuleInput if_side(if_vector);

        std::vector <fuzzyElement> else_vector;
        fuzzyElement else1(rule_to_add.RULE_HEADING, rule_to_add.RULE_HEADING_MEMBERSHIP);
        fuzzyElement else2(rule_to_add.RULE_SPEED,   rule_to_add.RULE_SPEED_MEMBERSHIP);
        else_vector.push_back(else1);
        else_vector.push_back(else2);
        fuzzyRuleOutput else_side(else_vector);

        fuzzyRule rule(rule_to_add.NAME, if_side, else_side);
        rules.push_back(rule);
    }
    inputs.push_back(inputSensor1);
    inputs.push_back(inputSensor2);
    inputs.push_back(inputSensor3);
    inputs.push_back(inputCamera);
    outputs.push_back(outputSpeed);
    outputs.push_back(outputHeading);
    fuzzyControl myFuzzyControl(inputs, outputs, rules);

    signal(SIGQUIT, sigquitHandler);

    std::map<std::string, int> inputs_list { 
        {in_sensor1::NAME, 0},
        {in_sensor2::NAME, 0},
        {in_sensor3::NAME, 0},
        {in_ov7670::NAME,  0} };

    while(is_running) {
        gettimeofday(&begin, 0);

        vSensorData = myDistanceSensor.getDistances();
        myCommon.saveToState(vSensorData[0], common::dataType::Sensor1);
        myCommon.saveToState(vSensorData[1], common::dataType::Sensor2);
        myCommon.saveToState(vSensorData[2], common::dataType::Sensor3);

        inputs_list[in_sensor1::NAME] = vSensorData[0];
        inputs_list[in_sensor2::NAME] = vSensorData[1];
        inputs_list[in_sensor3::NAME] = vSensorData[2];
        inputs_list[in_ov7670::NAME] = 160;

        //std::cout << myCommon.readFromState(common::dataType::Sensor1) << std::endl;
        std::map<std::string, float> fuzzyResult = myFuzzyControl.updateInputs(inputs_list);

        DEBUG_PRINT(("fuzzyResult %f %f\n", fuzzyResult.at(out_heading::NAME), fuzzyResult.at(out_speed::NAME)));
        DEBUG_PRINT(("Elapsed: %f \n", elapsed));
        DEBUG_PRINT(("Sensores %d %d %d \n", vSensorData[0], vSensorData[1],  vSensorData[2]));
        
        // Stop measuring time and calculate the elapsed time
        gettimeofday(&end, 0);
        seconds = end.tv_sec - begin.tv_sec;
        microseconds = end.tv_usec - begin.tv_usec;
        elapsed = seconds + microseconds*1e-6;

        if ( (CONTROL_PERIOD-elapsed) < 0 )
            is_running = 0;
        sleep(CONTROL_PERIOD-(elapsed));
    }
    return 0;
}