#!/bin/bash

echo "InstallDrivers script"
sudo insmod /home/ubuntu/drivers/driver_encoder_EMIOgpio_PL_1.ko;
sudo insmod /home/ubuntu/drivers/driver_encoder_EMIOgpio_PL_2.ko;
sudo insmod /home/ubuntu/drivers/driver_buttons_EMIOgpio_PL_1.ko;
sudo insmod /home/ubuntu/drivers/driver_leds_EMIOgpio_PL.ko;
sudo insmod /home/ubuntu/drivers/driver_i2c_PS_ov7670.ko;
sudo insmod /home/ubuntu/drivers/driver_vdma.ko;
sudo insmod /home/ubuntu/drivers/driver_MIOgpio_PS.ko;
sudo insmod /home/ubuntu/drivers/driver_pwm_EMIOgpio_PL.ko;
sudo insmod /home/ubuntu/drivers/driver_EMIOgpio_PL.ko;
sudo insmod /home/ubuntu/drivers/driver_i2c_PS_hmc5883L.ko; 
sudo rmmod  /home/ubuntu/drivers/driver_i2c_PS_hmc5883L.ko;
sudo /home/ubuntu/apps/ControlVdma;

sudo /home/ubuntu/buttonsControl/buttonsControl;