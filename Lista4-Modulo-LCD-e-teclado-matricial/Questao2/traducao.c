#include <p18f4520.h>

#define barramento LATC

#define RS LATDbits.LATD0
#define EN1 LATDbits.LATD1
#define EN2 LATDbits.LATD2

void delay_ms(void){
	
	int i;
	for(i = 0; i < 500; i++){} // 90ms
}

void delay_inicial(void){
	
	int i;
	for(i = 0; i < 5000; i++){}
}


void envia_dado_lcd(unsigned char dado, unsigned char display){
	
	unsigned char parte1 = dado >> 4; 
	unsigned char parte2 = dado; 
	
	if(display == 1){
		RS = 1;
		EN1 = 1;
		barramento = parte1;
		EN1 = 0;
		delay_ms();
		EN1 = 1;
		barramento = parte2;
		EN1 = 0;
		delay_ms();
	}else if(display == 2){
		RS = 1;
		EN2 = 1;
		barramento = parte1;
		EN2 = 0;
		delay_ms();
		EN2 = 1;
		barramento = parte2;
		EN2 = 0;
		delay_ms();		
	}else{
		RS = 1;
		EN1 = EN2 = 1;
		barramento = parte1;
		EN1 = EN2 = 0;
		delay_ms();
		EN1 = EN2 = 1;
		barramento = parte2;
		EN1 = EN2 = 0;
		delay_ms();
	}
}

void envia_comando_lcd(unsigned char comando){
	
	unsigned char parte1 = comando >> 4; 
	unsigned char parte2 = comando; 
	RS = 0;
	EN1 = EN2 = 1;
	barramento = parte1;
	EN1 = EN2 = 0;
	delay_ms();
	EN1 = EN2 = 1;
	barramento = parte2;
	EN1 = EN2 = 0;
	delay_ms();
}

void inicializa(void){

	delay_inicial(); // Espera inicializar
	envia_comando_lcd(0b0010);	// Configura interface 4 bits
	envia_comando_lcd(0b0010);

	envia_comando_lcd(0b1000);	// 2 linhas 5x8

	envia_comando_lcd(0b0000); // ligar cursor
	envia_comando_lcd(0b1110);	

	envia_comando_lcd(0b0000); // clear
	envia_comando_lcd(0b0001);
}

main(){
	
	TRISC = 0b00000000; // Barramento SAIDA
	TRISD = 0b00000000;// RS e EN como SAIDA
	inicializa();
	while(1){
	
		envia_comando_lcd(0x80);
		envia_dado_lcd('E',1);
		envia_dado_lcd('s',1);
		envia_dado_lcd('c',1);
		envia_dado_lcd('o',1);
		envia_dado_lcd('l',1);
		envia_dado_lcd('a',1);

		envia_dado_lcd('S',2);
		envia_dado_lcd('c',2);
		envia_dado_lcd('h',2);
		envia_dado_lcd('o',2);
		envia_dado_lcd('o',2);
		envia_dado_lcd('l',2);
	}
}