#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAXNAME        200      // Numero maximo de caracteres en los nombres 
#define UPPER_LIMIT      1      // Numero maximo asignable como grado de pertenencia 
#define DEBUG            1

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

#define MAX_RETRIES 10

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

// io_type crea una lista de entradas y salidas del sistema. Todos los campos
// son fijos excepto "value", que se actualiza en cada paso de inferencia difusa. 
struct io_type{
  char name[MAXNAME];                       // nombre de la entrada o salida.
  float value;                              // Valor de la entrada o salida.
  struct mf_type *membership_functions;     // Lista de las funciones de pertenencia de esa entrada o salida.
  struct io_type *next;                     // Puntero a la siguiente entrada o salida.
  };
// Membership functions: Esta asociada con cara entrada y salida del sistema 
struct mf_type{
  char name[MAXNAME];       /* name of membership function (fuzzy set)    */
  float value;              /* degree of membership or output strength    */
  float point1;               /* leftmost x-axis point of mem. function     */
  float point2;               /* rightmost x-axis point of mem. function    */
  float slope1;             /* slope of left side of membership function  */
  float slope2;             /* slope of right side of membership function */
  struct mf_type *next;     /* pointer to next membership function    */
  };

// Cada regla tiene un antecedente y un consecuente. Los elementos en "if_side" son antecedentes,
// y los elementos en "then_side" son consecuentes.44501516

struct rule_element_type{
  float *value;                     // Puntero al valor del antecedente o consecuente 
  struct rule_element_type *next;   // Proximo antecedente o consecuente en la regla
  };
struct rule_type{
  char name[MAXNAME];
  struct rule_element_type *if_side;     // Lista de antecedentes de esta regla.
  struct rule_element_type *then_side;   // Lista de consecuentes.
  struct rule_type *next;                // Proxima regla
  };


int initsem(key_t key, int nsems);
struct io_type* initialize_system_io(char *name, float value, struct mf_type *membership_functions, struct io_type *next);
int get_system_inputs(FILE* fdd_State, long long int *rightSensor, long long int *centerSensor, long long int *leftSensor, long long int *dir_imgproc);
int put_system_outputs(FILE* fdd_State, struct io_type *System_Outputs);
void fuzzification(struct io_type *System_Inputs);
void rule_evaluation(struct rule_type *Rule_Base, struct io_type *System_Outputs);
void defuzzification(struct io_type *System_Outputs);
float compute_area_of_trapezoid(struct mf_type *mf);
void add_rule (struct rule_type **rule, char *name, struct rule_element_type *if_side, struct rule_element_type *then_side, struct rule_type *next);
void add_rule_element( struct rule_element_type **element,  float value, struct rule_element_type *next);
void update_rule (struct rule_type *rule, char *name);
void charge_rule(   char *rule_text,                     
                    struct rule_element_type **if_side_right, struct rule_element_type **if_side_center, struct rule_element_type **if_side_left, struct rule_element_type **if_side_imgproc,
                    struct rule_element_type **then_side_dirr, struct rule_element_type **then_side_speed,
                    struct rule_type **rule, struct rule_type *next_rule );
void read_from_state_string(FILE* fdd_State, char recurso[], struct sembuf sb, int semid, char *readed);

void initialize_membership_inputs(char *name, int value, float point1, float point2, float slope1, float slope2, struct mf_type * next, struct mf_type** membership_functions_inputs);