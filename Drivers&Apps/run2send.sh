#!/bin/bash

echo ENTRE A MI BASH > /dev/kmsg 
cp /home/root/system.bin /lib/firmware/ 
echo 0 > /sys/class/fpga_manager/fpga0/flags 
echo system.bin > /sys/class/fpga_manager/fpga0/firmware 
echo FPGA programada > /dev/kmsg 
echo Instalo drivers > /dev/kmsg 
/sbin/insmod /home/root/Tesis/Drivers/driver_encoder_EMIOgpio_PL_1.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_encoder_EMIOgpio_PL_2.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_buttons_EMIOgpio_PL_1.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_i2c_PS_ov7670.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_vdma.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_MIOgpio_PS.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_pwm_EMIOgpio_PL.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_EMIOgpio_PL.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_i2c_PS_hmc5883L.ko 
/sbin/rmmod /home/root/Tesis/Drivers/driver_i2c_PS_hmc5883L.ko 
/sbin/insmod /home/root/Tesis/Drivers/driver_leds_EMIOgpio_PL.ko
echo Drivers instalados > /dev/kmsg 
echo Pongo a correr mis programas > /dev/kmsg 
./home/root/Tesis/Apps/usrSpace_top > /dev/null 2>&1 & disown &
./home/root/Tesis/Version3/FuzzyControl.bin > /dev/null 2>&1 & disown &
./home/root/Tesis/Apps/usrSpace_buttons_EMIOgpio_PL_1 > /dev/null 2>&1 & disown &

#python /home/root/Tesis/ServidorPNG/pngserver_ShowCNN.py &

./home/root/Tesis/Apps/ControlVdma 
cd /home/root/Tesis/final/sqzdet_c/ 
./main.bin > /dev/null 2>&1 & disown &


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
