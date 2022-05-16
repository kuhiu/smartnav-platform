obj-m 		:= driver_MIOgpio_PS.o
PWD 		:= $(shell pwd)
KERNEL_DIR  = /home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/work/plnx_zynq7-xilinx-linux-gnueabi/linux-xlnx/4.19-xilinx-v2019.1+gitAUTOINC+9811303824-r0/linux-plnx_zynq7-standard-build
GCC 		= arm-linux-gnueabihf-


all:
	make ARCH=arm CROSS_COMPILE=$(GCC) -C $(KERNEL_DIR) M=$(PWD) modules -Wall

main:
	arm-linux-gnueabihf-gcc -o ControlLed ControlLed.c
	arm-linux-gnueabihf-gcc -o ControlTpg ControlTpg.c
	arm-linux-gnueabihf-gcc -o ControlVdma ControlVdma.c
	arm-linux-gnueabihf-gcc -o test test.c
	arm-linux-gnueabihf-gcc -o usrSpace_MIOgpio_PS usrSpace_MIOgpio_PS.c

clean:
	make ARCH=arm CROSS_COMPILE=$(GCC) -C $(KERNEL_DIR) M=$(PWD) clean

send:
	scp -r ./Apps ./Drivers ./ServidorPNG run.sh root@192.168.100.130:/home/root/Tesis
	
source:
	cd /tools/Xilinx/Vivado/2019.1/
	source settings64.sh
	cd ~/Escritorio/Tesis/pImagen/Petalinux_Projects/Drivers
