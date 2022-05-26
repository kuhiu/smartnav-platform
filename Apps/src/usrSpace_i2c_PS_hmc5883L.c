#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
//#include <i2c/smbus.h>
#include "smbus.h"
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include <math.h>

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

int get_raw_x(int fd){

    int raw_x_lsb=0, raw_x_msb=0, raw_x=0;

    raw_x_lsb = i2c_smbus_read_byte_data (fd , QMC5883L_X_LSB);
    raw_x_msb = i2c_smbus_read_byte_data (fd , QMC5883L_X_MSB);

    raw_x = (raw_x_msb << 8) | raw_x_lsb;

    //printf("HMC5883L: data skipped: raw_x: %d \n", raw_x);

    if (raw_x >= 0x8000)    // To get negative value
        raw_x = raw_x - 0x10000;

    //printf("HMC5883L: data skipped: raw_x: %d \n", raw_x);
    
    return raw_x;
}

int get_raw_y(int fd){

    int raw_y_lsb=0, raw_y_msb=0, raw_y=0;

    raw_y_lsb = i2c_smbus_read_byte_data (fd , QMC5883L_Y_LSB);
    raw_y_msb = i2c_smbus_read_byte_data (fd , QMC5883L_Y_MSB);

    raw_y = (raw_y_msb << 8) | raw_y_lsb;

    if (raw_y >= 0x8000)    // To get negative value
        raw_y = raw_y - 0x10000;

    //printf("HMC5883L: data skipped: raw_y: %d \n", raw_y);

    return raw_y;
}

int get_raw_z(int fd){

    int raw_z_lsb=0, raw_z_msb=0, raw_z=0;

    raw_z_lsb = i2c_smbus_read_byte_data (fd , QMC5883L_Z_LSB);
    raw_z_msb = i2c_smbus_read_byte_data (fd , QMC5883L_Z_MSB);

    raw_z = (raw_z_msb << 8) | raw_z_lsb;

    if (raw_z >= 0x8000)    // To get negative value
        raw_z = raw_z - 0x10000;

    //printf("HMC5883L: data skipped: raw_y: %d \n", raw_y);

    return raw_z;
}

int main (void)
{ 
    int fd, i;
    int addr = 0x0D; /* The I2C address */

    int raw_x=0;
    int raw_y=0;
    int raw_z=0;

    float fx=0;
    float fy=0;

    float heading=0, acum_heading=0;

    int status;
    // Calibracion
    int xlow  = -12391;             // Calibracion
    int xhigh =   1301;
    int ylow  =  -6210;
    int yhigh =     75;   

    if ( (fd = open("/dev/i2c-0", O_WRONLY)) == -1)
    {
        printf("Error abriendo/dev/HMC5883L\n");
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        printf("Error ioctl HMC5883L: %s\n", strerror(errno));
        return -1;
    }

    //printf("HMC5883L: config: %08X, config2: %08X\n", i2c_smbus_read_byte_data (fd , QMC5883L_CONFIG), i2c_smbus_read_byte_data (fd , QMC5883L_CONFIG2));

    // printf("HMC5883L: Calibracion... \n");

    // for(i=0;i<500;i++)
    // {
    //     //printf("HMC5883L: Read raw data \n");
    //     status = i2c_smbus_read_byte_data (fd , QMC5883L_STATUS);
    //     //printf("HMC5883L: Status: %08X\n", status);

    //     if (status == 0X02){   // hubo ov
    //         printf("HMC5883L: Overflow \n");
    //         return -1;
    //     }

    //     if (status == 0X04){   // Data skipped
    //         raw_x = get_raw_x(fd);
    //         raw_y = get_raw_y(fd);
    //         raw_z = get_raw_z(fd);
    //         //printf("HMC5883L: data skipped: raw_x: %d, raw_y: %d \n", raw_x, raw_y);
    //         continue;
    //     }

    //     if (status == 0X01){   // New data available
    //         raw_x = get_raw_x(fd);
    //         raw_y = get_raw_y(fd);
    //         raw_z = get_raw_z(fd);
    //         printf("HMC5883L: new data: raw_x: %d, raw_y: %d \n", raw_x, raw_y);
    //     }

    //     else {                  // Data no available
    //         printf("HMC5883L: Data no disponible\n");
    //         usleep(100); // Sleep 50 mseg
    //         continue;
    //     }

    //     printf("HMC5883L: raw_x: %d, raw_y: %d \n", raw_x, raw_y);

    //     if(raw_x < xlow) 
    //         xlow = raw_x;
    //     if(raw_x > xhigh) 
    //         xhigh = raw_x;
    //     if(raw_y < ylow) 
    //         ylow = raw_y;
    //     if(raw_y > yhigh) 
    //         yhigh = raw_y;

    // }

    // printf("HMC5883L: La calibracion termino.\n");
    printf("HMC5883L: xlow: %d, xhigh: %d, ylow: %d, yhigh: %d\n", xlow, xhigh, ylow, yhigh);

    i=0;
    while(1)
    {
        status = i2c_smbus_read_byte_data (fd , QMC5883L_STATUS);
        status = status & 0x07; // Me quedo con los ultimos 3 bits

        //printf("status: %d \n", status);

        if ( (status & 0x02) == 0X02){   // hubo ov
            raw_x = get_raw_x(fd);
            raw_y = get_raw_y(fd);
            raw_z = get_raw_z(fd);
            continue;
        }

        if ( (status & 0x04) == 0X04){   // Data skipped
            raw_x = get_raw_x(fd);
            raw_y = get_raw_y(fd);
            raw_z = get_raw_z(fd);
            continue;
        }

        if ( (status & 0x01) == 0X01){   // New data available
            raw_x = get_raw_x(fd);
            raw_y = get_raw_y(fd);
            raw_z = get_raw_z(fd);
        }

        else {                  // Data no available
            //printf("HMC5883L: Data no disponible\n");
            usleep(100); // Sleep 50 mseg
            continue;
        }


        //printf("HMC5883L: raw_x: %d, raw_y: %d \n", raw_x, raw_y);

        raw_x = raw_x - (xhigh+xlow)/2;
        raw_y = raw_y - (yhigh+ylow)/2;

        fx = (float)raw_x/((float)xhigh-(float)xlow);
        fy = (float)raw_y/((float)yhigh-(float)ylow);

        //printf("Fx: %f, Fy: %f \n", fx, fy);

        heading = 180.0*atan2(fy,fx)/M_PI ;

        //printf("Heading: %f \n", heading);

        if(heading<=0) 
            heading += 360;

        printf("Heading: %f \n", heading);
        acum_heading = acum_heading + heading;

        if(i == 3)
        {
            i=0;
            //printf("Promedio: %f \n", acum_heading/3);
            acum_heading = 0;
        }

        //usleep(5000);
        i++;
    }

    close(fd);
    return 0;
}

