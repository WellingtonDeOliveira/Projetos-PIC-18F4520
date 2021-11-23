# MPLAB IDE generated this makefile for use with GNU make.
# Project: display.mcp
# Date: Fri Oct 01 13:28:35 2021

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

display.cof : display.o
	$(LD) /p18F4520 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "display.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"display.cof" /M"display.map" /W

display.o : display.c ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f4520.h
	$(CC) -p=18F4520 "display.c" -fo="display.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "display.o" "display.cof" "display.hex"

