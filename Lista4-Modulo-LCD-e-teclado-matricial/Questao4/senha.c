#include <p18f4520.h>

#define led PORTCbits.RC0

#define l1 PORTDbits.RD0
#define l2 PORTDbits.RD1
#define l3 PORTDbits.RD2
#define l4 PORTDbits.RD3

#define c1 PORTDbits.RD4
#define c2 PORTDbits.RD5
#define c3 PORTDbits.RD6

void gerar_valor(void);

unsigned int tecla;

int valor, aux1 = -2, aux2 = -2, aux3 = -2, aux4 = -2;

void delay_s(void){
	
	int i;
	for(i = 0; i < 31000; i++){}
}

int varre_teclado(void){

	c1=0;
	c2=1;
	c3=1;
	if(!l1){
		while(!l1){};
		return 1;
	}if(!l2){
		while(!l2){};
		return 4;
	}if(!l3){
		while(!l3){};
		return 7;
	}if(!l4){
		while(!l4){};
		return 10;
	}
	c1=1;
	c2=0;
	c3=1;
	if(!l1){
		while(!l1){};
		return 2;
	}if(!l2){
		while(!l2){};
		return 5;
	}if(!l3){
		while(!l3){};
		return 8;
	}if(!l4){
		while(!l4){};
		return 0;
	}
	c1=1;
	c2=1;
	c3=0;
	if(!l1){
		while(!l1){};
		return 3;
	}if(!l2){
		while(!l2){};
		return 6;
	}if(!l3){
		while(!l3){};
		return 9;
	}if(!l4){
		while(!l4){};
		return 11;
	}
	return 30;
}

void guarda_valor(void){

	if(tecla != 30 && tecla != 10 && tecla != 11){
		
		if(aux1==-2){
			aux1 = tecla;
		}else if(aux2==-2){
			aux2 = aux1;
			aux1 = tecla;
		}else if(aux3==-2){
			aux3=aux2;
			aux2=aux1;
			aux1=tecla;
		}else if(aux4==-2){
			aux4=aux3;
			aux3=aux2;
			aux2=aux1;
			aux1=tecla;
			gerar_valor();
		}
	}
}

void gerar_valor(void){

	unsigned int cache1=0,cache2=0,cache3=0;
	unsigned int a,b,c,d,e;
	if(aux4 != -2){
		c=aux4;
		cache3 = (c * 1000);
	}if(aux3 != -2){
		d=aux3;
		cache2 = (d * 100);
	}if(aux2 != -2){
		e=aux2;
		cache1 = (e * 10);
	}
	valor = (cache3+cache2+cache1+aux1);
}

void verifica(void){

	if(tecla != 30){
		if(valor == 1234){
			led = 1;
			while(1){};
		}else{
			led = 0;
		}
	}else{
		led = 0;
	}
}

main(){
	
	TRISC = 0b00000000; // Barramento SAIDA
	TRISD = 0b00001111; // Linhas como saidas e Colunas como entrada
	while(1){

		delay_s();
		tecla = varre_teclado();
		guarda_valor();
		verifica();	
	}
}