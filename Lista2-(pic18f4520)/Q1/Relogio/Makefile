# MPLAB IDE generated this makefile for use with GNU make.
# Project: relogio.mcp
# Date: Sat Sep 25 15:24:27 2021

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

relogio.cof : relogio.o
	$(LD) /p18F4520 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "relogio.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"relogio.cof" /M"relogio.map" /W

relogio.o : relogio.c ../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f4520.h
	$(CC) -p=18F4520 "relogio.c" -fo="relogio.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "relogio.o" "relogio.cof" "relogio.hex"

