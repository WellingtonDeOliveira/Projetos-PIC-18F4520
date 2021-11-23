#include <p18f4520.h>

#define barramento LATC

#define d1 LATDbits.LATD0
#define d2 LATDbits.LATD1
#define d3 LATDbits.LATD2
#define d4 LATDbits.LATD3
#define d5 LATDbits.LATD4
#define d6 LATDbits.LATD5
#define d7 LATDbits.LATD6
#define d8 LATDbits.LATD7

#define l1 PORTBbits.RB0
#define l2 PORTBbits.RB1
#define l3 PORTBbits.RB2
#define l4 PORTBbits.RB3

#define c1 PORTBbits.RB4
#define c2 PORTBbits.RB5
#define c3 PORTBbits.RB6

void varre_display(void);
void conta(void);

unsigned char dh=0, uh=0, dm=0, um=0, ds=0, us=0, espaco=10;
char aux=1, aux1=-2, aux2=-2, aux3=-2, aux4=-2, aux5=-2, aux6=-2;

unsigned char tecla;

unsigned char converte_7segmentos [11] = {

0b00111111, // 0
0b00000110, // 1
0b01011011, // 2
0b01001111, // 3
0b01100110, // 4
0b01101101, // 5
0b01111101, // 6
0b00000111, // 7
0b01111111, // 8
0b01101111, // 9
0b01000000, // -
};

void delay_ms(void){
	
	int i;
	for(i = 0; i < 200; i++){} // 3,96ms
}

void delay_s(void){
	
	unsigned int i;
	conta();
	for(i = 0; i < 31; i++){ // 988ms
		varre_display();
	}
}

void delay_ajuste(void){
	
	unsigned int i;
	for(i = 0; i < 45000; i++){} // 990ms
}

void conta(void){

	us++;
	if(us >=10){
		us = 0;
		ds++;
		if(ds >= 6){
			ds = 0;
			um++;
			if(um >= 10){
				um = 0;
				dm++;
				if(dm >= 6){
					dm = 0;
					uh++;
					if(dh == 2 && uh >= 4){
						uh = dh = 0;
					}else if(uh >= 10){
						uh = 0;
						dh++;
					}
				}
			}
		}
	}
}

void varre_display(void){

	d1=d2=d3=d4=d5=d6=d7=d8=1; // Dessabilida todos os displays
	
	barramento = converte_7segmentos[dh];
	d1=0; // habilita display
	delay_ms(); //tempo
	d1=1; // dessabilida

	barramento = converte_7segmentos[uh];
	d2=0; // habilita display
	delay_ms(); //tempo
	d2=1; // dessabilida

	barramento = converte_7segmentos[espaco];
	d3=0; // habilita display
	delay_ms(); //tempo
	d3=1; // dessabilida

	barramento = converte_7segmentos[dm];
	d4=0; // habilita display
	delay_ms(); //tempo
	d4=1; // dessabilida

	barramento = converte_7segmentos[um];
	d5=0; // habilita display
	delay_ms(); //tempo
	d5=1; // dessabilida

	barramento = converte_7segmentos[espaco];
	d6=0; // habilita display
	delay_ms(); //tempo
	d6=1; // dessabilida
	
	barramento = converte_7segmentos[ds];
	d7=0; // habilita display
	delay_ms(); //tempo
	d7=1; // dessabilida

	barramento = converte_7segmentos[us];
	d8=0; // habilita display
	delay_ms(); //tempo
	d8=1; // dessabilida
}

int varre_teclado(void){

	int i = 0;
	for(i; i < 4; i++){ // Varredura de C1
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
	}
	i=0;
	for(i; i < 4; i++){// Varredura C2
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
	}
	i=0;
	for(i; i < 4; i++){// Varredura C3
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
	}
	return 30;
}

void mostrar(void){
	
	if(dh != -1 && aux6 == -2){
		dh=uh=dm=um=ds=us=-1;
	}
	if(tecla != 11 && tecla != 10){
		if(us == -1 && tecla != 30 && ds != aux1){
			us = tecla;
			aux1 = us;
		}else if(us == aux1 && tecla != 30 && aux2 != us){
			ds = aux1;
			us = tecla;
			aux2 = us;
		}else if(ds == aux1 && tecla != 30 && aux3 != us){
			um = aux1;
			ds = aux2;
			us = tecla;
			aux3 = us;
		}else if(um == aux1 && tecla != 30 && aux4 != us){
			dm = aux1;
			um = aux2;
			ds = aux3;
			us = tecla;
			aux4 = us;
		}else if(dm == aux1 && tecla != 30 && aux5 != us){
			uh = aux1;
			dm = aux2;
			um = aux3;
			ds = aux4;
			us = tecla;
			aux5 = us;
		}else if(uh == aux1 && tecla != 30 && aux6 != us){
			dh = aux1;
			uh = aux2;
			dm = aux3;
			um = aux4;
			ds = aux5;
			us = tecla;
			aux6 = us;
		}
	}
}

void verifica(void){

	if(aux6 != -2){
		if(us < 10 ){
			if(ds < 6){
				if(um < 10){
					if(dm < 6){
						if((dh==2 && uh < 4) || (dh < 2 && uh < 10)){
							aux = 0;
							delay_s();
						}else{
							dh=uh=dm=um=ds=us=-1;
							aux1=aux2=aux3=aux4=aux5=aux6=-2;
						}
					}else{
						dh=uh=dm=um=ds=us=-1;
						aux1=aux2=aux3=aux4=aux5=aux6=-2;
					}
				}else{
					dh=uh=dm=um=ds=us=-1;
					aux1=aux2=aux3=aux4=aux5=aux6=-2;
				}
			}else{
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
			}
		}else{
			dh=uh=dm=um=ds=us=-1;
			aux1=aux2=aux3=aux4=aux5=aux6=-2;
		}
	}
}

void ajuste(){

	if(tecla == 11){
		delay_ajuste();
		if(tecla == 11){
			delay_ajuste();
			if(tecla == 11){
				dh=uh=dm=um=ds=us=-1;
				aux=1;
				while(aux){
					mostrar();
					varre_display();
					tecla = varre_teclado();
					verifica();
				}
			}
		}else{
			delay_s();
		}
	}else{
		delay_s();
	}
}
main(){
	
	TRISC = 0b00000000; // Barramento SAIDA
	TRISD = 0b00000000; // Habilidadores SAIDA
	TRISB = 0b00001111; // Linhas como saidas e Colunas como entrada
	ADCON1 = 0b00001111;
	while(1){

		delay_s();
		tecla = varre_teclado();
		ajuste();
	}
}