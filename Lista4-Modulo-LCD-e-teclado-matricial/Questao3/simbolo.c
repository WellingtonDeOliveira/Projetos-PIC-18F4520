#include <p18f4520.h>

#define barramento LATC

#define RS LATDbits.LATD0
#define EN1 LATDbits.LATD1

void delay_ms(void){
	
	int i;
	for(i = 0; i < 500; i++){} // 90ms
}

void delay_inicial(void){
	
	int i;
	for(i = 0; i < 5000; i++){}
}


void envia_dado_lcd(unsigned char dado){
	
	RS = 1;
	EN1 = 1;
	barramento = dado;
	EN1 = 0;
	delay_ms();
}

void envia_comando_lcd(unsigned char comando){
	
	RS = 0;
	EN1 = 1;
	barramento = comando;
	EN1 = 0;
	delay_ms();
}

void inicializa(void){

	delay_inicial(); // Espera inicializar
	envia_comando_lcd(0b00111000); // 2 linhas 5x8
	envia_comando_lcd(0b00001110); // cursor ligado
	envia_comando_lcd(0b00000001); // clear
}

void criar_caracter(void){

	envia_comando_lcd(0b01000000); // Manda para a linha 0x40
	envia_dado_lcd(0b00000100); // Começa a escrever caracter "0"
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00000000); // Fim do caracter "0"

	envia_dado_lcd(0b00000100); // Começa a escrever caracter "1"
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00000000); // Fim do caracter "1"

	envia_dado_lcd(0b00000100); // Começa a escrever caracter "2"
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00000000); // Fim do caracter "2"

	envia_dado_lcd(0b00000100); // Começa a escrever caracter "3"
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00010001);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00000000); // Fim do caracter "3"

	envia_dado_lcd(0b00000100); // Começa a escrever caracter "4"
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00011111);
	envia_dado_lcd(0b00000000); // Fim do caracter "4"
}

main(){
	
	TRISC = 0b00000000; // Barramento SAIDA
	TRISD = 0b00000000;// RS e EN como SAIDA
	inicializa();
	criar_caracter();
	envia_comando_lcd(0x80);
	while(1){
	
		envia_dado_lcd(0b00000000);
		envia_comando_lcd(0x80);
		delay_inicial();
		envia_dado_lcd(0b00000001);
		envia_comando_lcd(0x80);
		delay_inicial();
		envia_dado_lcd(0b00000010);
		envia_comando_lcd(0x80);
		delay_inicial();
		envia_dado_lcd(0b00000011);
		envia_comando_lcd(0x80);
		delay_inicial();
		envia_dado_lcd(0b00000100);
		envia_comando_lcd(0x80);
		delay_inicial();
	}
}