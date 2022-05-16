#include "readSTATE.h"

int main(void)
{

    // Semaforo
    key_t key;              
    int semid, fdp;
    struct sembuf sb;
    union semun arg;

    sb.sem_num = 0;
    sb.sem_op = -1; /* set to allocate resource */
    sb.sem_flg = SEM_UNDO;

    // File
    FILE* fdd_State;
    ssize_t lread;
    char * line = NULL;
    size_t len = 0;  


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

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////   main  /////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    while(1)
    {
        printf("Trying to lock...\n");
        sb.sem_op = -1;         /* Asignar recurso */
        if (semop(semid, &sb, 1) == -1) {           /* semop setea, chequea o limpia uno o varios semaforos */
            perror("semop");
            exit(1);
        }
        printf("Locked.\n");


            // Reunicio puntero al archivo
            fseek(fdd_State, 0, SEEK_SET);
        
            // Leo el archivo buscando las entradas
            while ( (lread=getline(&line, &len, fdd_State )) != -1)
            {
                printf("%s", line);
            }

        sb.sem_op = 1;          /* Libera el recurso */
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(1);
        }
        printf("Unlocked\n");

        //printf("press to read again\n"); 
        //getchar();

        sleep(1);
    }

     /* remove it: */
    if (semctl(semid, 0, IPC_RMID, arg) == -1) {
    perror("semctl");
    exit(1);
    }

    return 0;
}