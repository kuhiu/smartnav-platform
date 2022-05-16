#!/bin/bash

xterm -e 'sshpass -p 44501516 ssh -t root@192.168.100.130 "cp system.bin /lib/firmware/;
echo 0 > /sys/class/fpga_manager/fpga0/flags;
echo system.bin > /sys/class/fpga_manager/fpga0/firmware;
/sbin/insmod Tesis/Drivers/driver_encoder_EMIOgpio_PL_1.ko;
/sbin/insmod Tesis/Drivers/driver_encoder_EMIOgpio_PL_2.ko;
/sbin/insmod Tesis/Drivers/driver_buttons_EMIOgpio_PL_1.ko;
/sbin/insmod Tesis/Drivers/driver_leds_EMIOgpio_PL.ko;
/sbin/insmod Tesis/Drivers/driver_i2c_PS_ov7670.ko;
/sbin/insmod Tesis/Drivers/driver_vdma.ko;
/sbin/insmod Tesis/Drivers/driver_MIOgpio_PS.ko;
/sbin/insmod Tesis/Drivers/driver_pwm_EMIOgpio_PL.ko;
/sbin/insmod Tesis/Drivers/driver_EMIOgpio_PL.ko;
/sbin/insmod Tesis/Drivers/driver_i2c_PS_hmc5883L.ko; 
/sbin/rmmod Tesis/Drivers/driver_i2c_PS_hmc5883L.ko;"' 

#xterm -e 'sshpass -p 44501516 ssh -f root@192.168.100.130 "./Tesis/Apps/usrSpace_top > /dev/null 2>&1"' &
#xterm -e 'sshpass -p 44501516 ssh -f root@192.168.100.130 "./Tesis/Version3/FuzzyControl.bin > /dev/null 2>&1"' &
#xterm -hold -e 'sshpass -p 44501516 ssh -f root@192.168.100.130 "./Tesis/Apps/usrSpace_buttons_EMIOgpio_PL_1"' &
#
#xterm -hold -e 'sshpass -p 44501516 ssh -t root@192.168.100.130 "./Tesis/final/readSTATE.bin;
#bash -l"' &
#sleep 1

#xterm -hold -e 'sshpass -p 44501516 ssh -t root@192.168.100.130 "python Tesis/ServidorPNG/pngserver_ShowCNN.py;
#bash -l"' &
#sleep 1

#xterm -hold -e 'sshpass -p 44501516 ssh -t root@192.168.100.130 "top;
#bash -l"' &
#sleep 2

#xterm -hold -e 'sshpass -p 44501516 ssh -t root@192.168.100.130 "./Tesis/Apps/ControlVdma;
#cd Tesis/final/sqzdet_c/;
#./main.bin;
#bash -l"' & 
