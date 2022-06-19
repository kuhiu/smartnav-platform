#include "fun.h"

int main(void)
{
    // File
    FILE* fdd_State;

    // Semaforo
    key_t key;              
    int semid, fdp;
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1; /* set to allocate resource */
    sb.sem_flg = SEM_UNDO;

    // System inputs                                      System_Inputs_leftSensor -> System_Inputs_centerSensor -> System_Inputs_rightSensor
    struct io_type *System_Inputs_leftSensor   = NULL;
    struct io_type *System_Inputs_centerSensor = NULL;
    struct io_type *System_Inputs_rightSensor  = NULL;
    struct io_type *System_Inputs_ImgProc      = NULL;

    // System outputs
    struct io_type *System_Outputs_ang   = NULL;
    struct io_type *System_Outputs_speed = NULL;

    // ENTRADAS: Funciones de pertenencias de sensores de distancia 
    struct mf_type *membership_functions_inputs_cerca_right  = NULL;  
    struct mf_type *membership_functions_inputs_lejos_right  = NULL;

    struct mf_type *membership_functions_inputs_cerca_center = NULL;  
    struct mf_type *membership_functions_inputs_lejos_center = NULL; 

    struct mf_type *membership_functions_inputs_cerca_left   = NULL;  
    struct mf_type *membership_functions_inputs_lejos_left   = NULL; 

    // ENTRADAS: Funciones de pertenencias de la etapa de procesamiento de imagenes
    struct mf_type *membership_functions_inputs_left_imgproc   = NULL;
    struct mf_type *membership_functions_inputs_center_imgproc = NULL;
    struct mf_type *membership_functions_inputs_right_imgproc  = NULL;

    // SALIDAS: Funciones de pertenencia de la direccion 
    struct mf_type *membership_functions_outputs_goLeft      = NULL;
    struct mf_type *membership_functions_outputs_goRight     = NULL;
    struct mf_type *membership_functions_outputs_goCenter    = NULL;

    // SALIDAS: Funciones de pertenencia de la velocidad 
    struct mf_type *membership_functions_outputs_high_speed   = NULL;
    struct mf_type *membership_functions_outputs_normal_speed = NULL;
    struct mf_type *membership_functions_outputs_low_speed    = NULL;

    //////////////////////////////////////////////// Reglas
    //////////////////////////////////////////////// leftSensor, centerSensor, rightSensor
    struct rule_type         *rule_0            = NULL;                  
    struct rule_element_type *if_side_0_left    = NULL;
    struct rule_element_type *if_side_0_right   = NULL;
    struct rule_element_type *if_side_0_center  = NULL;
    struct rule_element_type *if_side_0_imgproc = NULL;
    struct rule_element_type *then_side_0_dirr  = NULL; 
    struct rule_element_type *then_side_0_speed = NULL;

    struct rule_type         *rule_1            = NULL;
    struct rule_element_type *if_side_1_left    = NULL;
    struct rule_element_type *if_side_1_right   = NULL; 
    struct rule_element_type *if_side_1_center  = NULL;
    struct rule_element_type *if_side_1_imgproc = NULL;
    struct rule_element_type *then_side_1_dirr  = NULL;
    struct rule_element_type *then_side_1_speed = NULL;

    struct rule_type         *rule_2            = NULL;
    struct rule_element_type *if_side_2_left    = NULL;
    struct rule_element_type *if_side_2_right   = NULL; 
    struct rule_element_type *if_side_2_center  = NULL;
    struct rule_element_type *if_side_2_imgproc = NULL;
    struct rule_element_type *then_side_2_dirr  = NULL; 
    struct rule_element_type *then_side_2_speed = NULL;

    struct rule_type         *rule_3            = NULL;
    struct rule_element_type *if_side_3_left    = NULL;
    struct rule_element_type *if_side_3_right   = NULL; 
    struct rule_element_type *if_side_3_center  = NULL;
    struct rule_element_type *if_side_3_imgproc = NULL;
    struct rule_element_type *then_side_3_dirr  = NULL;
    struct rule_element_type *then_side_3_speed = NULL;

    struct rule_type         *rule_4            = NULL;
    struct rule_element_type *if_side_4_left    = NULL;
    struct rule_element_type *if_side_4_right   = NULL; 
    struct rule_element_type *if_side_4_center  = NULL;
    struct rule_element_type *if_side_4_imgproc = NULL;
    struct rule_element_type *then_side_4_dirr  = NULL; 
    struct rule_element_type *then_side_4_speed = NULL;

    struct rule_type         *rule_5            = NULL;
    struct rule_element_type *if_side_5_left    = NULL;
    struct rule_element_type *if_side_5_right   = NULL; 
    struct rule_element_type *if_side_5_center  = NULL;
    struct rule_element_type *if_side_5_imgproc = NULL;
    struct rule_element_type *then_side_5_dirr  = NULL; 
    struct rule_element_type *then_side_5_speed = NULL;

    struct rule_type         *rule_6            = NULL;
    struct rule_element_type *if_side_6_left    = NULL;
    struct rule_element_type *if_side_6_right   = NULL; 
    struct rule_element_type *if_side_6_center  = NULL;
    struct rule_element_type *if_side_6_imgproc = NULL;
    struct rule_element_type *then_side_6_dirr  = NULL; 
    struct rule_element_type *then_side_6_speed = NULL;

    struct rule_type         *rule_7            = NULL;
    struct rule_element_type *if_side_7_left    = NULL;
    struct rule_element_type *if_side_7_right   = NULL; 
    struct rule_element_type *if_side_7_center  = NULL;
    struct rule_element_type *if_side_7_imgproc = NULL;
    struct rule_element_type *then_side_7_dirr  = NULL; 
    struct rule_element_type *then_side_7_speed = NULL;

    struct rule_type         *rule_8            = NULL;
    struct rule_element_type *if_side_8_left    = NULL;
    struct rule_element_type *if_side_8_right   = NULL; 
    struct rule_element_type *if_side_8_center  = NULL;
    struct rule_element_type *if_side_8_imgproc = NULL;
    struct rule_element_type *then_side_8_dirr  = NULL; 
    struct rule_element_type *then_side_8_speed = NULL;

    struct rule_type         *rule_9            = NULL;
    struct rule_element_type *if_side_9_left    = NULL;
    struct rule_element_type *if_side_9_right   = NULL; 
    struct rule_element_type *if_side_9_center  = NULL;
    struct rule_element_type *if_side_9_imgproc = NULL;
    struct rule_element_type *then_side_9_dirr  = NULL; 
    struct rule_element_type *then_side_9_speed = NULL;

    struct rule_type         *rule_10             = NULL;
    struct rule_element_type *if_side_10_left     = NULL;
    struct rule_element_type *if_side_10_right    = NULL; 
    struct rule_element_type *if_side_10_center   = NULL;
    struct rule_element_type *if_side_10_imgproc  = NULL;
    struct rule_element_type *then_side_10_dirr   = NULL; 
    struct rule_element_type *then_side_10_speed  = NULL;

    struct rule_type         *rule_11             = NULL;
    struct rule_element_type *if_side_11_left     = NULL;
    struct rule_element_type *if_side_11_right    = NULL; 
    struct rule_element_type *if_side_11_center   = NULL;
    struct rule_element_type *if_side_11_imgproc  = NULL;
    struct rule_element_type *then_side_11_dirr   = NULL; 
    struct rule_element_type *then_side_11_speed  = NULL;

    struct rule_type         *rule_12             = NULL;
    struct rule_element_type *if_side_12_left     = NULL;
    struct rule_element_type *if_side_12_right    = NULL; 
    struct rule_element_type *if_side_12_center   = NULL;
    struct rule_element_type *if_side_12_imgproc  = NULL;
    struct rule_element_type *then_side_12_dirr   = NULL;
    struct rule_element_type *then_side_12_speed  = NULL; 

    struct rule_type         *rule_13             = NULL;
    struct rule_element_type *if_side_13_left     = NULL;
    struct rule_element_type *if_side_13_right    = NULL; 
    struct rule_element_type *if_side_13_center   = NULL;
    struct rule_element_type *if_side_13_imgproc  = NULL;
    struct rule_element_type *then_side_13_dirr   = NULL; 
    struct rule_element_type *then_side_13_speed  = NULL;

    struct rule_type         *rule_14             = NULL;
    struct rule_element_type *if_side_14_left     = NULL;
    struct rule_element_type *if_side_14_right    = NULL; 
    struct rule_element_type *if_side_14_center   = NULL;
    struct rule_element_type *if_side_14_imgproc  = NULL;
    struct rule_element_type *then_side_14_dirr   = NULL; 
    struct rule_element_type *then_side_14_speed  = NULL;

    struct rule_type         *rule_15             = NULL;
    struct rule_element_type *if_side_15_left     = NULL;
    struct rule_element_type *if_side_15_right    = NULL; 
    struct rule_element_type *if_side_15_center   = NULL;
    struct rule_element_type *if_side_15_imgproc  = NULL;
    struct rule_element_type *then_side_15_dirr   = NULL; 
    struct rule_element_type *then_side_15_speed  = NULL;

    struct rule_type         *rule_16             = NULL;
    struct rule_element_type *if_side_16_left     = NULL;
    struct rule_element_type *if_side_16_right    = NULL; 
    struct rule_element_type *if_side_16_center   = NULL;
    struct rule_element_type *if_side_16_imgproc  = NULL;
    struct rule_element_type *then_side_16_dirr   = NULL; 
    struct rule_element_type *then_side_16_speed  = NULL;

    struct rule_type         *rule_17             = NULL;
    struct rule_element_type *if_side_17_left     = NULL;
    struct rule_element_type *if_side_17_right    = NULL; 
    struct rule_element_type *if_side_17_center   = NULL;
    struct rule_element_type *if_side_17_imgproc  = NULL;
    struct rule_element_type *then_side_17_dirr   = NULL; 
    struct rule_element_type *then_side_17_speed  = NULL;

    struct rule_type         *rule_18             = NULL;
    struct rule_element_type *if_side_18_left     = NULL;
    struct rule_element_type *if_side_18_right    = NULL; 
    struct rule_element_type *if_side_18_center   = NULL;
    struct rule_element_type *if_side_18_imgproc  = NULL;
    struct rule_element_type *then_side_18_dirr   = NULL; 
    struct rule_element_type *then_side_18_speed  = NULL;

    struct rule_type         *rule_19             = NULL;
    struct rule_element_type *if_side_19_left     = NULL;
    struct rule_element_type *if_side_19_right    = NULL; 
    struct rule_element_type *if_side_19_center   = NULL;
    struct rule_element_type *if_side_19_imgproc  = NULL;
    struct rule_element_type *then_side_19_dirr   = NULL;
    struct rule_element_type *then_side_19_speed  = NULL; 

    struct rule_type         *rule_20             = NULL;
    struct rule_element_type *if_side_20_left     = NULL;
    struct rule_element_type *if_side_20_right    = NULL; 
    struct rule_element_type *if_side_20_center   = NULL;
    struct rule_element_type *if_side_20_imgproc  = NULL;
    struct rule_element_type *then_side_20_dirr   = NULL; 
    struct rule_element_type *then_side_20_speed  = NULL;

    struct rule_type         *rule_21             = NULL;
    struct rule_element_type *if_side_21_left     = NULL;
    struct rule_element_type *if_side_21_right    = NULL; 
    struct rule_element_type *if_side_21_center   = NULL;
    struct rule_element_type *if_side_21_imgproc  = NULL;
    struct rule_element_type *then_side_21_dirr   = NULL; 
    struct rule_element_type *then_side_21_speed  = NULL;

    struct rule_type         *rule_22             = NULL;
    struct rule_element_type *if_side_22_left     = NULL;
    struct rule_element_type *if_side_22_right    = NULL; 
    struct rule_element_type *if_side_22_center   = NULL;
    struct rule_element_type *if_side_22_imgproc  = NULL;
    struct rule_element_type *then_side_22_dirr   = NULL; 
    struct rule_element_type *then_side_22_speed  = NULL;

    struct rule_type         *rule_23             = NULL;
    struct rule_element_type *if_side_23_left     = NULL;
    struct rule_element_type *if_side_23_right    = NULL; 
    struct rule_element_type *if_side_23_center   = NULL;
    struct rule_element_type *if_side_23_imgproc  = NULL;
    struct rule_element_type *then_side_23_dirr   = NULL; 
    struct rule_element_type *then_side_23_speed  = NULL;

    long long int rightSensor, centerSensor, leftSensor, dir_imgproc;

    float *rightSensor_membership_functions_value_lejos, *rightSensor_membership_functions_value_cerca;
    float *leftSensor_membership_functions_value_lejos, *leftSensor_membership_functions_value_cerca;
    float *centerSensor_membership_functions_value_lejos, *centerSensor_membership_functions_value_cerca;
    float *cameraSensor_membership_functions_value_left, *cameraSensor_membership_functions_value_center, *cameraSensor_membership_functions_value_right; 

    float *ang_membership_functions_value_left, *ang_membership_functions_value_right, *ang_membership_functions_value_center;
    float *speed_membership_functions_value_slow, *speed_membership_functions_value_normal, *speed_membership_functions_value_fast;  

    char recurso[50], img_proc_tipo[30];

    float *faux;

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
    //////////////////////////////////////   State TXT  //////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    if ( (fdd_State = fopen("state.txt", "r+")) == NULL){
        printf("Error abriendo state.txt\n");
        return -1;
    }

    // Cargo las funciones de pertenencias 
    // Funciones de pertenencia para rightSensor
    initialize_membership_inputs("Lejos", 0,   30,  940, (float)1/30, (float)1/30, NULL, &membership_functions_inputs_lejos_right);
    initialize_membership_inputs("Cerca", 0,  -60,   60, (float)1/30, (float)1/30, membership_functions_inputs_lejos_right, &membership_functions_inputs_cerca_right);

    // Funciones de pertenencia para centerSensor
    initialize_membership_inputs("Lejos", 0,  30,  940,  (float)1/30, (float)1/30, NULL, &membership_functions_inputs_lejos_center);
    initialize_membership_inputs("Cerca", 0, -60,   60,  (float)1/30, (float)1/30, membership_functions_inputs_lejos_center, &membership_functions_inputs_cerca_center);

    // Funciones de pertenencia para leftSensor
    initialize_membership_inputs("Lejos", 0,    30,   940,  (float)1/30, (float)1/30, NULL, &membership_functions_inputs_lejos_left);
    initialize_membership_inputs("Cerca", 0,   -60,   60,  (float)1/30, (float)1/30, membership_functions_inputs_lejos_left, &membership_functions_inputs_cerca_left);

    // Funciones de pertenencia para imgproc
    initialize_membership_inputs("Derecha",   0,  160, 480,  (float)1/160, (float)1/160, NULL, &membership_functions_inputs_right_imgproc);
    initialize_membership_inputs("Centro",    0,    0, 320,  (float)1/160, (float)1/160, membership_functions_inputs_right_imgproc, &membership_functions_inputs_center_imgproc);
    initialize_membership_inputs("Izquierda", 0, -160, 160,  (float)1/160, (float)1/160, membership_functions_inputs_center_imgproc, &membership_functions_inputs_left_imgproc);

    // Outputs
    initialize_membership_inputs("high_speed",     0,  0.3, 0.5, (float)1/0.1, (float)1/0.1, NULL, &membership_functions_outputs_high_speed);
    initialize_membership_inputs("normal_speed", 0,  0.2, 0.4, (float)1/0.1, (float)1/0.1, membership_functions_outputs_high_speed, &membership_functions_outputs_normal_speed);
    initialize_membership_inputs("low_speed",      0,  0.1, 0.3, (float)1/0.1, (float)1/0.1, membership_functions_outputs_normal_speed, &membership_functions_outputs_low_speed);

    initialize_membership_inputs("goRight",  0,    0,  90, (float)1/45, (float)1/45, NULL, &membership_functions_outputs_goRight);
    initialize_membership_inputs("goCenter", 0,  -45,  45, (float)1/45, (float)1/45, membership_functions_outputs_goRight, &membership_functions_outputs_goCenter);
    initialize_membership_inputs("goLeft",   0,  -90,   0, (float)1/45, (float)1/45, membership_functions_outputs_goCenter, &membership_functions_outputs_goLeft);

    // Cargo las estructuras de las Entradas 
    System_Inputs_ImgProc   = initialize_system_io("ImgProc", 0, membership_functions_inputs_left_imgproc, NULL);
    if (System_Inputs_ImgProc == NULL)
        return -1;

    System_Inputs_rightSensor  = initialize_system_io("Right", 0, membership_functions_inputs_cerca_right, System_Inputs_ImgProc);
    if (System_Inputs_rightSensor == NULL)
        return -1;

    System_Inputs_centerSensor = initialize_system_io("Center", 0, membership_functions_inputs_cerca_center, System_Inputs_rightSensor);
    if (System_Inputs_centerSensor == NULL)
        return -1;

    System_Inputs_leftSensor   = initialize_system_io("Left", 0, membership_functions_inputs_cerca_left, System_Inputs_centerSensor);
    if (System_Inputs_leftSensor == NULL)
        return -1;

    // Cargo las estructuras de las Salidas
    System_Outputs_speed = initialize_system_io("Speed", 0, membership_functions_outputs_low_speed, NULL);
    if (System_Outputs_speed == NULL)
        return -1; 

    System_Outputs_ang = initialize_system_io("Angulo", 0, membership_functions_outputs_goLeft, System_Outputs_speed);
    if (System_Outputs_ang == NULL)
        return -1;

    // Rules
    rightSensor_membership_functions_value_lejos = &(System_Inputs_rightSensor -> membership_functions->next->value);
    rightSensor_membership_functions_value_cerca = &(System_Inputs_rightSensor -> membership_functions->value);

    centerSensor_membership_functions_value_lejos = &(System_Inputs_centerSensor -> membership_functions->next->value);
    centerSensor_membership_functions_value_cerca = &(System_Inputs_centerSensor -> membership_functions->value);

    leftSensor_membership_functions_value_lejos = &(System_Inputs_leftSensor -> membership_functions->next->value);
    leftSensor_membership_functions_value_cerca = &(System_Inputs_leftSensor -> membership_functions->value);

    cameraSensor_membership_functions_value_left    = &(System_Inputs_ImgProc -> membership_functions->value); 
    cameraSensor_membership_functions_value_center  = &(System_Inputs_ImgProc -> membership_functions->next->value); 
    cameraSensor_membership_functions_value_right   = &(System_Inputs_ImgProc -> membership_functions->next->next->value);

    ang_membership_functions_value_left   = &(System_Outputs_ang -> membership_functions->value);
    ang_membership_functions_value_center = &(System_Outputs_ang -> membership_functions->next->value);
    ang_membership_functions_value_right  = &(System_Outputs_ang -> membership_functions->next->next->value);

    speed_membership_functions_value_slow   = &(System_Outputs_speed -> membership_functions->value);
    speed_membership_functions_value_normal = &(System_Outputs_speed -> membership_functions->next->value);
    speed_membership_functions_value_fast   = &(System_Outputs_speed -> membership_functions->next->next->value);

    // Rule 23
    charge_rule( "LEJOS, LEJOS, LEJOS, Img_Proc_IZQUIERDA = IZQUIERDA, S_RAPIDA", 
                &if_side_23_right, &if_side_23_center, &if_side_23_left, &if_side_23_imgproc,
                &then_side_23_dirr, &then_side_23_speed, 
                &rule_23, NULL);
    if_side_23_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_23_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_23_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_23_imgproc -> value = cameraSensor_membership_functions_value_left;
    then_side_23_dirr  -> value = ang_membership_functions_value_left;
    then_side_23_speed -> value = speed_membership_functions_value_fast;

    // Rule 22
    charge_rule( "LEJOS, LEJOS, LEJOS, Img_Proc_DERECHA = DERECHA, S_RAPIDA", 
                &if_side_22_right, &if_side_22_center, &if_side_22_left, &if_side_22_imgproc,
                &then_side_22_dirr, &then_side_22_speed, 
                &rule_22, rule_23);
    if_side_22_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_22_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_22_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_22_imgproc -> value = cameraSensor_membership_functions_value_right;
    then_side_22_dirr  -> value = ang_membership_functions_value_right;
    then_side_22_speed -> value = speed_membership_functions_value_fast;

    // Rule 21
    charge_rule( "LEJOS, LEJOS, LEJOS, Img_Proc_CENTRO = CENTRO, S_RAPIDA",
                &if_side_21_right, &if_side_21_center, &if_side_21_left, &if_side_21_imgproc,
                &then_side_21_dirr, &then_side_21_speed,
                &rule_21, rule_22);
    if_side_21_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_21_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_21_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_21_imgproc -> value = cameraSensor_membership_functions_value_center;
    then_side_21_dirr  -> value = ang_membership_functions_value_center;
    then_side_21_speed -> value = speed_membership_functions_value_fast;

    // Rule 20
    charge_rule( "LEJOS, LEJOS, CERCA, Img_Proc_IZQUIERDA = IZQUIERDA, S_LENTA",
                &if_side_20_right, &if_side_20_center, &if_side_20_left, &if_side_20_imgproc,
                &then_side_20_dirr, &then_side_20_speed, 
                &rule_20, rule_21);
    if_side_20_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_20_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_20_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_20_imgproc -> value = cameraSensor_membership_functions_value_left;
    then_side_20_dirr  -> value = ang_membership_functions_value_left;
    then_side_20_speed -> value = speed_membership_functions_value_slow;

    // Rule 19
    charge_rule( "LEJOS, LEJOS, CERCA, Img_Proc_DERECHA = DERECHA, S_LENTA", 
                &if_side_19_right, &if_side_19_center, &if_side_19_left, &if_side_19_imgproc,
                &then_side_19_dirr, &then_side_19_speed, 
                &rule_19, rule_20);
    if_side_19_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_19_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_19_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_19_imgproc -> value = cameraSensor_membership_functions_value_right;
    then_side_19_dirr  -> value = ang_membership_functions_value_right;
    then_side_19_speed -> value = speed_membership_functions_value_slow;

    // Rule 18
    charge_rule( "LEJOS, LEJOS, CERCA, Img_Proc_CENTRO = CENTRO, S_LENTA", 
                &if_side_18_right, &if_side_18_center, &if_side_18_left, &if_side_18_imgproc,
                &then_side_18_dirr, &then_side_18_speed, 
                &rule_18, rule_19);
    if_side_18_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_18_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_18_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_18_imgproc -> value = cameraSensor_membership_functions_value_center;
    then_side_18_dirr  -> value = ang_membership_functions_value_center;
    then_side_18_speed -> value = speed_membership_functions_value_slow;

    // Rule 17
    charge_rule( "LEJOS, CERCA, LEJOS, Img_Proc_IZQUIERDA = IZQUIERDA, S_LENTA",
                &if_side_17_right, &if_side_17_center, &if_side_17_left, &if_side_17_imgproc,
                &then_side_17_dirr, &then_side_17_speed, 
                &rule_17, rule_18);
    if_side_17_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_17_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_17_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_17_imgproc -> value = cameraSensor_membership_functions_value_left;
    then_side_17_dirr  -> value = ang_membership_functions_value_left;
    then_side_17_speed -> value = speed_membership_functions_value_slow;

    // Rule 16
    charge_rule( "LEJOS, CERCA, LEJOS, Img_Proc_DERECHA = DERECHA, S_LENTA", 
                &if_side_16_right, &if_side_16_center, &if_side_16_left, &if_side_16_imgproc,
                &then_side_16_dirr, &then_side_16_speed, 
                &rule_16, rule_17);
    if_side_16_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_16_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_16_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_16_imgproc -> value = cameraSensor_membership_functions_value_right;
    then_side_16_dirr  -> value = ang_membership_functions_value_right;
    then_side_16_speed -> value = speed_membership_functions_value_slow;

    // Rule 15
    charge_rule( "LEJOS, CERCA, LEJOS, Img_Proc_CENTRO = CENTRO, S_ZERO",
                &if_side_15_right, &if_side_15_center, &if_side_15_left, &if_side_15_imgproc,
                &then_side_15_dirr, &then_side_15_speed,  
                &rule_15, rule_16);
    if_side_15_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_15_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_15_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_15_imgproc -> value = cameraSensor_membership_functions_value_center;
    then_side_15_dirr  -> value = ang_membership_functions_value_center;
    then_side_15_speed -> value = speed_membership_functions_value_slow;

    // Rule 14    
    charge_rule( "LEJOS, CERCA, CERCA, Img_Proc_IZQUIERDA = IZQUIERDA, S_LENTA", 
                &if_side_14_right, &if_side_14_center, &if_side_14_left, &if_side_14_imgproc,
                &then_side_14_dirr, &then_side_14_speed,
                &rule_14, rule_15);
    if_side_14_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_14_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_14_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_14_imgproc -> value = cameraSensor_membership_functions_value_left;
    then_side_14_dirr  -> value = ang_membership_functions_value_left;
    then_side_14_speed -> value = speed_membership_functions_value_slow;

    // Rule 13
    charge_rule( "LEJOS, CERCA, CERCA, Img_Proc_DERECHA = DERECHA, S_LENTA", 
                &if_side_13_right, &if_side_13_center, &if_side_13_left, &if_side_13_imgproc,
                &then_side_13_dirr, &then_side_13_speed, 
                &rule_13, rule_14);
    if_side_13_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_13_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_13_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_13_imgproc -> value = cameraSensor_membership_functions_value_right;
    then_side_13_dirr  -> value = ang_membership_functions_value_right;
    then_side_13_speed -> value = speed_membership_functions_value_slow;

    // Rule 12
    charge_rule( "LEJOS, CERCA, CERCA, Img_Proc_CENTRO = CENTRO, S_ZERO", 
                &if_side_12_right, &if_side_12_center, &if_side_12_left, &if_side_12_imgproc,
                &then_side_12_dirr, &then_side_12_speed, 
                &rule_12, rule_13); 
    if_side_12_left    -> value = leftSensor_membership_functions_value_lejos;
    if_side_12_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_12_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_12_imgproc -> value = cameraSensor_membership_functions_value_center;
    then_side_12_dirr  -> value = ang_membership_functions_value_center;
    then_side_12_speed -> value = speed_membership_functions_value_slow;

    // Rule 11
    charge_rule( "CERCA, LEJOS, LEJOS, Img_Proc_IZQUIERDA = IZQUIERDA, S_LENTA",
                &if_side_11_right, &if_side_11_center, &if_side_11_left, &if_side_11_imgproc,
                &then_side_11_dirr, &then_side_11_speed, 
                &rule_11, rule_12);
    if_side_11_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_11_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_11_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_11_imgproc -> value = cameraSensor_membership_functions_value_left;
    then_side_11_dirr  -> value = ang_membership_functions_value_left;
    then_side_11_speed -> value = speed_membership_functions_value_slow;

    // Rule 10
    charge_rule( "CERCA, LEJOS, LEJOS, Img_Proc_DERECHA = DERECHA, S_LENTA",
                &if_side_10_right, &if_side_10_center, &if_side_10_left, &if_side_10_imgproc,
                &then_side_10_dirr, &then_side_10_speed,
                &rule_10, rule_11);
    if_side_10_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_10_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_10_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_10_imgproc -> value = cameraSensor_membership_functions_value_right;
    then_side_10_dirr  -> value = ang_membership_functions_value_right;
    then_side_10_speed -> value = speed_membership_functions_value_slow;

    // Rule 9
    charge_rule( "CERCA, LEJOS, LEJOS, Img_Proc_CENTRO = CENTRO, S_LENTA", 
                &if_side_9_right, &if_side_9_center, &if_side_9_left, &if_side_9_imgproc,
                &then_side_9_dirr, &then_side_9_speed, 
                &rule_9, rule_10);
    if_side_9_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_9_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_9_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_9_imgproc -> value = cameraSensor_membership_functions_value_center;
    then_side_9_dirr  -> value = ang_membership_functions_value_center;
    then_side_9_speed -> value = speed_membership_functions_value_slow;

    // Rule 8
    charge_rule( "CERCA, LEJOS, CERCA, Img_Proc_IZQUIERDA = IZQUIERDA, S_LENTA",
                &if_side_8_right, &if_side_8_center, &if_side_8_left, &if_side_8_imgproc,
                &then_side_8_dirr, &then_side_8_speed,  
                &rule_8, rule_9);
    if_side_8_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_8_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_8_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_8_imgproc -> value = cameraSensor_membership_functions_value_left;
    then_side_8_dirr  -> value = ang_membership_functions_value_left;
    then_side_8_speed -> value = speed_membership_functions_value_slow;

    // Rule 7
    charge_rule( "CERCA, LEJOS, CERCA, Img_Proc_DERECHA = DERECHA, S_LENTA", 
                &if_side_7_right, &if_side_7_center, &if_side_7_left, &if_side_7_imgproc,
                &then_side_7_dirr, &then_side_7_speed, 
                &rule_7, rule_8);
    if_side_7_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_7_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_7_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_7_imgproc -> value = cameraSensor_membership_functions_value_right;
    then_side_7_dirr  -> value = ang_membership_functions_value_right;
    then_side_7_speed -> value = speed_membership_functions_value_slow;

    charge_rule( "CERCA, LEJOS, CERCA, Img_Proc_CENTRO = CENTRO, S_LENTA",
                &if_side_6_right, &if_side_6_center, &if_side_6_left, &if_side_6_imgproc,
                &then_side_6_dirr, &then_side_6_speed, 
                &rule_6, rule_7);
    // Rule 6
    if_side_6_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_6_center  -> value = centerSensor_membership_functions_value_lejos;
    if_side_6_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_6_imgproc -> value = cameraSensor_membership_functions_value_center;
    then_side_6_dirr  -> value = ang_membership_functions_value_center;
    then_side_6_speed -> value = speed_membership_functions_value_slow;

    // Rule 5
    charge_rule( "CERCA, CERCA, LEJOS, Img_Proc_IZQUIERDA = IZQUIERDA, S_LENTA",
                &if_side_5_right, &if_side_5_center, &if_side_5_left, &if_side_5_imgproc,
                &then_side_5_dirr, &then_side_5_speed, 
                &rule_5, rule_6);
    if_side_5_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_5_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_5_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_5_imgproc -> value = cameraSensor_membership_functions_value_left;
    then_side_5_dirr  -> value = ang_membership_functions_value_left;
    then_side_5_speed -> value = speed_membership_functions_value_slow;

    // Rule 4
    charge_rule( "CERCA, CERCA, LEJOS, Img_Proc_DERECHA = DERECHA, S_LENTA",
                &if_side_4_right, &if_side_4_center, &if_side_4_left, &if_side_4_imgproc,
                &then_side_4_dirr, &then_side_4_speed, 
                &rule_4, rule_5);
    if_side_4_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_4_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_4_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_4_imgproc -> value = cameraSensor_membership_functions_value_right;
    then_side_4_dirr  -> value = ang_membership_functions_value_right;
    then_side_4_speed -> value = speed_membership_functions_value_slow;

    // Rule 3
    charge_rule( "CERCA, CERCA, LEJOS, Img_Proc_CENTRO = CENTRO, S_LENTA",
                &if_side_3_right, &if_side_3_center, &if_side_3_left, &if_side_3_imgproc,
                &then_side_3_dirr, &then_side_3_speed, 
                &rule_3, rule_4);
    if_side_3_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_3_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_3_right   -> value = rightSensor_membership_functions_value_lejos;
    if_side_3_imgproc -> value = cameraSensor_membership_functions_value_center;
    then_side_3_dirr  -> value = ang_membership_functions_value_center;
    then_side_3_speed -> value = speed_membership_functions_value_slow;

    // Rule 2
    charge_rule( "CERCA, CERCA, CERCA, Img_Proc_IZQUIERDA = IZQUIERDA, S_LENTA",
                &if_side_2_right, &if_side_2_center, &if_side_2_left, &if_side_2_imgproc,
                &then_side_2_dirr, &then_side_2_speed, 
                &rule_2, rule_3);
    if_side_2_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_2_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_2_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_2_imgproc -> value = cameraSensor_membership_functions_value_left;
    then_side_2_dirr  -> value = ang_membership_functions_value_left;
    then_side_2_speed -> value = speed_membership_functions_value_slow;

    // Rule 1
    charge_rule( "CERCA, CERCA, CERCA, Img_Proc_DERECHA = DERECHA, S_LENTA",
                &if_side_1_right, &if_side_1_center, &if_side_1_left, &if_side_1_imgproc,
                &then_side_1_dirr, &then_side_1_speed, 
                &rule_1, rule_2);
    if_side_1_left    -> value = leftSensor_membership_functions_value_cerca;
    if_side_1_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_1_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_1_imgproc -> value = cameraSensor_membership_functions_value_right;
    then_side_1_dirr  -> value = ang_membership_functions_value_right;
    then_side_1_speed -> value = speed_membership_functions_value_slow;

    // Rule 0
    charge_rule( "CERCA, CERCA, CERCA, Img_Proc_CENTRO = CENTRO, S_ZERO",
                &if_side_0_right, &if_side_0_center, &if_side_0_left, &if_side_0_imgproc,
                &then_side_0_dirr, &then_side_0_speed,  
                &rule_0, rule_1); 
    if_side_0_left    -> value = leftSensor_membership_functions_value_cerca;    
    if_side_0_center  -> value = centerSensor_membership_functions_value_cerca;
    if_side_0_right   -> value = rightSensor_membership_functions_value_cerca;
    if_side_0_imgproc -> value = cameraSensor_membership_functions_value_center;
    then_side_0_dirr  -> value = ang_membership_functions_value_center;
    then_side_0_speed -> value = speed_membership_functions_value_slow;          

    while(1)
    {
        sb.sem_op = -1;         /* Asignar recurso */
        if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
            perror("semop");
            exit(1);
        }

        // Leo las entradas del archivo "state.txt"
        get_system_inputs(fdd_State, &rightSensor, &centerSensor, &leftSensor, &dir_imgproc);
        DEBUG_PRINT(("rightSensor %d, centerSensor %d, leftSensor %d, dir_imgproc %d \n", (int)rightSensor, (int)centerSensor, (int)leftSensor, (int)dir_imgproc));

        sb.sem_op = 1;          /* Libera el recurso */
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(1);
        }
        //printf("Unlocked\n");
        System_Inputs_rightSensor->value  = rightSensor;
        System_Inputs_centerSensor->value = centerSensor;
        System_Inputs_leftSensor->value   = leftSensor;
        System_Inputs_ImgProc->value      = dir_imgproc;

        // Fuzzificion de todas las entradas
        fuzzification(System_Inputs_leftSensor);  // left -> center -> right

        //printf("if_side_2_left %f if_side_2_center %f if_side_2_right %f %f %f %f\n", *(if_side_2_left->value), *(if_side_2_center->value), *(if_side_2_right->value), *(if_side_2_imgproc->value), *(then_side_2_dirr->value), *(then_side_2_speed->value) );

        // Evaluo cada regla
        rule_evaluation(rule_0, System_Outputs_ang);

        // Defuzzificion de todas las salidas
        defuzzification(System_Outputs_ang);


        DEBUG_PRINT(("Left cerca %f, left lejos %f \n", *leftSensor_membership_functions_value_cerca, *leftSensor_membership_functions_value_lejos));
        DEBUG_PRINT(("central cerca %f, central lejos %f \n", *centerSensor_membership_functions_value_cerca, *centerSensor_membership_functions_value_lejos));
        DEBUG_PRINT(("right cerca %f, right lejos %f \n", *rightSensor_membership_functions_value_cerca, *rightSensor_membership_functions_value_lejos));
        DEBUG_PRINT(("imgproc left %f, imgproc center %f, imgproc right %f \n", *cameraSensor_membership_functions_value_left, *cameraSensor_membership_functions_value_center, *cameraSensor_membership_functions_value_right));
        DEBUG_PRINT(("ang left %f, ang center %f, ang right %f\n", *ang_membership_functions_value_left, *ang_membership_functions_value_center, *ang_membership_functions_value_right));
        DEBUG_PRINT(("speed slow %f, speed normal %f, speed fast %f \n", *speed_membership_functions_value_slow, *speed_membership_functions_value_normal, *speed_membership_functions_value_fast));

        DEBUG_PRINT(("Las salidas defuzzificadas son: %f, %f\n", System_Outputs_ang->value, System_Outputs_speed->value));

        sb.sem_op = -1;         /* Asignar recurso */
        if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
            perror("semop");
            exit(1);
        }

        // Escribo archivo STATE.txt
        put_system_outputs(fdd_State, System_Outputs_ang->value, System_Outputs_speed->value);

        sb.sem_op = 1;          /* Libera el recurso */
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(1);
        }

        // Reseteo las funciones de pertenencia de las salidas para volver a empezar
        *ang_membership_functions_value_left   = 0; 
        *ang_membership_functions_value_center = 0;
        *ang_membership_functions_value_right  = 0;

        *speed_membership_functions_value_slow   = 0; 
        *speed_membership_functions_value_normal = 0;
        *speed_membership_functions_value_fast   = 0;
        
        usleep(100000);
    }

    // Libero toda la memoria pedida y los file descriptors
    free(System_Inputs_rightSensor);
    free(System_Inputs_centerSensor);
    free(System_Inputs_leftSensor);
    free(System_Inputs_ImgProc);
    free(System_Outputs_speed);
    free(System_Outputs_ang);
    free(membership_functions_outputs_high_speed);
    free(membership_functions_outputs_low_speed);
    free(membership_functions_outputs_goRight);
    free(membership_functions_outputs_goCenter);
    free(membership_functions_outputs_goLeft);
    free(membership_functions_inputs_lejos_right);
    free(membership_functions_inputs_cerca_right);
    free(membership_functions_inputs_lejos_center);
    free(membership_functions_inputs_cerca_center);
    free(membership_functions_inputs_lejos_left);
    free(membership_functions_inputs_cerca_left);
    fclose(fdd_State);
    close(fdp);
    return 0;
}