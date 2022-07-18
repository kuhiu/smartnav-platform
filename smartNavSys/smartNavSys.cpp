#include <smartNavSys.hpp>
#include <rulesIA.hpp>

smartNavSys::smartNavSys() {
    std::vector<struct RULE> rulesDefinition;
    /* Fuzzy input 1 */
    fuzzyInput inputSensor1;
    fuzzyMembership membership1Sensor1;
    fuzzyMembership membership2Sensor1;
    std::vector<fuzzyMembership> membershipsSensor1;
    /* Fuzzy input 2 */
    fuzzyInput inputSensor2;
    fuzzyMembership membership1Sensor2;
    fuzzyMembership membership2Sensor2;
    std::vector<fuzzyMembership> membershipsSensor2;
    /* Fuzzy input 3 */
    fuzzyInput inputSensor3;
    fuzzyMembership membership1Sensor3;
    fuzzyMembership membership2Sensor3;
    std::vector<fuzzyMembership> membershipsSensor3;
    /* Fuzzy input 4 */
    fuzzyInput inputCamera;
    fuzzyMembership membership1Camera;
    fuzzyMembership membership2Camera;
    fuzzyMembership membership3Camera;
    std::vector<fuzzyMembership> membershipsCamera;
    /* Fuzzy output 1 */
    fuzzyOutput outputSpeed;
    fuzzyMembership membership1Speed;
    fuzzyMembership membership2Speed;
    fuzzyMembership membership3Speed;
    std::vector<fuzzyMembership> membershipsSpeed;
    /* Fuzzy output 2 */
    fuzzyOutput outputHeading;
    fuzzyMembership membership1Heading;
    fuzzyMembership membership2Heading;
    fuzzyMembership membership3Heading;
    std::vector<fuzzyMembership> membershipsHeading;
    /* io and rules */
    std::vector<fuzzyInput> inputs;
    std::vector<fuzzyOutput> outputs;
    std::vector<fuzzyRule> rules;

    /* ImgProc Initilization */
    __imgProc.initializer(  cv::Scalar( imgProc::__RED_UPER_MASK_H, 
                                        imgProc::__RED_UPER_MASK_S,
                                        imgProc::__RED_UPER_MASK_V ), 
                            cv::Scalar( imgProc::__RED_LOWER_MASK_H,
                                        imgProc::__RED_LOWER_MASK_S,
                                        imgProc::__RED_LOWER_MASK_V) );
    /* Create a vector of struct rule to take a easy way to add rules to the fuzzySystem */
    rulesDefinition.push_back(RULE23);
    rulesDefinition.push_back(RULE22);
    rulesDefinition.push_back(RULE21);
    rulesDefinition.push_back(RULE20);
    rulesDefinition.push_back(RULE19);
    rulesDefinition.push_back(RULE18);
    rulesDefinition.push_back(RULE17);
    rulesDefinition.push_back(RULE16);
    rulesDefinition.push_back(RULE15);
    rulesDefinition.push_back(RULE14);
    rulesDefinition.push_back(RULE13);
    rulesDefinition.push_back(RULE12);
    rulesDefinition.push_back(RULE11);
    rulesDefinition.push_back(RULE10);
    rulesDefinition.push_back(RULE9);
    rulesDefinition.push_back(RULE8);
    rulesDefinition.push_back(RULE7);
    rulesDefinition.push_back(RULE6);
    rulesDefinition.push_back(RULE5);
    rulesDefinition.push_back(RULE4);
    rulesDefinition.push_back(RULE3);
    rulesDefinition.push_back(RULE2);
    rulesDefinition.push_back(RULE1);
    rulesDefinition.push_back(RULE0);
    /* Create Fuzzy Input */
    membership1Sensor1.initializer( in_sensor1::membership1::MEMBERSHIP_LEJOS,
                                    in_sensor1::membership1::point1,
                                    in_sensor1::membership1::point2,
                                    in_sensor1::membership1::slope1,
                                    in_sensor1::membership1::slope2);
    membership2Sensor1.initializer( in_sensor1::membership2::MEMBERSHIP_CERCA,
                                    in_sensor1::membership2::point1,
                                    in_sensor1::membership2::point2,
                                    in_sensor1::membership2::slope1,
                                    in_sensor1::membership2::slope2);
    membershipsSensor1.push_back(membership1Sensor1);
    membershipsSensor1.push_back(membership2Sensor1);                                             
    inputSensor1.initializer(in_sensor1::NAME, membershipsSensor1);
    /* Create Fuzzy Input */
    membership1Sensor2.initializer( in_sensor2::membership1::MEMBERSHIP_LEJOS,
                                    in_sensor2::membership1::point1,
                                    in_sensor2::membership1::point2,
                                    in_sensor2::membership1::slope1,
                                    in_sensor2::membership1::slope2) ;
    membership2Sensor2.initializer( in_sensor2::membership2::MEMBERSHIP_CERCA,
                                    in_sensor2::membership2::point1,
                                    in_sensor2::membership2::point2,
                                    in_sensor2::membership2::slope1,
                                    in_sensor2::membership2::slope2) ;                                             
    membershipsSensor2.push_back(membership1Sensor2);
    membershipsSensor2.push_back(membership2Sensor2);     
    inputSensor2.initializer(in_sensor2::NAME, membershipsSensor2);
    /* Create Fuzzy Input */
    membership1Sensor3.initializer( in_sensor3::membership1::MEMBERSHIP_LEJOS,
                                    in_sensor3::membership1::point1,
                                    in_sensor3::membership1::point2,
                                    in_sensor3::membership1::slope1,
                                    in_sensor3::membership1::slope2);
    membership2Sensor3.initializer( in_sensor3::membership2::MEMBERSHIP_CERCA,
                                    in_sensor3::membership2::point1,
                                    in_sensor3::membership2::point2,
                                    in_sensor3::membership2::slope1,
                                    in_sensor3::membership2::slope2);                                             
    membershipsSensor3.push_back(membership1Sensor3);
    membershipsSensor3.push_back(membership2Sensor3);     
    inputSensor3.initializer(in_sensor3::NAME, membershipsSensor3);
    /* Create Fuzzy Input */
    membership1Camera.initializer(  in_ov7670::membership1::MEMBERSHIP_DERECHA,
                                    in_ov7670::membership1::point1,
                                    in_ov7670::membership1::point2,
                                    in_ov7670::membership1::slope1,
                                    in_ov7670::membership1::slope2);
    membership2Camera.initializer(  in_ov7670::membership2::MEMBERSHIP_CENTRO,
                                    in_ov7670::membership2::point1,
                                    in_ov7670::membership2::point2,
                                    in_ov7670::membership2::slope1,
                                    in_ov7670::membership2::slope2);  
    membership3Camera.initializer(  in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
                                    in_ov7670::membership3::point1,
                                    in_ov7670::membership3::point2,
                                    in_ov7670::membership3::slope1,
                                    in_ov7670::membership3::slope2); 
    membershipsCamera.push_back(membership1Camera);  
    membershipsCamera.push_back(membership2Camera);  
    membershipsCamera.push_back(membership3Camera);                                            
    inputCamera.initializer(in_ov7670::NAME, membershipsCamera);
    /* Create Fuzzy output */
    membership1Speed.initializer(   out_speed::membership1::MEMBERSHIP_AUMENTAR,
                                    out_speed::membership1::point1,
                                    out_speed::membership1::point2,
                                    out_speed::membership1::slope1,
                                    out_speed::membership1::slope2);
    membership2Speed.initializer(   out_speed::membership2::MEMBERSHIP_MANTENER,
                                    out_speed::membership2::point1,
                                    out_speed::membership2::point2,
                                    out_speed::membership2::slope1,
                                    out_speed::membership2::slope2);  
    membership3Speed.initializer(   out_speed::membership3::MEMBERSHIP_REDUCIR,
                                    out_speed::membership3::point1,
                                    out_speed::membership3::point2,
                                    out_speed::membership3::slope1,
                                    out_speed::membership3::slope2);   
    membershipsSpeed.push_back(membership1Speed);  
    membershipsSpeed.push_back(membership2Speed);  
    membershipsSpeed.push_back(membership3Speed);                                                                                     
    outputSpeed.initializer(out_speed::NAME, membershipsSpeed);
    // /* Create Fuzzy output */
    membership1Heading.initializer( out_heading::membership1::MEMBERSHIP_DERECHA,
                                    out_heading::membership1::point1,
                                    out_heading::membership1::point2,
                                    out_heading::membership1::slope1,
                                    out_heading::membership1::slope2);
    membership2Heading.initializer( out_heading::membership2::MEMBERSHIP_CENTRO,
                                    out_heading::membership2::point1,
                                    out_heading::membership2::point2,
                                    out_heading::membership2::slope1,
                                    out_heading::membership2::slope2);  
    membership3Heading.initializer( out_heading::membership3::MEMBERSHIP_IZQUIERDA,
                                    out_heading::membership3::point1,
                                    out_heading::membership3::point2,
                                    out_heading::membership3::slope1,
                                    out_heading::membership3::slope2); 
    membershipsHeading.push_back(membership1Heading);  
    membershipsHeading.push_back(membership2Heading);  
    membershipsHeading.push_back(membership3Heading);                                                                                                                              
    outputHeading.initializer(out_heading::NAME, membershipsHeading);
    /* Add RULES */
    for ( auto rule_to_add : rulesDefinition) {
        fuzzyElement if1; 
        fuzzyElement if2;
        fuzzyElement if3;
        fuzzyElement if4;
        fuzzyElement else1;
        fuzzyElement else2;
        fuzzyRuleInput if_side;
        fuzzyRuleOutput else_side;
        std::vector <fuzzyElement> if_vector;
        std::vector <fuzzyElement> else_vector;
        fuzzyRule rule;
        /* If side of rule */
        if1.initializer(rule_to_add.RULE_SENSOR1, rule_to_add.RULE_SENSOR1_MEMBERSHIP);
        if2.initializer(rule_to_add.RULE_SENSOR2, rule_to_add.RULE_SENSOR2_MEMBERSHIP);
        if3.initializer(rule_to_add.RULE_SENSOR3, rule_to_add.RULE_SENSOR3_MEMBERSHIP); 
        if4.initializer(rule_to_add.RULE_CAMARA,  rule_to_add.RULE_CAMARA_MEMBERSHIP);
        if_vector.push_back(if1);
        if_vector.push_back(if2);
        if_vector.push_back(if3);
        if_vector.push_back(if4);
        if_side.initializer(if_vector);
        /* Else side of rule */
        else1.initializer(rule_to_add.RULE_HEADING, rule_to_add.RULE_HEADING_MEMBERSHIP);
        else2.initializer(rule_to_add.RULE_SPEED,   rule_to_add.RULE_SPEED_MEMBERSHIP);
        else_vector.push_back(else1);
        else_vector.push_back(else2);
        else_side.initializer(else_vector);
        /* Create and add rule */
        rule.initializer(rule_to_add.NAME, if_side, else_side);
        rules.push_back(rule);
    }
    inputs.push_back(inputSensor1);
    inputs.push_back(inputSensor2);
    inputs.push_back(inputSensor3);
    inputs.push_back(inputCamera);
    outputs.push_back(outputSpeed);
    outputs.push_back(outputHeading);

    __fuzzyControl.initializer(inputs, outputs, rules);

    __fuzzyInputsMap = {{in_sensor1::NAME, 0},
                        {in_sensor2::NAME, 0},
                        {in_sensor3::NAME, 0},
                        {in_ov7670::NAME,  0}};

    __driverInputsMap = {{out_heading::NAME, 0},
                         {out_speed::NAME, 0},
                         {in_ov7670::NAME, 0}};
}

void smartNavSys::run(void) {
    /* Run distance sensors */
    __sensorData = __distanceSensor.getDistances();

    /* Run fuzzy system */
    __fuzzyInputsMap[in_sensor1::NAME] = __sensorData[0];
    __fuzzyInputsMap[in_sensor2::NAME] = __sensorData[1];
    __fuzzyInputsMap[in_sensor3::NAME] = __sensorData[2];
    __fuzzyInputsMap[in_ov7670::NAME] = __imgProc.updateInput();
    std::map<std::string, float> fuzzyResult = __fuzzyControl.updateInputs(__fuzzyInputsMap);

    /* Run driver */
    __driverInputsMap[out_heading::NAME] = fuzzyResult[out_heading::NAME]; 
    __driverInputsMap[out_speed::NAME] = fuzzyResult[out_speed::NAME]; 
    __driverInputsMap[in_ov7670::NAME] = __fuzzyInputsMap[in_ov7670::NAME]; 
    __driver.drive(__driverInputsMap);

    /* Debug */
    DEBUG_PRINT(("smartNavSys:: imgProc output %d\n", __fuzzyInputsMap[in_ov7670::NAME]));
    DEBUG_PRINT(("smartNavSys:: fuzzyResult %f %f\n", fuzzyResult.at(out_heading::NAME), fuzzyResult.at(out_speed::NAME)));
    DEBUG_PRINT(("smartNavSys:: sensores %d %d %d \n", __sensorData[0], __sensorData[1],  __sensorData[2]));
}