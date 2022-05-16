#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include "smbus.h"
#include <sys/ioctl.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Semaforo
union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

#define MAX_RETRIES 10
int initsem(key_t key, int nsems);

//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Variables sensores de distancia*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define BYTE2READ_MIOgpio_PS 8*3    // 3 bytes

long long int to_distance_cm (long long int time);

//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Variables brujula */
//////////////////////////////////////////////////////////////////////////////////////////////////////

#define HMC5883L_cal_loop         300
#define CALIBRACION_ENABLE          0
#define HMC5883L_I2C_ADDRESS     0x0D       // Fake board: 0x0D, original board: 0x1E

/* Registers */
#define QMC5883L_X_LSB           0x00
#define QMC5883L_X_MSB           0x01
#define QMC5883L_Y_LSB           0x02
#define QMC5883L_Y_MSB           0x03
#define QMC5883L_Z_LSB           0x04
#define QMC5883L_Z_MSB           0x05
#define QMC5883L_STATUS          0x06
#define QMC5883L_TEMP_LSB        0x07
#define QMC5883L_TEMP_MSB        0x08
#define QMC5883L_CONFIG          0x09
#define QMC5883L_CONFIG2         0x0A
#define QMC5883L_RESET           0x0B
#define QMC5883L_RESERVED        0x0C
#define QMC5883L_CHIP_ID         0x0D

int get_raw_x(int fd);
int get_raw_y(int fd);
int get_raw_z(int fd);
int calibracion_HMC5883L(int fd, int *xlow, int *xhigh, int *ylow, int *yhigh);
int get_headeing_degree(int fd, int xlow, int xhigh, int ylow, int yhigh);
int calibracion_HMC5883L_yz(int fd, int *zlow, int *zhigh, int *ylow, int *yhigh);
int get_headeing_degree_yz(int fd, int zlow, int zhigh, int ylow, int yhigh);
//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Variables encoder */
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define BYTE2READ_encoder       32*4

float get_revoluciones_rpm(__s64 in);
float get_distance_m(unsigned int in);
