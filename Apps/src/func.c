#include "func.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Variables sensores de distancia*/
//////////////////////////////////////////////////////////////////////////////////////////////////////

long long int to_distance_cm (long long int time)
{
    long long int distance;

    distance = time*0.01715;

    if ( (distance > 500) || (distance < 0) )
        distance = 500;

    return distance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Variables brujula */
//////////////////////////////////////////////////////////////////////////////////////////////////////

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


int calibracion_HMC5883L(int fd, int *xlow, int *xhigh, int *ylow, int *yhigh)
{
    int i;
    int status;
    int raw_x=0, raw_y=0, raw_z=0;

    for(i=0;i<HMC5883L_cal_loop;)
    {
        status = i2c_smbus_read_byte_data (fd , QMC5883L_STATUS) & 0x7;
        printf("status es= %d e i es = %d\n", status, i);
        if ( (status & 0x02) == 0X02){   // hubo ov
            return -1;
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
            i++;
        }

        else {                  // Data no available
            usleep(10000); // Sleep 10 mseg
            continue;
        }
        if(raw_x < *xlow) 
            *xlow = raw_x;
        if(raw_x > *xhigh) 
            *xhigh = raw_x;
        if(raw_y < *ylow) 
            *ylow = raw_y;
        if(raw_y > *yhigh) 
            *yhigh = raw_y;
    }

    return 0;
}

int calibracion_HMC5883L_yz(int fd, int *zlow, int *zhigh, int *ylow, int *yhigh)
{
    int i;
    int status;
    int raw_x=0, raw_y=0, raw_z=0;

    for(i=0;i<HMC5883L_cal_loop;)
    {
        status = i2c_smbus_read_byte_data (fd , QMC5883L_STATUS) & 0x7;
        printf("status es= %d e i es = %d\n", status, i);
        if ( (status & 0x02) == 0X02){   // hubo ov
            return -1;
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
            i++;
        }

        else {                  // Data no available
            usleep(10000); // Sleep 10 mseg
            continue;
        }
        if(raw_z < *zlow) 
            *zlow = raw_z;
        if(raw_z > *zhigh) 
            *zhigh = raw_z;
        if(raw_y < *ylow) 
            *ylow = raw_y;
        if(raw_y > *yhigh) 
            *yhigh = raw_y;
    }

    return 0;
}

int get_headeing_degree(int fd, int xlow, int xhigh, int ylow, int yhigh)
{
    int status;
    float raw_x=0, raw_y=0, raw_z=0;
    float fx=0;
    float fy=0;
    float heading=0;

    status = i2c_smbus_read_byte_data (fd , QMC5883L_STATUS);
    status = status & 0x07; // Me quedo con los ultimos 3 bits

    //printf("status: %08X \n", status);

    if ( (status & 0x02) == 0X02){   // hubo ov
        raw_x = get_raw_x(fd);
        raw_y = get_raw_y(fd);
        raw_z = get_raw_z(fd);
        return -1;
    }

    if ( (status & 0x04) == 0X04){   // Data skipped
        raw_x = get_raw_x(fd);
        raw_y = get_raw_y(fd);
        raw_z = get_raw_z(fd);
        return -2;
    }

    if ( (status & 0x01) == 0X01){   // New data available
        raw_x = get_raw_x(fd);
        raw_y = get_raw_y(fd);
        raw_z = get_raw_z(fd);
    }

    else {                  // Data no available
        return -3;
    }

    printf("raw_x: %f, raw_y: %f \n", raw_x, raw_y);

    raw_x = raw_x - ((float)xhigh+(float)xlow)/2;
    raw_y = raw_y - ((float)yhigh+(float)ylow)/2;

    printf("POST OFFSET= raw_x: %f, raw_y: %f \n", raw_x, raw_y);

    fx = (float)raw_x / (((float)xhigh-(float)xlow)/2);
    fy = (float)raw_y / (((float)yhigh-(float)ylow)/2);

    printf("Fx: %f, Fy: %f \n", fx, fy);

    heading = 180.0*atan2(fy,fx)/M_PI ;

    //printf("Heading: %f \n", heading);

    if(heading<=0) 
        heading += 360;

    return heading;
}

int get_headeing_degree_yz(int fd, int zlow, int zhigh, int ylow, int yhigh)
{
    int status;
    float raw_x=0, raw_y=0, raw_z=0;
    float fz=0;
    float fy=0;
    float heading=0;

    status = i2c_smbus_read_byte_data (fd , QMC5883L_STATUS);
    status = status & 0x07; // Me quedo con los ultimos 3 bits

    //printf("status: %08X \n", status);

    if ( (status & 0x02) == 0X02){   // hubo ov
        raw_x = get_raw_x(fd);
        raw_y = get_raw_y(fd);
        raw_z = get_raw_z(fd);
        return -1;
    }

    if ( (status & 0x04) == 0X04){   // Data skipped
        raw_x = get_raw_x(fd);
        raw_y = get_raw_y(fd);
        raw_z = get_raw_z(fd);
        return -2;
    }

    if ( (status & 0x01) == 0X01){   // New data available
        raw_x = get_raw_x(fd);
        raw_y = get_raw_y(fd);
        raw_z = get_raw_z(fd);
    }

    else {                  // Data no available
        return -3;
    }

    printf("raw_z: %f, raw_y: %f \n", raw_z, raw_y);

    raw_z = raw_z - ((float)zhigh+(float)zlow)/2;
    raw_y = raw_y - ((float)yhigh+(float)ylow)/2;

    printf("POST OFFSET= raw_z: %f, raw_y: %f \n", raw_z, raw_y);

    fz = (float)raw_z / (((float)zhigh-(float)zlow)/2);
    fy = (float)raw_y / (((float)yhigh-(float)ylow)/2);

    printf("Fz: %f, Fy: %f \n", fz, fy);

    heading = 180.0*atan2(fy,fz)/M_PI ;

    //printf("Heading: %f \n", heading);

    if(heading<=0) 
        heading += 360;

    return heading;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/* Variables encoder */
//////////////////////////////////////////////////////////////////////////////////////////////////////

float get_revoluciones_rpm(__s64 in)
{
    if (in == -1) 
        return 0;
    else
        return (((60 * 1000000)/ ((float)in*5) ));
}
    
float get_distance_m(unsigned int in){
    return (in*2*M_PI*3*5/100);
}