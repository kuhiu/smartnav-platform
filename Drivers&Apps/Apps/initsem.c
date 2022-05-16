#include "./Funciones/func.h"

int initsem(key_t key, int nsems) 
{
    int i;
    union semun arg;
    struct semid_ds buf;
    struct sembuf sb;
    int semid;

    semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);
    if ((semid) >= 0) {             /* Este proceso gano la carrera para conseguir el set de semaforos */
        sb.sem_op = 1;              /* Operacion; 1 => Liberar el recurso */
        sb.sem_flg = 0;             /* IPC_NOWAIT : No bloquea semop y devuelve EAGAIN.    ; SEM_UNDO: recuerda y reestable los cambios hechos al semaforo */
        arg.val = 1;
        //printf("press return\n"); getchar();
        for(sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++) {
            if (semop(semid, &sb, 1) == -1) {           /* Una vez cargada sembuf utilizo semop para liberar los semaforos que voy a usar */
                int e = errno;
                semctl(semid, 0, IPC_RMID);             /* Remove the specified semaphore set from the system. The semnum (2) parameter is ignored */
                errno = e;
                return -1;                              /* error, check errno */
            }
        }
    } 
    else if (errno == EEXIST) {             /* someone else got it first */
        int ready = 0;

        semid = semget(key, nsems, 0);      /* get the id */
        if (semid < 0) 
            return semid;                   /* error, check errno */

        /* wait for other process to initialize the semaphore: */
        arg.buf = &buf;
        for(i = 0; i < MAX_RETRIES && !ready; i++) 
        {
            semctl(semid, nsems-1, IPC_STAT, arg);      /* IPC_STAT Carga informacion en semid_ds estructura semun */
            if (arg.buf->sem_otime != 0)
                ready = 1;  
            else
                sleep(1);
        }
        if (!ready) 
        {
            errno = ETIME;
            return -1;
        }
    } 
    else 
        return semid;                       /* error, check errno */

    return semid;
}