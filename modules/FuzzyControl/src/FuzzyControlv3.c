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

  // System outputs
  struct io_type *System_Outputs_ang   = NULL;
  struct io_type *System_Outputs_w     = NULL;
  struct io_type *System_Outputs_speed = NULL;

  // Funciones de pertenencias
  struct mf_type *membership_functions_inputs_cerca_right  = NULL;  
  struct mf_type *membership_functions_inputs_lejos_right  = NULL;  
  struct mf_type *membership_functions_inputs_cerca_center = NULL;  
  struct mf_type *membership_functions_inputs_lejos_center = NULL; 
  struct mf_type *membership_functions_inputs_cerca_left   = NULL;  
  struct mf_type *membership_functions_inputs_lejos_left   = NULL; 

  struct mf_type *membership_functions_outputs_goLeft      = NULL;
  struct mf_type *membership_functions_outputs_goRight     = NULL;
  struct mf_type *membership_functions_outputs_goCenter    = NULL;

  struct mf_type *membership_functions_outputs_low_W       = NULL;
  struct mf_type *membership_functions_outputs_high_W      = NULL;   

  struct mf_type *membership_functions_outputs_high_speed   = NULL;
  struct mf_type *membership_functions_outputs_normal_speed = NULL;
  struct mf_type *membership_functions_outputs_low_speed    = NULL;
  
  //////////////////////////////////////////////// Reglas
  //////////////////////////////////////////////// leftSensor, centerSensor, rightSensor
  struct rule_type         *rule_0           = NULL;                  
  struct rule_element_type *if_side_0_left   = NULL;
  struct rule_element_type *if_side_0_right  = NULL;
  struct rule_element_type *if_side_0_center = NULL;
  struct rule_element_type *then_side_0      = NULL; // Si CERCA, CERCA , CERCA = CENTRO
  struct rule_type         *rule_1           = NULL;
  struct rule_element_type *if_side_1_left   = NULL;
  struct rule_element_type *if_side_1_right  = NULL; 
  struct rule_element_type *if_side_1_center = NULL;
  struct rule_element_type *then_side_1      = NULL; // Si CERCA, CERCA , LEJOS = DERECHA

  struct rule_type         *rule_2           = NULL;
  struct rule_element_type *if_side_2_left   = NULL;
  struct rule_element_type *if_side_2_right  = NULL; 
  struct rule_element_type *if_side_2_center = NULL;
  struct rule_element_type *then_side_2      = NULL; // Si CERCA, LEJOS , CERCA = CENTRO

  struct rule_type         *rule_3           = NULL;
  struct rule_element_type *if_side_3_left   = NULL;
  struct rule_element_type *if_side_3_right  = NULL; 
  struct rule_element_type *if_side_3_center = NULL;
  struct rule_element_type *then_side_3      = NULL; // Si CERCA, LEJOS , LEJOS = DERECHA

  struct rule_type         *rule_4           = NULL;
  struct rule_element_type *if_side_4_left   = NULL;
  struct rule_element_type *if_side_4_right  = NULL; 
  struct rule_element_type *if_side_4_center = NULL;
  struct rule_element_type *then_side_4      = NULL; // Si LEJOS, CERCA , CERCA = IZQUIERDA

  struct rule_type         *rule_5           = NULL;
  struct rule_element_type *if_side_5_left   = NULL;
  struct rule_element_type *if_side_5_right  = NULL; 
  struct rule_element_type *if_side_5_center = NULL;
  struct rule_element_type *then_side_5      = NULL; // Si LEJOS, CERCA , LEJOS = DERECHA

  struct rule_type         *rule_6           = NULL;
  struct rule_element_type *if_side_6_left   = NULL;
  struct rule_element_type *if_side_6_right  = NULL; 
  struct rule_element_type *if_side_6_center = NULL;
  struct rule_element_type *then_side_6      = NULL; // Si LEJOS, LEJOS , CERCA = IZQUIERDA

  struct rule_type         *rule_7           = NULL;
  struct rule_element_type *if_side_7_left   = NULL;
  struct rule_element_type *if_side_7_right  = NULL; 
  struct rule_element_type *if_side_7_center = NULL;
  struct rule_element_type *then_side_7      = NULL; // Si LEJOS, LEJOS , LEJOS = CENTRO

  long long int rightSensor, centerSensor, leftSensor;

  char recurso[50], img_proc_tipo[30];

  //printf("Entradas: leftSensor, centerSensor, rightSensor \n");

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

  if ( (fdd_State = fopen("/home/root/Tesis/Apps/state.txt", "r+")) == NULL)
  {
      printf("Error abriendo state.txt\n");
      return -1;
  }

  // Cargo las funciones de pertenencias 
  // Funciones de pertenencia para rightSensor
  membership_functions_inputs_lejos_right = initialize_membership_inputs("Lejos", 0,   30,  940, (float)1/30, (float)1/30, NULL);
  membership_functions_inputs_cerca_right = initialize_membership_inputs("Cerca", 0,  -60,   60, (float)1/30, (float)1/30, membership_functions_inputs_lejos_right);

  // Funciones de pertenencia para centerSensor
  membership_functions_inputs_lejos_center = initialize_membership_inputs("Lejos", 0,  30,  940,  (float)1/30, (float)1/30, NULL);
  membership_functions_inputs_cerca_center = initialize_membership_inputs("Cerca", 0, -60,   60,  (float)1/30, (float)1/30, membership_functions_inputs_lejos_center);

  // Funciones de pertenencia para leftSensor
  membership_functions_inputs_lejos_left = initialize_membership_inputs("Lejos", 0,    30,   940,  (float)1/30, (float)1/30, NULL);
  membership_functions_inputs_cerca_left = initialize_membership_inputs("Cerca", 0,   -60,   60,  (float)1/30, (float)1/30, membership_functions_inputs_lejos_left);

  // Cargo las estructuras de las entradas (lo tengo que hacer aca porque las entradas varian)
  System_Inputs_rightSensor  = initialize_system_io("Right", 0, membership_functions_inputs_cerca_right, NULL);
  if (System_Inputs_rightSensor == NULL)
    return -1;
  System_Inputs_centerSensor = initialize_system_io("Center", 0, membership_functions_inputs_cerca_center, System_Inputs_rightSensor);
  if (System_Inputs_centerSensor == NULL)
    return -1;
  System_Inputs_leftSensor   = initialize_system_io("Left", 0, membership_functions_inputs_cerca_left, System_Inputs_centerSensor);
  if (System_Inputs_leftSensor == NULL)
    return -1;

  // Cargo cada regla con los valores de la fuzzificacion
  charge_rules(   "LEJOS, LEJOS , LEJOS = CENTRO, W_BAJO, S_RAPIDA", 
                  "LEJOS, LEJOS , CERCA = CENTRO, W_ALTO, S_LENTA",
                  "LEJOS, CERCA , LEJOS = IZQUIERDA, W_ALTO, S_LENTA",
                  "LEJOS, CERCA , CERCA = IZQUIERDA, W_ALTO, S_LENTA",
                  "CERCA, LEJOS , LEJOS = CENTRO, W_ALTO, S_LENTA",
                  "CERCA, LEJOS , CERCA = CENTRO, W_ALTO, S_LENTA",
                  "CERCA, CERCA , LEJOS = DERECHA, W_ALTO, S_LENTA",
                  "CERCA, CERCA , CERCA = IZQUIERDA, W_ALTO, S_LENTA",
                  &if_side_7_right, &if_side_7_center, &if_side_7_left,
                  &then_side_7, &rule_7,
                  &if_side_6_right, &if_side_6_center, &if_side_6_left,
                  &then_side_6, &rule_6,
                  &if_side_5_right, &if_side_5_center, &if_side_5_left,
                  &then_side_5, &rule_5,
                  &if_side_4_right, &if_side_4_center, &if_side_4_left,
                  &then_side_4, &rule_4,
                  &if_side_3_right, &if_side_3_center, &if_side_3_left,
                  &then_side_3, &rule_3,
                  &if_side_2_right, &if_side_2_center, &if_side_2_left,
                  &then_side_2, &rule_2,
                  &if_side_1_right, &if_side_1_center, &if_side_1_left,
                  &then_side_1, &rule_1,
                  &if_side_0_right, &if_side_0_center, &if_side_0_left,
                  &then_side_0, &rule_0,
                  System_Inputs_rightSensor, System_Inputs_centerSensor, System_Inputs_leftSensor);
  // Outputs
  membership_functions_outputs_high_speed = initialize_membership_inputs("high_speed",     0,  0.3, 0.5, (float)1/0.1, (float)1/0.1, NULL);
  membership_functions_outputs_normal_speed = initialize_membership_inputs("normal_speed", 0,  0.2, 0.4, (float)1/0.1, (float)1/0.1, membership_functions_outputs_high_speed);
  membership_functions_outputs_low_speed  = initialize_membership_inputs("low_speed",      0,  0.1, 0.3, (float)1/0.1, (float)1/0.1, membership_functions_outputs_normal_speed);
  
  //membership_functions_outputs_high_speed = initialize_membership_inputs("high_speed",  0,  0.3, 0.7, (float)1/0.2, (float)1/0.2, NULL);
  //membership_functions_outputs_low_speed  = initialize_membership_inputs("low_speed",   0,  0.1, 0.5, (float)1/0.2, (float)1/0.2, membership_functions_outputs_high_speed);

  // membership_functions_outputs_high_W   = initialize_membership_inputs("high_W",  0, -0.75, 0.75, (float)1/0.5, (float)1/0.5, NULL);
  // membership_functions_outputs_low_W    = initialize_membership_inputs("low_W", 0,  0.25, 1.75, (float)1/0.5, (float)1/0.5, membership_functions_outputs_high_W);
  membership_functions_outputs_high_W   = initialize_membership_inputs("high_W",  0, 0, 2, (float)1/0.5, (float)1/0.5, NULL);
  membership_functions_outputs_low_W    = initialize_membership_inputs("low_W",   0,-0.5, 0.5, (float)1/0.5, (float)1/0.5, membership_functions_outputs_high_W);

  //membership_functions_outputs_goRight  = initialize_membership_inputs("goRight",  0,    0, 180, (float)1/25, (float)1/25, NULL);
  //membership_functions_outputs_goCenter = initialize_membership_inputs("goCenter", 0,  -25,  25, (float)1/25, (float)1/25, membership_functions_outputs_goRight);
  //membership_functions_outputs_goLeft   = initialize_membership_inputs("goLeft",   0, -180,   0, (float)1/25, (float)1/25, membership_functions_outputs_goCenter);

  membership_functions_outputs_goRight  = initialize_membership_inputs("goRight",  0,    0,  90, (float)1/45, (float)1/45, NULL);
  membership_functions_outputs_goCenter = initialize_membership_inputs("goCenter", 0,  -45,  45, (float)1/45, (float)1/45, membership_functions_outputs_goRight);
  membership_functions_outputs_goLeft   = initialize_membership_inputs("goLeft",   0,  -90,   0, (float)1/45, (float)1/45, membership_functions_outputs_goCenter);

  System_Outputs_speed = initialize_system_io("Speed", 0, membership_functions_outputs_low_speed, NULL);
  if (System_Outputs_speed == NULL)
    return -1; 
  
  System_Outputs_w = initialize_system_io("W", 0, membership_functions_outputs_low_W, System_Outputs_speed);
  if (System_Outputs_w == NULL)
    return -1;

  System_Outputs_ang = initialize_system_io("Angulo", 0, membership_functions_outputs_goLeft, System_Outputs_w);
  if (System_Outputs_ang == NULL)
    return -1;

  // Cargo los valores de la fuzzificacion en las reglas
  // LEJOS, LEJOS , LEJOS = CENTRO
  if_side_7_right  -> value = &(System_Inputs_rightSensor -> membership_functions->next->value);
  if_side_7_center -> value = &(System_Inputs_centerSensor-> membership_functions->next->value);
  if_side_7_left   -> value = &(System_Inputs_leftSensor  -> membership_functions->next->value);

  // LEJOS, LEJOS , CERCA = IZQUIERDA
  if_side_6_right  -> value = &(System_Inputs_rightSensor -> membership_functions->value);
  if_side_6_center -> value = &(System_Inputs_centerSensor-> membership_functions->next->value);
  if_side_6_left   -> value = &(System_Inputs_leftSensor  -> membership_functions->next->value);

  // LEJOS, CERCA , LEJOS = DERECHA
  if_side_5_right  -> value = &(System_Inputs_rightSensor -> membership_functions->next->value);
  if_side_5_center -> value = &(System_Inputs_centerSensor-> membership_functions->value);
  if_side_5_left   -> value = &(System_Inputs_leftSensor  -> membership_functions->next->value);

  // LEJOS, CERCA , CERCA = IZQUIERDA
  if_side_4_right  -> value = &(System_Inputs_rightSensor -> membership_functions->value);
  if_side_4_center -> value = &(System_Inputs_centerSensor-> membership_functions->value);
  if_side_4_left   -> value = &(System_Inputs_leftSensor  -> membership_functions->next->value);

  // Si CERCA, LEJOS , LEJOS = DERECHA
  if_side_3_right  -> value = &(System_Inputs_rightSensor -> membership_functions->next->value);
  if_side_3_center -> value = &(System_Inputs_centerSensor-> membership_functions->next->value);
  if_side_3_left   -> value = &(System_Inputs_leftSensor  -> membership_functions->value);

  // Si CERCA, LEJOS , CERCA = CENTRO
  if_side_2_right  -> value = &(System_Inputs_rightSensor -> membership_functions->value);
  if_side_2_center -> value = &(System_Inputs_centerSensor-> membership_functions->next->value);
  if_side_2_left   -> value = &(System_Inputs_leftSensor  -> membership_functions->value);

  // Si CERCA, CERCA , LEJOS = DERECHA
  if_side_1_right  -> value = &(System_Inputs_rightSensor -> membership_functions->next->value);
  if_side_1_center -> value = &(System_Inputs_centerSensor-> membership_functions->value);
  if_side_1_left   -> value = &(System_Inputs_leftSensor  -> membership_functions->value);

  // Si CERCA, CERCA , CERCA = DERECHA
  if_side_0_right  -> value = &(System_Inputs_rightSensor -> membership_functions->value);
  if_side_0_center -> value = &(System_Inputs_centerSensor-> membership_functions->value);
  if_side_0_left   -> value = &(System_Inputs_leftSensor  -> membership_functions->value);

  while(1)
  {
      sb.sem_op = -1;         /* Asignar recurso */
      if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
          perror("semop");
          exit(1);
      }

      // Leo las entradas del archivo "state.txt"
      get_system_inputs(fdd_State, &rightSensor, &centerSensor, &leftSensor);
      //printf("rightSensor %lld, centerSensor %lld, leftSensor %lld \n", rightSensor, centerSensor, leftSensor);

      sb.sem_op = 1;          /* Libera el recurso */
      if (semop(semid, &sb, 1) == -1) {
          perror("semop");
          exit(1);
      }
      //printf("Unlocked\n");
      System_Inputs_rightSensor->value  = rightSensor;
      System_Inputs_centerSensor->value = centerSensor;
      System_Inputs_leftSensor->value   = leftSensor;

      fuzzification(System_Inputs_leftSensor);  // left -> center -> right

      // // Antes de evaluar las reglas, chequeo el estado del sistema de procesamiento de imagenes
      strcpy(recurso,"ImgProc, Direccion = %s\n");
      read_from_state_string(fdd_State, recurso, sb, semid, img_proc_tipo);

      if( strcmp(img_proc_tipo, "IZQUIERDA") == 0){
        //printf("Reconoci un tomate, cambio el set de reglas\n");
        update_rule(rule_7, "LEJOS, LEJOS , LEJOS = IZQUIERDA, W_BAJO, S_NORMAL");
        update_rule(rule_6, "LEJOS, LEJOS , CERCA = IZQUIERDA, W_ALTO, S_NORMAL");
        update_rule(rule_5, "LEJOS, CERCA , LEJOS = IZQUIERDA, W_ALTO, S_NORMAL");
        update_rule(rule_4, "LEJOS, CERCA , CERCA = IZQUIERDA, W_ALTO, S_NORMAL");
        update_rule(rule_3, "CERCA, LEJOS , LEJOS = IZQUIERDA, W_ALTO, S_NORMAL");
        update_rule(rule_2, "CERCA, LEJOS , CERCA = IZQUIERDA, W_ALTO, S_NORMAL");
        update_rule(rule_1, "CERCA, CERCA , LEJOS = IZQUIERDA, W_ALTO, S_NORMAL");
        update_rule(rule_0, "CERCA, CERCA , CERCA = IZQUIERDA, W_ALTO, S_NORMAL");
      }
      if( strcmp(img_proc_tipo, "DERECHA") == 0){
        //printf("Reconoci un tomate, cambio el set de reglas\n");
        update_rule(rule_7, "LEJOS, LEJOS , LEJOS = DERECHA, W_BAJO, S_NORMAL");
        update_rule(rule_6, "LEJOS, LEJOS , CERCA = DERECHA, W_ALTO, S_NORMAL");
        update_rule(rule_5, "LEJOS, CERCA , LEJOS = DERECHA, W_ALTO, S_NORMAL");
        update_rule(rule_4, "LEJOS, CERCA , CERCA = DERECHA, W_ALTO, S_NORMAL");
        update_rule(rule_3, "CERCA, LEJOS , LEJOS = DERECHA, W_ALTO, S_NORMAL");
        update_rule(rule_2, "CERCA, LEJOS , CERCA = DERECHA, W_ALTO, S_NORMAL");
        update_rule(rule_1, "CERCA, CERCA , LEJOS = DERECHA, W_ALTO, S_NORMAL");
        update_rule(rule_0, "CERCA, CERCA , CERCA = DERECHA, W_ALTO, S_NORMAL");
      }

      if( strcmp(img_proc_tipo, "DESCONOCIDO") == 0){
        /* Con destino */
        // update_rule(rule_7, "LEJOS, LEJOS , LEJOS = CENTRO, W_BAJO, S_LENTA");
        // update_rule(rule_6, "LEJOS, LEJOS , CERCA = CENTRO, W_ALTO, S_LENTA");
        // update_rule(rule_5, "LEJOS, CERCA , LEJOS = IZQUIERDA, W_ALTO, S_LENTA");
        // update_rule(rule_4, "LEJOS, CERCA , CERCA = IZQUIERDA, W_ALTO, S_LENTA");
        // update_rule(rule_3, "CERCA, LEJOS , LEJOS = CENTRO, W_ALTO, S_LENTA");
        // update_rule(rule_2, "CERCA, LEJOS , CERCA = CENTRO, W_ALTO, S_LENTA");
        // update_rule(rule_1, "CERCA, CERCA , LEJOS = DERECHA, W_ALTO, S_LENTA");
        // update_rule(rule_0, "CERCA, CERCA , CERCA = IZQUIERDA, W_ALTO, S_LENTA");

        /* Libre */
        update_rule(rule_7, "LEJOS, LEJOS , LEJOS = CENTRO, W_BAJO, S_LENTA");
        update_rule(rule_6, "LEJOS, LEJOS , CERCA = IZQUIERDA, W_ALTO, S_LENTA");
        update_rule(rule_5, "LEJOS, CERCA , LEJOS = DERECHA, W_ALTO, S_LENTA");
        update_rule(rule_4, "LEJOS, CERCA , CERCA = IZQUIERDA, W_ALTO, S_LENTA");
        update_rule(rule_3, "CERCA, LEJOS , LEJOS = DERECHA, W_ALTO, S_LENTA");
        update_rule(rule_2, "CERCA, LEJOS , CERCA = CENTRO, W_ALTO, S_LENTA");
        update_rule(rule_1, "CERCA, CERCA , LEJOS = DERECHA, W_ALTO, S_LENTA");
        update_rule(rule_0, "CERCA, CERCA , CERCA = DERECHA, W_ALTO, S_LENTA"); 
      }


      // Evaluo cada regla
      rule_evaluation(rule_0, System_Outputs_ang);
      
      // Defuzzificion
      defuzzification(System_Outputs_ang);
      //printf("Las salidas defuzzificadas son: %f, %f, %f\n", System_Outputs_ang->value, System_Outputs_w->value, System_Outputs_speed->value);

      sb.sem_op = -1;         /* Asignar recurso */
      if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
          perror("semop");
          exit(1);
      }

      // Escribo archivo STATE.txt
      put_system_outputs(fdd_State, System_Outputs_ang);

      sb.sem_op = 1;          /* Libera el recurso */
      if (semop(semid, &sb, 1) == -1) {
          perror("semop");
          exit(1);
      }
      
      //usleep(20000);
  }

  // Libero toda la memoria pedida y los file descriptors
  free(System_Inputs_rightSensor);
  free(System_Inputs_centerSensor);
  free(System_Inputs_leftSensor);
  free(System_Outputs_speed);
  free(System_Outputs_w);
  free(System_Outputs_ang);
  free(membership_functions_outputs_high_speed);
  free(membership_functions_outputs_low_speed);
  free(membership_functions_outputs_high_W);
  free(membership_functions_outputs_low_W);
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