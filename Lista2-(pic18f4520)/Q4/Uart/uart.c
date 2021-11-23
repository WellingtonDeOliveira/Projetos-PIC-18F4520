#include <p18f4520.h>

#define tx PORTCbits.RC0
#define rx PORTCbits.RC1

char dado[8];

void delay(void){ // 1/1200 = 833us

	unsigned char i;
	for(i=0;i<=139;i++){}
}

void meio_delay(void){ // 1/1200 = 833us/2 = 416

	unsigned char i;
	for(i=0;i<=126;i++){}
	for(i=0;i<=20;i++){}
}

void transmite_serial(char controle){ // dado = 01000001 = A so que comeca no ultimo

	int mascara = 0b00000001;
	int x;

	tx = 1;
	delay(); //repouso
	tx = 0;
	delay(); //start
	for(x = 0; x < 8 ; x++){
		tx = dado[x] && mascara << x; 
		delay();
	}
    tx = 1; // stop bit
	delay();
}

char recebe_serial(void){

	char mascara;
	int i;

	while(rx){}
	meio_delay();
	for(i=0;i<8;i++){
		delay();
		dado[i] = rx;
	}

	return mascara;
}

main(){
	
	TRISCbits.RC0 = 0; // tx -> saida
	TRISCbits.RC1 = 1; // rx -> entrada

	meio_delay();
	delay();
	while(1){
		transmite_serial(recebe_serial());
	}
}