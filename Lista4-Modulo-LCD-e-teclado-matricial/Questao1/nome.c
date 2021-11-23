#include <p18f4520.h>

#define barramento LATC

#define RS LATDbits.LATD0
#define EN LATDbits.LATD1

void delay_ms(void){
	
	int i;
	for(i = 0; i < 500; i++){} // 90ms
}

void delay_inicial(void){
	
	int i;
	for(i = 0; i < 5000; i++){}
}


void envia_dado_lcd(unsigned char dado){
	
	unsigned char parte1 = dado >> 4; 
	unsigned char parte2 = dado; 
	RS = 1;
	EN = 1;
	barramento = parte1;
	EN = 0;
	delay_ms();
	EN = 1;
	barramento = parte2;
	EN = 0;
	delay_ms();
}

void envia_comando_lcd(unsigned char comando){
	
	unsigned char parte1 = comando >> 4; 
	unsigned char parte2 = comando; 
	RS = 0;
	EN = 1;
	barramento = parte1;
	EN = 0;
	delay_ms();
	EN = 1;
	barramento = parte2;
	EN = 0;
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
	TRISD = 0b00000000; // intro e enable como SAIDA
	inicializa();
	while(1){
	
		envia_comando_lcd(0x80);
		envia_dado_lcd('W');
		envia_dado_lcd('e');
		envia_dado_lcd('l');
		envia_dado_lcd('l');
		envia_dado_lcd('i');
		envia_dado_lcd('n');
		envia_dado_lcd('g');
		envia_dado_lcd('t');
		envia_dado_lcd('o');
		envia_dado_lcd('n');
		envia_dado_lcd(' ');
		
	}
}