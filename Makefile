# MPLAB IDE generated this makefile for use with GNU make.
# Project: Sensor.mcp
# Date: Fri Dec 04 14:02:18 2015

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

Sensor.cof : Test.o
	$(LD) /p18F45K22 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "Test.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"Sensor.cof" /M"Sensor.map" /W

Test.o : Test.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/delays.h LCD4xlib.h Test.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18cxxx.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f45k22.h LCDdefs.h
	$(CC) -p=18F45K22 "Test.c" -fo="Test.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Test.o" "Sensor.cof" "Sensor.hex"

