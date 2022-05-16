#!/bin/bash

xterm -e 'sshpass -p 44501516 ssh -t root@192.168.100.130 "echo system.bin > /sys/class/fpga_manager/fpga0/firmware;
/sbin/insmod Tesis/Drivers/driver_encoder_EMIOgpio_PL_1.ko;
/sbin/insmod Tesis/Drivers/driver_encoder_EMIOgpio_PL_2.ko;
/sbin/insmod Tesis/Drivers/driver_i2c_PS_ov7670.ko;
/sbin/insmod Tesis/Drivers/driver_vdma.ko;
/sbin/insmod Tesis/Drivers/driver_MIOgpio_PS.ko;
/sbin/insmod Tesis/Drivers/driver_pwm_EMIOgpio_PL.ko;
/sbin/insmod Tesis/Drivers/driver_EMIOgpio_PL.ko;
/sbin/insmod Tesis/Drivers/driver_i2c_PS_hmc5883L.ko; 
/sbin/rmmod Tesis/Drivers/driver_i2c_PS_hmc5883L.ko;"' 

#xterm -e 'sshpass -p 44501516 ssh -f root@192.168.100.130 "./Tesis/Apps/usrSpace_top > /dev/null 2>&1 & disown;
#./Tesis/Version2/FuzzyControl.bin > /dev/null 2>&1 & disown;
#./Tesis/Apps/usrSpace_drive > /dev/null 2>&1 & disown"' &
#sleep 2 

xterm -hold -e 'sshpass -p 44501516 ssh -t root@192.168.100.130 "./Tesis/final/readSTATE.bin;
bash -l"' &

xterm -hold -e 'sshpass -p 44501516 ssh -f root@192.168.100.130 "./Tesis/Apps/usrSpace_top;
bash -l" ' &

xterm -hold -e 'sshpass -p 44501516 ssh -f root@192.168.100.130 "./Tesis/Version2/FuzzyControl.bin;
bash -l" ' &



