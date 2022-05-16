obj-m 		:= driver_leds_EMIOgpio_PL.o driver_buttons_EMIOgpio_PL_1.o driver_encoder_EMIOgpio_PL_1.o driver_encoder_EMIOgpio_PL_2.o driver_i2c_PS_ov7670.o driver_vdma.o driver_MIOgpio_PS.o driver_pwm_EMIOgpio_PL.o driver_EMIOgpio_PL.o driver_i2c_PS_hmc5883L.o
PWD 		:= $(shell pwd)

KERNEL_DIR  = /home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/work/plnx_zynq7-xilinx-linux-gnueabi/linux-xlnx/4.19-xilinx-v2019.1+gitAUTOINC+9811303824-r0/linux-plnx_zynq7-standard-build
#KERNEL_DIR = /home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/work-shared/plnx-zynq7/kernel-source

#GCC  = arm-xilinx-linux-gnueabi-
GCC = arm-linux-gnueabihf-
#GCC = arm-none-eabi-

all:
	make ARCH=arm CROSS_COMPILE=$(GCC) -C $(KERNEL_DIR) M=$(PWD) modules -Wall

clean:
	make ARCH=arm CROSS_COMPILE=$(GCC) -C $(KERNEL_DIR) M=$(PWD) clean

send:
	scp -r ./Apps ./Drivers ./ServidorPNG run.sh root@192.168.100.130:/home/root/Tesis

source:
	cd /tools/Xilinx/Vivado/2019.1/
	source settings64.sh
	cd ~/Escritorio/Tesis/Petalinux_Projects/Drivers

insmod:
	insmod Tesis/Drivers/driver_MIOgpio_PS.ko && insmod Tesis/Drivers/driver_pwm_EMIOgpio_PL.ko && insmod Tesis/Drivers/driver_EMIOgpio_PL.ko && insmod Tesis/Drivers/driver_i2c_PS_hmc5883L.ko && rmmod Tesis/Drivers/driver_i2c_PS_hmc5883L.ko && insmod Tesis/Drivers/driver_encoder_EMIOgpio_PL.ko
