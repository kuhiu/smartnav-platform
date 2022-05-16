#GCC = gcc
GCC = arm-linux-gnueabihf-gcc

FuzzyControl:
	@echo Generando $@.o...
	$(GCC) -o FuzzyControl.bin FuzzyControlv2.c fun.c initsem.c -Wall -lm
	$(GCC) -o readSTATE.bin readSTATE.c initsem.c -Wall 

send:
	scp -r ../Version2 root@192.168.100.130:/home/root/Tesis