#include <p18f4520.h>

#define barramento LATC

#define d1 LATDbits.LATD0
#define d2 LATDbits.LATD1
#define d3 LATDbits.LATD2
#define d4 LATDbits.LATD3
#define d5 LATDbits.LATD4
#define d6 LATDbits.LATD5

#define l1 PORTBbits.RB0
#define l2 PORTBbits.RB1
#define l3 PORTBbits.RB2
#define l4 PORTBbits.RB3

#define c1 PORTBbits.RB4
#define c2 PORTBbits.RB5
#define c3 PORTBbits.RB6
#define c4 PORTBbits.RB7

void delay_ms(void);
void varre_display(void);
signed long int varre_teclado(void);
void organizar(void);
void resultado(void);
void valores(void);
void guardarValores(void);
void operadores(void);

unsigned char dh, uh, dm, um, ds, us;
char aux, aux1=-2, aux2=-2, aux3=-2, aux4=-2, aux5=-2, aux6=-2;

signed long int tecla, operador=0;

signed long int valor1=0, valor2=0, igualdade=0;

unsigned char converte_7segmentos [14] = {

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
0b01111001, // E
0b01000000, // -
0b10000000, // .
0b01010000, // r
};

void delay_ms(void){
	
	int i;
	for(i = 0; i < 200; i++){} // 3,96ms
}

void varre_display(void){

	d1=d2=d3=d4=d5=d6=1; // Dessabilida todos os displays
	
	barramento = converte_7segmentos[dh];
	d1=0; // habilita display
	delay_ms(); //tempo
	d1=1; // dessabilida

	barramento = converte_7segmentos[uh];
	d2=0; // habilita display
	delay_ms(); //tempo
	d2=1; // dessabilida

	barramento = converte_7segmentos[dm];
	d3=0; // habilita display
	delay_ms(); //tempo
	d3=1; // dessabilida

	barramento = converte_7segmentos[um];
	d4=0; // habilita display
	delay_ms(); //tempo
	d4=1; // dessabilida
	
	barramento = converte_7segmentos[ds];
	d5=0; // habilita display
	delay_ms(); //tempo
	d5=1; // dessabilida

	barramento = converte_7segmentos[us];
	d6=0; // habilita display
	delay_ms(); //tempo
	d6=1; // dessabilida
}

signed long int varre_teclado(void){

	int i = 0;
	for(i; i < 1; i++){ // Varredura de C1
		c1=0;
		c2=1;
		c3=1;
		c4=1;
		if(!l1){
			while(!l1){};
			return 7;
		}if(!l2){
			while(!l2){};
			return 4;
		}if(!l3){
			while(!l3){};
			return 1;
		}if(!l4){
			while(!l4){};
			return 10;
		}
	}
	i=0;
	for(i; i < 1; i++){// Varredura C2
		c1=1;
		c2=0;
		c3=1;
		c4=1;
		if(!l1){
			while(!l1){};
			return 8;
		}if(!l2){
			while(!l2){};
			return 5;
		}if(!l3){
			while(!l3){};
			return 2;
		}if(!l4){
			while(!l4){};
			return 0;
		}
	}
	i=0;
	for(i; i < 1; i++){// Varredura C3
		c1=1;
		c2=1;
		c3=0;
		c4=1;
		if(!l1){
			while(!l1){};
			return 9;
		}if(!l2){
			while(!l2){};
			return 6;
		}if(!l3){
			while(!l3){};
			return 3;
		}if(!l4){
			while(!l4){};
			return 11;
		}
	}
	i=0;
	for(i; i < 1; i++){// Varredura C4
		c1=1;
		c2=1;
		c3=1;
		c4=0;
		if(!l1){
			while(!l1){};
			return 12;
		}if(!l2){
			while(!l2){};
			return 13;
		}if(!l3){
			while(!l3){};
			return 14;
		}if(!l4){
			while(!l4){};
			return 15;
		}
	}
	return 30;
}

void soma(void){

	igualdade = valor1 + valor2;
	if(igualdade > 999999){
		dh=10;uh=13;dm=13;um=0;
		varre_display();
		aux=1;
		while(aux){
			varre_display();
			tecla = varre_teclado();
			if(tecla == 10){
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
				aux = 0;
			}
		}
	}else{
		organizar();
		dh=aux1;
		uh=aux2;
		dm=aux3;
		um=aux4;
		ds=aux5;
		us=aux6;
		aux=1;
		while(aux){
			varre_display();
			tecla = varre_teclado();
			if(tecla == 10){
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
				aux = 0;
			}
		}
	}
}

void subtracao(void){

	igualdade = valor1 - valor2;
	if(valor1 < valor2){
		igualdade = igualdade * (-1);
		organizar();
		dh=11;
		uh=aux2;
		dm=aux3;
		um=aux4;
		ds=aux5;
		us=aux6;
		aux=1;
		while(aux){
			varre_display();
			tecla = varre_teclado();
			if(tecla == 10){
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
				aux = 0;
			}
		}
	}else{
		organizar();
		dh=aux1;
		uh=aux2;
		dm=aux3;
		um=aux4;
		ds=aux5;
		us=aux6;
		aux=1;
		while(aux){
			varre_display();
			tecla = varre_teclado();
			if(tecla == 10){
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
				aux = 0;
			}
		}
	}
}

void multiplicacao(void){

	igualdade = valor1 * valor2;
	if(igualdade > 999999){
		dh=10;uh=13;dm=13;um=0;
		varre_display();
		aux=1;
		while(aux){
			varre_display();
			tecla = varre_teclado();
			if(tecla == 10){
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
				aux = 0;
			}
		}
	}else{
		organizar();
		dh=aux1;
		uh=aux2;
		dm=aux3;
		um=aux4;
		ds=aux5;
		us=aux6;
		aux=1;
		while(aux){
			varre_display();
			tecla = varre_teclado();
			if(tecla == 10){
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
				aux = 0;
			}
		}
	}
}

void divisao(void){

	igualdade = valor1 / valor2;
	if(igualdade > 9999){
		dh=10;uh=13;dm=13;um=0;
		varre_display();
		aux=1;
		while(aux){
			varre_display();
			tecla = varre_teclado();
			if(tecla == 10){
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
				aux = 0;
			}
		}
	}else{
		organizar();
		dh=aux3;
		uh=aux4;
		dm=aux5;
		um=aux6;
		ds=12;
		igualdade = ((valor1*1000)/valor2);
		organizar();
		us=aux4;
		aux=1;
		while(aux){
			varre_display();
			tecla = varre_teclado();
			if(tecla == 10){
				dh=uh=dm=um=ds=us=-1;
				aux1=aux2=aux3=aux4=aux5=aux6=-2;
				aux = 0;
			}
		}
	}
}

void organizar(void){

	if(igualdade > 100000){
		aux1=igualdade/100000;
		igualdade %= 100000;
		aux2=igualdade/10000;
		igualdade %= 10000;
		aux3=igualdade/1000;
		igualdade %= 1000;
		aux4=igualdade/100;
		igualdade %= 100;
		aux5=igualdade/10;
		igualdade %= 10;
		aux6=igualdade;
	}else if(igualdade > 10000){
		aux2=igualdade/10000;
		igualdade %= 10000;
		aux3=igualdade/1000;
		igualdade %= 1000;
		aux4=igualdade/100;
		igualdade %= 100;
		aux5=igualdade/10;
		igualdade %= 10;
		aux6=igualdade;
	}else if(igualdade > 1000){
		aux3=igualdade/1000;
		igualdade %= 1000;
		aux4=igualdade/100;
		igualdade %= 100;
		aux5=igualdade/10;
		igualdade %= 10;
		aux6=igualdade;
	}else if(igualdade > 100){
		aux4=igualdade/100;
		igualdade %= 100;
		aux5=igualdade/10;
		igualdade %= 10;
		aux6=igualdade;
	}else if(igualdade > 10){
		aux5=igualdade/10;
		igualdade %= 10;
		aux6=igualdade;
	}
}

void resultado(void){
	
	if(tecla == 11){
		signed long int cache1=0,cache2=0,cache3=0,cache4=0,cache5=0;
		signed long int a,b,c,d,e;
		if(dh != -1 && dh != 0){
			a= dh;
			cache5 = (a * 100000);
		}if(uh != -1 && uh != 0){
			b=uh;
			cache4 = (b * 10000);
		}if(dm != -1 && dm != 0){
			c=dm;
			cache3 = (c * 1000);
		}if(um != -1 && um != 0){
			d=um;
			cache2 = (d * 100);
		}if(ds != -1 && ds != 0){
			e=ds;
			cache1 = (e * 10);
		}
		valor2 = (cache5+cache4+cache3+cache2+cache1+us);
		dh=uh=dm=um=ds=us=-1;
		aux1=aux2=aux3=aux4=aux5=aux6=-2;
		if(operador == 12){
			divisao();
		}else if(operador == 13){
			multiplicacao();
		}else if(operador == 14){
			subtracao();
		}else if(operador == 15){
			soma();
		}
	}
}

void valores(void){
	
	if(dh != -1 && aux6 == -2){
		dh=uh=dm=um=ds=us=-1;
	}
	if(valor1 != 0){
		resultado();
	}
	if(tecla != 10 && tecla != 11 && tecla != 12 && tecla != 13 && tecla != 14 && tecla != 15 && tecla != 30 ){
		if(us == -1 && ds != aux1){
			us = tecla;
			aux1 = us;
		}else if(us == aux1 && aux2 != us){
			ds = aux1;
			us = tecla;
			aux2 = us;
		}else if(ds == aux1 && aux3 != us){
			um = aux1;
			ds = aux2;
			us = tecla;
			aux3 = us;
		}else if(um == aux1 && aux4 != us){
			dm = aux1;
			um = aux2;
			ds = aux3;
			us = tecla;
			aux4 = us;
		}else if(dm == aux1 && aux5 != us){
			uh = aux1;
			dm = aux2;
			um = aux3;
			ds = aux4;
			us = tecla;
			aux5 = us;
		}else if(uh == aux1 && aux6 != us){
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

void guardarValores(void){

	signed long int cache1=0,cache2=0,cache3=0,cache4=0,cache5=0;
	signed long int a,b,c,d,e;
	if(dh != -1 && dh != 0){
		a= dh;
		cache5 = (a * 100000);
	}if(uh != -1 && uh != 0){
		b=uh;
		cache4 = (b * 10000);
	}if(dm != -1 && dm != 0){
		c=dm;
		cache3 = (c * 1000);
	}if(um != -1 && um != 0){
		d=um;
		cache2 = (d * 100);
	}if(ds != -1 && ds != 0){
		e=ds;
		cache1 = (e * 10);
	}
	valor1 = (cache5+cache4+cache3+cache2+cache1+us);
	dh=uh=dm=um=ds=us=-1;
	aux1=aux2=aux3=aux4=aux5=aux6=-2;
	aux=1;
	while(aux){

		varre_display();
		tecla = varre_teclado();
		valores();
	}
}

void operadores(void){

	if(us != -1 && (us!=0 || ds!=0 || um!=0)){
		if(tecla == 12){
			operador = 12;
			guardarValores();
		}else if(tecla == 13){
			operador = 13;
			guardarValores();
		}else if(tecla == 14){
			operador = 14;
			guardarValores();
		}else if(tecla == 15){
			operador = 15;
			guardarValores();
		}
	}
}

main(){

	TRISC = 0b00000000; // Barramento SAIDA
	TRISD = 0b00000000; // Habilidadores SAIDA
	TRISB = 0b00001111; // Linhas como saidas e Colunas como entrada
	ADCON1 = 0b00001111;
	while(1){
		
		varre_display();
		tecla = varre_teclado();
		operadores();
		valores();
	}
}