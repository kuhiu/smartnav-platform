#!/bin/bash

# If you need update FPGA logic uncomment this
#cp system.bin /lib/firmware/;
#echo 0 > /sys/class/fpga_manager/fpga0/flags;
#echo system.bin > /sys/class/fpga_manager/fpga0/firmware;

# Insmod all drivers
xterm -hold -e 'sshpass -p temppwd ssh -t ubuntu@192.168.100.130 "echo temppwd | sudo -S insmod ~/drivers/driver_encoder_EMIOgpio_PL_1.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_encoder_EMIOgpio_PL_2.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_buttons_EMIOgpio_PL_1.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_leds_EMIOgpio_PL.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_i2c_PS_ov7670.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_vdma.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_MIOgpio_PS.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_pwm_EMIOgpio_PL.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_EMIOgpio_PL.ko;
echo temppwd | sudo -S insmod ~/drivers/driver_i2c_PS_hmc5883L.ko; 
echo temppwd | sudo -S rmmod ~/drivers/driver_i2c_PS_hmc5883L.ko;"' 

# Change drivers permissions
xterm -e 'sshpass -p temppwd ssh -t ubuntu@192.168.100.130 "echo temppwd | sudo -S chown ubuntu:ubuntu /dev/chardev_encoder_EMIOgpio_PL_1;
echo temppwd | sudo -S chown ubuntu:ubuntu /dev/chardev_encoder_EMIOgpio_PL_2;
echo temppwd | sudo -S chown ubuntu:ubuntu /dev/chardev_buttons_EMIOgpio_PL_1;
echo temppwd | sudo -S chown ubuntu:ubuntu /dev/chardev_leds_EMIOgpio_PL;
echo temppwd | sudo -S chown ubuntu:ubuntu /dev/vdma_control_chardev;
echo temppwd | sudo -S chown ubuntu:ubuntu /dev/chardev_MIOgpio_PS;
echo temppwd | sudo -S chown ubuntu:ubuntu /dev/chardev_pwm_EMIOgpio_PL;
echo temppwd | sudo -S chown ubuntu:ubuntu /dev/chardev_EMIOgpio_PL;
echo temppwd | sudo -S chown ubuntu:ubuntu /dev/i2c-0;"' 

# Run VDMA 
xterm -e 'sshpass -p temppwd ssh -t ubuntu@192.168.100.130 "~/apps/ControlVdma;"'

# PNG Server
xterm -e 'sshpass -p temppwd ssh -t ubuntu@192.168.100.130 "echo temppwd | sudo -S python ~/PngServer/pngserver_ShowCNN.py;"' &

# Run top app
#xterm -hold -e 'sshpass -p 44501516 ssh -f ubuntu@192.168.100.130 "~/apps/usrSpace_top > /dev/null 2>&1"' &

#xterm -e 'sshpass -p 44501516 ssh -f ubuntu@192.168.100.130 "./Tesis/Version3/FuzzyControl.bin > /dev/null 2>&1"' &
#xterm -hold -e 'sshpass -p 44501516 ssh -f ubuntu@192.168.100.130 "./Tesis/Apps/usrSpace_buttons_EMIOgpio_PL_1"' &
#
#xterm -hold -e 'sshpass -p 44501516 ssh -t ubuntu@192.168.100.130 "./Tesis/final/readSTATE.bin;
#bash -l"' &
#sleep 1

#xterm -hold -e 'sshpass -p 44501516 ssh -t ubuntu@192.168.100.130 "python Tesis/ServidorPNG/pngserver_ShowCNN.py;
#bash -l"' &
#sleep 1

#xterm -hold -e 'sshpass -p 44501516 ssh -t ubuntu@192.168.100.130 "top;
#bash -l"' &
#sleep 2

#xterm -hold -e 'sshpass -p 44501516 ssh -t ubuntu@192.168.100.130 "./Tesis/Apps/ControlVdma;
#cd Tesis/final/sqzdet_c/;
#./main.bin;
#bash -l"' & 
