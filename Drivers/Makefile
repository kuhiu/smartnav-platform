SRC_DIR		= src/

obj-m 		+= $(SRC_DIR)/driver_leds_EMIOgpio_PL.o 
obj-m 		+= $(SRC_DIR)/driver_buttons_EMIOgpio_PL_1.o 
obj-m 		+= $(SRC_DIR)/driver_encoder_EMIOgpio_PL_1.o 
obj-m 		+= $(SRC_DIR)/driver_encoder_EMIOgpio_PL_2.o 
obj-m 		+= $(SRC_DIR)/driver_i2c_PS_ov7670.o 
obj-m 		+= $(SRC_DIR)/driver_vdma.o 
obj-m 		+= $(SRC_DIR)/driver_MIOgpio_PS.o 
obj-m 		+= $(SRC_DIR)/driver_pwm_EMIOgpio_PL_1.o 
obj-m 		+= $(SRC_DIR)/driver_pwm_EMIOgpio_PL_2.o 
obj-m 		+= $(SRC_DIR)/driver_EMIOgpio_PL.o 
obj-m 		+= $(SRC_DIR)/driver_i2c_PS_hmc5883L.o

PWD 		:= $(shell pwd)
KERNEL_DIR  = /media/kuhiu/5e8324a1-752c-4afa-961c-05d693d0ddc6/Tesis/Petalinux_Projects/Imagen/build/tmp/work/plnx_zynq7-xilinx-linux-gnueabi/linux-xlnx/4.19-xilinx-v2019.1+gitAUTOINC+9811303824-r0/linux-plnx_zynq7-standard-build
GCC 		= arm-linux-gnueabihf-

OUTPUT 		= gen

all:
	make ARCH=arm CROSS_COMPILE=$(GCC) -C $(KERNEL_DIR) M=$(PWD) modules
	mkdir -p ../gen/drivers
	cp ./src/*.ko ../gen/drivers
	make ARCH=arm CROSS_COMPILE=$(GCC) -C $(KERNEL_DIR) M=$(PWD) clean

clean:
	make ARCH=arm CROSS_COMPILE=$(GCC) -C $(KERNEL_DIR) M=$(PWD) clean

