#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

#define MAX_RETRIES 10

#ifdef DEBUG 
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x) do {} while (0)
#endif 

union semun {
    int val;
    struct semid_ds *buf;
    short *array;
};

int initsem(key_t key, int nsems) ;