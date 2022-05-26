GCC 		= arm-linux-gnueabihf-gcc
LIBS 		= -lm -lpthread -li2c
LIBS_DIR 	= -L/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/lib
INC_DIR 	= -I/home/martin/Escritorio/Tesis/Petalinux_Projects/Imagen/build/tmp/sysroots-components/cortexa9t2hf-neon/i2c-tools/usr/include/i2c -I./inc
FLAGS		= -Wall
SRC_DIR 	= src
SEM_FILE	= src/initsem.c
OUTPUT_DIR	= ../gen/apps

all:
	mkdir -p $(OUTPUT_DIR)
	$(GCC) -o $(OUTPUT_DIR)/ControlLed 						$(SRC_DIR)/ControlLed.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/ControlTpg 						$(SRC_DIR)/ControlTpg.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/ControlVdma 					$(SRC_DIR)/ControlVdma.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/test 							$(SRC_DIR)/test.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_MIOgpio_PS 			$(SRC_DIR)/usrSpace_MIOgpio_PS.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_pwm_EMIOgpio_PL 		$(SRC_DIR)/usrSpace_pwm_EMIOgpio_PL.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/testingdeadtime 				$(SRC_DIR)/testingdeadtime.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_encoder_EMIOgpio_PL 	$(SRC_DIR)/usrSpace_encoder_EMIOgpio_PL.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_buttons_EMIOgpio_PL_1 	$(SRC_DIR)/usrSpace_buttons_EMIOgpio_PL_1.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_EMIOgpio_PL 			$(SRC_DIR)/usrSpace_EMIOgpio_PL.c $(FLAGS)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_i2c_PS_hmc5883L 		$(SRC_DIR)/usrSpace_i2c_PS_hmc5883L.c $(FLAGS) $(LIBS) $(LIBS_DIR) $(INC_DIR)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_top 					$(SRC_DIR)/usrSpace_top.c $(SRC_DIR)/func.c $(SEM_FILE) $(FLAGS) $(LIBS) $(LIBS_DIR) $(INC_DIR)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_drive 					$(SRC_DIR)/usrSpace_drive.c $(SEM_FILE) $(FLAGS) $(LIBS) $(LIBS_DIR)  $(INC_DIR)
	$(GCC) -o $(OUTPUT_DIR)/usrSpace_drive_v3 				$(SRC_DIR)/usrSpace_drive_v3.c $(SEM_FILE) $(FLAGS) $(LIBS) $(LIBS_DIR) $(INC_DIR)