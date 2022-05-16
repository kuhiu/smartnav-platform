OPT = -Ofast -Wall

main:
	arm-linux-gnueabihf-gcc -o ControlLed ControlLed.c -Wall
	arm-linux-gnueabihf-gcc -o ControlTpg ControlTpg.c -Wall
	arm-linux-gnueabihf-gcc -o ControlVdma ControlVdma.c -Wall
	arm-linux-gnueabihf-gcc -o test test.c -Wall
	arm-linux-gnueabihf-gcc -o usrSpace_MIOgpio_PS usrSpace_MIOgpio_PS.c -Wall
	arm-linux-gnueabihf-gcc -o usrSpace_pwm_EMIOgpio_PL usrSpace_pwm_EMIOgpio_PL.c -Wall
	arm-linux-gnueabihf-gcc -o testingdeadtime testingdeadtime.c -Wall
	arm-linux-gnueabihf-gcc -o usrSpace_encoder_EMIOgpio_PL usrSpace_encoder_EMIOgpio_PL.c -Wall
	arm-linux-gnueabihf-gcc -o usrSpace_buttons_EMIOgpio_PL_1 usrSpace_buttons_EMIOgpio_PL_1.c -Wall
	
	arm-linux-gnueabihf-gcc -o usrSpace_EMIOgpio_PL usrSpace_EMIOgpio_PL.c -Wall
	arm-linux-gnueabihf-gcc -o usrSpace_i2c_PS_hmc5883L usrSpace_i2c_PS_hmc5883L.c -Wall -lm -L/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/lib -lpthread -li2c -I/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/include/i2c
	arm-linux-gnueabihf-gcc -o usrSpace_top usrSpace_top.c ./Funciones/func.c initsem.c -Wall -lm -L/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/lib -lpthread -li2c -I/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/include/i2c
	arm-linux-gnueabihf-gcc -o usrSpace_drive usrSpace_drive.c initsem.c -Wall -lm -L/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/lib -lpthread -li2c -I/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/include/i2c
	arm-linux-gnueabihf-gcc -o usrSpace_drive_v3 usrSpace_drive_v3.c initsem.c -Wall -lm -L/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/lib -lpthread -li2c -I/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/include/i2c
	
asd:
	insmod Tesis/Drivers/driver_MIOgpio_PS.ko && insmod Tesis/Drivers/driver_pwm_EMIOgpio_PL.ko && insmod Tesis/Drivers/driver_EMIOgpio_PL.ko && insmod Tesis/Drivers/driver_i2c_PS_hmc5883L.ko && rmmod Tesis/Drivers/driver_i2c_PS_hmc5883L.ko && insmod Tesis/Drivers/driver_encoder_EMIOgpio_PL.ko