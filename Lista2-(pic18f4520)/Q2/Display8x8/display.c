#include <p18f4520.h>

int ponteiro;
int coluna;

unsigned char mensagem[] = {
// Espaços
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,

// W
0b11111111,
0b11111111,
0b11000000,
0b00011111,
0b11100111,
0b00011111,
0b11000000,

// E
0b11111111,
0b11111111,
0b01111110,
0b01101110,
0b01101110,
0b00000000,
0b00000000,

// L
0b11111111,
0b11111111,
0b00111111,
0b00111111,
0b00111111,
0b00000000,
0b00000000,

// L
0b11111111,
0b11111111,
0b00111111,
0b00111111,
0b00111111,
0b00000000,
0b00000000,

// I
0b11111111,
0b11111111,
0b00111100,
0b00111100,
0b00000000,
0b00111100,
0b00111100,

// G
0b11111111,
0b11111111,
0b00000100,
0b00100100,
0b00111100,
0b00000000,
0b00000000,

// T
0b11111111,
0b11111111,
0b11111100,
0b11111100,
0b00000000,
0b11111100,
0b11111100,

// O
0b11111111,
0b11111111,
0b00000000,
0b00000000,
0b00111100,
0b00000000,
0b00000000,

// N
0b11111111,
0b11111111,
0b00000000,
0b11111001,
0b11100111,
0b10011111,
0b00000000,

// Espaços
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
};

void delay(void){

	int i;
	for(i=0;i<800;i++){}
}

void mostrar(void){
	
	for(ponteiro=0;ponteiro < 60; ponteiro++){
			for(coluna=0;coluna < 8; coluna++){
				if(coluna <= 7){
					PORTD = 0b10000000 >> coluna;
				}else{
					PORTD = 0b10000000 >> coluna-6;
				}
				PORTC = (mensagem[ponteiro+coluna+7]);
				PORTB = (mensagem[ponteiro+coluna]);
				delay();
			}
	}
}

main(){

	TRISD = 0; // Varredura do painel 1 e 2
	TRISC = 0; // Barramento do painel 1
	TRISB = 0; // Barramento do painel 2
	ADCON1 = 0b00001111;

	while(1){

		mostrar();
	}
}