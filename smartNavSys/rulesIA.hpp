#ifndef __RULES_H__
#define __RULES_H__

#include  <ioConfig.hpp>
#include <string>

struct RULE {
    const std::string NAME;
    const std::string RULE_SENSOR1;
    const std::string RULE_SENSOR1_MEMBERSHIP;
    const std::string RULE_SENSOR2;
    const std::string RULE_SENSOR2_MEMBERSHIP;
    const std::string RULE_SENSOR3;
    const std::string RULE_SENSOR3_MEMBERSHIP;
    const std::string RULE_CAMARA;
    const std::string RULE_CAMARA_MEMBERSHIP;
    const std::string RULE_SPEED;
    const std::string RULE_SPEED_MEMBERSHIP;
    const std::string RULE_HEADING;
    const std::string RULE_HEADING_MEMBERSHIP;
};

RULE RULE23 {   
    "RULE23",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership1::MEMBERSHIP_DERECHA,
    out_speed::NAME,
    out_speed::membership1::MEMBERSHIP_AUMENTAR,
    out_heading::NAME,
    out_heading::membership1::MEMBERSHIP_DERECHA};  

RULE RULE22 {
    "RULE22",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership2::MEMBERSHIP_CENTRO,
    out_speed::NAME,
    out_speed::membership1::MEMBERSHIP_AUMENTAR,
    out_heading::NAME,
    out_heading::membership2::MEMBERSHIP_CENTRO};

RULE RULE21 {
    "RULE21",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
    out_speed::NAME,
    out_speed::membership1::MEMBERSHIP_AUMENTAR,
    out_heading::NAME,
    out_heading::membership3::MEMBERSHIP_IZQUIERDA};

RULE RULE20 {
    "RULE20",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership1::MEMBERSHIP_DERECHA,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership1::MEMBERSHIP_DERECHA};

RULE RULE19 {
    "RULE19",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,  
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership2::MEMBERSHIP_CENTRO,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership2::MEMBERSHIP_CENTRO};

RULE RULE18 {
    "RULE18",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership3::MEMBERSHIP_IZQUIERDA};

RULE RULE17 {
    "RULE17",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership1::MEMBERSHIP_DERECHA,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership1::MEMBERSHIP_DERECHA};

RULE RULE16 {
    "RULE16",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership2::MEMBERSHIP_CENTRO,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership2::MEMBERSHIP_CENTRO};

RULE RULE15 {
    "RULE15",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership3::MEMBERSHIP_IZQUIERDA};

RULE RULE14 {
    "RULE14",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership1::MEMBERSHIP_DERECHA,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership1::MEMBERSHIP_DERECHA};

RULE RULE13 {
    "RULE13",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership2::MEMBERSHIP_CENTRO,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership2::MEMBERSHIP_CENTRO};

RULE RULE12 {
    "RULE12",
    in_sensor1::NAME,
    in_sensor1::membership1::MEMBERSHIP_LEJOS,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership3::MEMBERSHIP_IZQUIERDA};

RULE RULE11 {
    "RULE11",
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership1::MEMBERSHIP_DERECHA,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership1::MEMBERSHIP_DERECHA};

RULE RULE10 {
    "RULE10",
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership2::MEMBERSHIP_CENTRO,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership2::MEMBERSHIP_CENTRO};

RULE RULE9 {
    "RULE9",
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership3::MEMBERSHIP_IZQUIERDA};

RULE RULE8 {
    "RULE8",        
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership1::MEMBERSHIP_DERECHA,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership1::MEMBERSHIP_DERECHA};

RULE RULE7 {
    "RULE7",        
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership2::MEMBERSHIP_CENTRO,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership2::MEMBERSHIP_CENTRO};

RULE RULE6 {
    "RULE6",
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership1::MEMBERSHIP_LEJOS,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
    out_speed::NAME,
    out_speed::membership2::MEMBERSHIP_MANTENER,
    out_heading::NAME,
    out_heading::membership3::MEMBERSHIP_IZQUIERDA};

RULE RULE5 {
    "RULE5",        
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership1::MEMBERSHIP_DERECHA,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership1::MEMBERSHIP_DERECHA};

RULE RULE4 {
    "RULE4",        
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership2::MEMBERSHIP_CENTRO,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership2::MEMBERSHIP_CENTRO};

RULE RULE3 {
    "RULE3",        
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership1::MEMBERSHIP_LEJOS,
    in_ov7670::NAME,
    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership3::MEMBERSHIP_IZQUIERDA};

RULE RULE2 {
    "RULE2",
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership1::MEMBERSHIP_DERECHA,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership1::MEMBERSHIP_DERECHA};

RULE RULE1 {
    "RULE1",
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership2::MEMBERSHIP_CENTRO,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership2::MEMBERSHIP_CENTRO};

RULE RULE0 {
    "RULE0",        
    in_sensor1::NAME,
    in_sensor1::membership2::MEMBERSHIP_CERCA,
    in_sensor2::NAME,
    in_sensor2::membership2::MEMBERSHIP_CERCA,
    in_sensor3::NAME,
    in_sensor3::membership2::MEMBERSHIP_CERCA,
    in_ov7670::NAME,
    in_ov7670::membership3::MEMBERSHIP_IZQUIERDA,
    out_speed::NAME,
    out_speed::membership3::MEMBERSHIP_REDUCIR,
    out_heading::NAME,
    out_heading::membership3::MEMBERSHIP_IZQUIERDA};

#endif // __RULES_H__