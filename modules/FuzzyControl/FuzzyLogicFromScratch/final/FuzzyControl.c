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
  struct io_type *System_Outputs = NULL;

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


  long long int rightSensor, centerSensor, leftSensor;

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
  membership_functions_inputs_lejos_right = initialize_membership_inputs("Lejos", 0,  30, 970, (float)1/30, (float)1/30, NULL);
  membership_functions_inputs_cerca_right = initialize_membership_inputs("Cerca", 0, -60, 60, (float)1/30, (float)1/30, membership_functions_inputs_lejos_right);

  // Funciones de pertenencia para centerSensor
  membership_functions_inputs_lejos_center = initialize_membership_inputs("Lejos", 0,  30,  970, (float)1/30, (float)1/30, NULL);
  membership_functions_inputs_cerca_center = initialize_membership_inputs("Cerca", 0, -60,  60, (float)1/30, (float)1/30, membership_functions_inputs_lejos_center);

  // Funciones de pertenencia para leftSensor
  membership_functions_inputs_lejos_left = initialize_membership_inputs("Lejos", 0,  30,  970, (float)1/30, (float)1/30, NULL);
  membership_functions_inputs_cerca_left = initialize_membership_inputs("Cerca", 0, -60,  60, (float)1/30, (float)1/30, membership_functions_inputs_lejos_left);

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
  // Si LEJOS, LEJOS , LEJOS = CENTRO
  if_side_7_right  = add_rule_element(if_side_7_right,  System_Inputs_rightSensor ->membership_functions->next->value, NULL);
  if_side_7_center = add_rule_element(if_side_7_center, System_Inputs_centerSensor->membership_functions->next->value, if_side_7_right);
  if_side_7_left   = add_rule_element(if_side_7_left,   System_Inputs_leftSensor  ->membership_functions->next->value, if_side_7_center);
  then_side_7      = add_rule_element(then_side_7,      0.0, NULL);
  rule_7           = add_rule(rule_7, "LEJOS, LEJOS , LEJOS = CENTRO", if_side_7_left, then_side_7, NULL);

  // Si LEJOS, LEJOS , CERCA = IZQUIERDA
  if_side_6_right  = add_rule_element(if_side_6_right,  System_Inputs_rightSensor ->membership_functions->value, NULL);
  if_side_6_center = add_rule_element(if_side_6_center, System_Inputs_centerSensor->membership_functions->next->value, if_side_6_right);
  if_side_6_left   = add_rule_element(if_side_6_left,   System_Inputs_leftSensor  ->membership_functions->next->value, if_side_6_center);
  then_side_6      = add_rule_element(then_side_6,      0.0, NULL);
  rule_6           = add_rule(rule_6, "LEJOS, LEJOS , CERCA = IZQUIERDA", if_side_6_left, then_side_6, rule_7);

  // Si LEJOS, CERCA , LEJOS = DERECHA
  if_side_5_right  = add_rule_element(if_side_5_right,  System_Inputs_rightSensor ->membership_functions->next->value, NULL);
  if_side_5_center = add_rule_element(if_side_5_center, System_Inputs_centerSensor->membership_functions->value, if_side_5_right);
  if_side_5_left   = add_rule_element(if_side_5_left,   System_Inputs_leftSensor  ->membership_functions->next->value, if_side_5_center);
  then_side_5      = add_rule_element(then_side_5,      0.0, NULL);
  rule_5           = add_rule(rule_5, "LEJOS, CERCA , LEJOS = DERECHA", if_side_5_left, then_side_5, rule_6);

  // Si LEJOS, CERCA , CERCA = IZQUIERDA
  if_side_4_right  = add_rule_element(if_side_4_right,  System_Inputs_rightSensor ->membership_functions->value, NULL);
  if_side_4_center = add_rule_element(if_side_4_center, System_Inputs_centerSensor->membership_functions->value, if_side_4_right);
  if_side_4_left   = add_rule_element(if_side_4_left,   System_Inputs_leftSensor  ->membership_functions->next->value, if_side_4_center);
  then_side_4      = add_rule_element(then_side_4,      0.0, NULL);
  rule_4           = add_rule(rule_4, "LEJOS, CERCA , CERCA = IZQUIERDA", if_side_4_left, then_side_4, rule_5);

  // Si CERCA, LEJOS , LEJOS = DERECHA
  if_side_3_right  = add_rule_element(if_side_3_right,  System_Inputs_rightSensor ->membership_functions->next->value, NULL);
  if_side_3_center = add_rule_element(if_side_3_center, System_Inputs_centerSensor->membership_functions->next->value, if_side_3_right);
  if_side_3_left   = add_rule_element(if_side_3_left,   System_Inputs_leftSensor  ->membership_functions->value, if_side_3_center);
  then_side_3      = add_rule_element(then_side_3,      0.0, NULL);
  rule_3           = add_rule(rule_3, "CERCA, LEJOS , LEJOS = DERECHA", if_side_3_left, then_side_3, rule_4);
  
  // Si CERCA, LEJOS , CERCA = CENTRO
  if_side_2_right  = add_rule_element(if_side_2_right,  System_Inputs_rightSensor ->membership_functions->value, NULL);
  if_side_2_center = add_rule_element(if_side_2_center, System_Inputs_centerSensor->membership_functions->next->value, if_side_2_right);
  if_side_2_left   = add_rule_element(if_side_2_left,   System_Inputs_leftSensor  ->membership_functions->value, if_side_2_center);
  then_side_2      = add_rule_element(then_side_2,      0.0, NULL);
  rule_2           = add_rule(rule_2, "CERCA, LEJOS , CERCA = CENTRO", if_side_2_left, then_side_2, rule_3);
  
  // Si CERCA, CERCA , LEJOS = DERECHA
  if_side_1_right  = add_rule_element(if_side_1_right,  System_Inputs_rightSensor ->membership_functions->next->value, NULL);
  if_side_1_center = add_rule_element(if_side_1_center, System_Inputs_centerSensor->membership_functions->value, if_side_1_right);
  if_side_1_left   = add_rule_element(if_side_1_left,   System_Inputs_leftSensor  ->membership_functions->value, if_side_1_center);
  then_side_1      = add_rule_element(then_side_1,      0.0, NULL);
  rule_1           = add_rule(rule_1, "CERCA, CERCA , LEJOS = DERECHA", if_side_1_left, then_side_1, rule_2);
  
  // Si CERCA, CERCA , CERCA = CENTRO
  if_side_0_right  = add_rule_element(if_side_0_right,  System_Inputs_rightSensor ->membership_functions->value, NULL);
  if_side_0_center = add_rule_element(if_side_0_center, System_Inputs_centerSensor->membership_functions->value, if_side_0_right);
  if_side_0_left   = add_rule_element(if_side_0_left,   System_Inputs_leftSensor  ->membership_functions->value, if_side_0_center);
  then_side_0      = add_rule_element(then_side_0,      0.0, NULL);
  rule_0           = add_rule(rule_0, "CERCA, CERCA , CERCA = DERECHA", if_side_0_left, then_side_0, rule_1);

  // Output
  membership_functions_outputs_goRight  = initialize_membership_inputs("goRight",  0,   20, 340, (float)1/10, (float)1/10, NULL);
  membership_functions_outputs_goCenter = initialize_membership_inputs("goCenter", 0,  -20,  20, (float)1/10, (float)1/10, membership_functions_outputs_goRight);
  membership_functions_outputs_goLeft   = initialize_membership_inputs("goLeft",   0, -340, -20, (float)1/10, (float)1/10, membership_functions_outputs_goCenter);

  System_Outputs   = initialize_system_io("Angulo", 0, membership_functions_outputs_goLeft, NULL);
  if (System_Outputs == NULL)
    return -1;

  while(1)
  {
      //printf("While \n");

      //printf("Trying to lock...\n");
      sb.sem_op = -1;         /* Asignar recurso */
      if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
          perror("semop");
          exit(1);
      }
      //printf("Locked.\n");

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

      // Cargo los valores de la fuzzificacion en las reglas

      // LEJOS, LEJOS , LEJOS = CENTRO
      *(if_side_7_right  -> value) = System_Inputs_rightSensor -> membership_functions->next->value;
      *(if_side_7_center -> value) = System_Inputs_centerSensor-> membership_functions->next->value;
      *(if_side_7_left   -> value) = System_Inputs_leftSensor  -> membership_functions->next->value;

      // LEJOS, LEJOS , CERCA = IZQUIERDA
      *(if_side_6_right  -> value) = System_Inputs_rightSensor -> membership_functions->value;
      *(if_side_6_center -> value) = System_Inputs_centerSensor-> membership_functions->next->value;
      *(if_side_6_left   -> value) = System_Inputs_leftSensor  -> membership_functions->next->value;

      // LEJOS, CERCA , LEJOS = DERECHA
      *(if_side_5_right  -> value) = System_Inputs_rightSensor -> membership_functions->next->value;
      *(if_side_5_center -> value) = System_Inputs_centerSensor-> membership_functions->value;
      *(if_side_5_left   -> value) = System_Inputs_leftSensor  -> membership_functions->next->value;

      // LEJOS, CERCA , CERCA = IZQUIERDA
      *(if_side_4_right  -> value) = System_Inputs_rightSensor -> membership_functions->value;
      *(if_side_4_center -> value) = System_Inputs_centerSensor-> membership_functions->value;
      *(if_side_4_left   -> value) = System_Inputs_leftSensor  -> membership_functions->next->value;

      // Si CERCA, LEJOS , LEJOS = DERECHA
      *(if_side_3_right  -> value) = System_Inputs_rightSensor -> membership_functions->next->value;
      *(if_side_3_center -> value) = System_Inputs_centerSensor-> membership_functions->next->value;
      *(if_side_3_left   -> value) = System_Inputs_leftSensor  -> membership_functions->value;

      // Si CERCA, LEJOS , CERCA = CENTRO
      *(if_side_2_right  -> value) = System_Inputs_rightSensor -> membership_functions->value;
      *(if_side_2_center -> value) = System_Inputs_centerSensor-> membership_functions->next->value;
      *(if_side_2_left   -> value) = System_Inputs_leftSensor  -> membership_functions->value;

      // Si CERCA, CERCA , LEJOS = DERECHA
      *(if_side_1_right  -> value) = System_Inputs_rightSensor -> membership_functions->next->value;
      *(if_side_1_center -> value) = System_Inputs_centerSensor-> membership_functions->value;
      *(if_side_1_left   -> value) = System_Inputs_leftSensor  -> membership_functions->value;

      // Si CERCA, CERCA , CERCA = DERECHA
      *(if_side_0_right  -> value) = System_Inputs_rightSensor -> membership_functions->value;
      *(if_side_0_center -> value) = System_Inputs_centerSensor-> membership_functions->value;
      *(if_side_0_left   -> value) = System_Inputs_leftSensor  -> membership_functions->value;
      
      // Evaluo cada regla
      rule_evaluation(rule_0, System_Outputs);

      // Defuzzifico
      defuzzification(System_Outputs);


      //printf("Trying to lock...\n");
      sb.sem_op = -1;         /* Asignar recurso */
      if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
          perror("semop");
          exit(1);
      }
      //printf("Locked.\n");

          // Escribo archivo STATE.txt
          put_system_outputs(fdd_State, System_Outputs->value);

      sb.sem_op = 1;          /* Libera el recurso */
      if (semop(semid, &sb, 1) == -1) {
          perror("semop");
          exit(1);
      }
      //printf("Unlocked\n");
      
      usleep(200000);
  }

  fclose(fdd_State);
  return 0;
}