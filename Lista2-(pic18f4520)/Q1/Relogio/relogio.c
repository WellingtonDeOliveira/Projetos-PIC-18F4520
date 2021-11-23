#include <p18f4520.h>

#define chaveMin PORTAbits.RA1
#define chaveHr PORTAbits.RA0
#define botao PORTAbits.RA2
#define buzzer PORTAbits.RA3

unsigned char contador_unidade_segundos = 0;
unsigned char contador_dezena_segundos = 0;
unsigned char contador_unidade_minutos = 0;
unsigned char contador_dezena_minutos = 0;
unsigned char contador_unidade_horas = 0;
unsigned char contador_dezena_horas = 0;

unsigned char auxiliar_unidade_segundos = 0;
unsigned char auxiliar_dezena_segundos = 0;
unsigned char auxiliar_unidade_minutos = 0;
unsigned char auxiliar_dezena_minutos = 0;
unsigned char auxiliar_unidade_horas = 0;
unsigned char auxiliar_dezena_horas = 0;

unsigned char alarme_unidade_minutos = 0;
unsigned char alarme_dezena_minutos = 0;
unsigned char alarme_unidade_horas = 2;
unsigned char alarme_dezena_horas = 1;

unsigned char converte_BCD [10] = {
	0b00000000,
	0b00000001,
	0b00000010,
	0b00000011,
	0b00000100,
	0b00000101,
	0b00000110,
	0b00000111,
	0b00001000,
	0b00001001
};

void delay_ms(unsigned int mili){
	
	int i;
	for(i=0;i<mili;i++){
		int j;
		for(j=0;j<4600;j++){}
	}
}

void delay_s(unsigned int segundos){
	
	int p;
	for(p=0;p<segundos;p++){
		unsigned short long i;
		for(i=0;i<40000;i++){}
	}
}

void contador_decimal(void){
	
	contador_unidade_segundos++;
	if(contador_unidade_segundos >=10){
		contador_unidade_segundos = 0;
		contador_dezena_segundos++;
		if(contador_dezena_segundos >= 6){
			contador_dezena_segundos = 0;
			contador_unidade_minutos++;
			if(contador_unidade_minutos >= 10){
				contador_unidade_minutos = 0;
				contador_dezena_minutos++;
				if(contador_dezena_minutos >= 6){
					contador_dezena_minutos = 0;
					contador_unidade_horas++;
					if(contador_dezena_horas == 2 && contador_unidade_horas >= 4){
						contador_unidade_horas = 0;
						contador_dezena_horas = 0;
					}else if(contador_unidade_horas >= 10){
						contador_unidade_horas = 0;
						contador_dezena_horas++;
					}
				}
			}
		}
	}
}

void contar_minuto(void){
	
	contador_unidade_minutos++;
	if(contador_unidade_minutos >= 10){
		contador_unidade_minutos = 0;
		contador_dezena_minutos++;
		if(contador_dezena_minutos >= 6){
			contador_dezena_minutos = 0;
			contador_unidade_horas++;
			if(contador_dezena_horas == 2 && contador_unidade_horas >= 4){
				contador_unidade_horas = 0;
				contador_dezena_horas = 0;
			}else if(contador_unidade_horas >= 10){
				contador_unidade_horas = 0;
				contador_dezena_horas++;
			}
		}
	}
}

void contar_hora(void){

	contador_unidade_horas++;
	if(contador_dezena_horas == 2 && contador_unidade_horas >= 4){
		contador_unidade_horas = 0;
		contador_dezena_horas = 0;
	}else if(contador_unidade_horas >= 10){
		contador_unidade_horas = 0;
		contador_dezena_horas++;
	}
}

void mostrar(void){
	
	PORTC = converte_BCD[contador_unidade_segundos] | converte_BCD[contador_dezena_segundos] << 4;
	PORTD = converte_BCD[contador_unidade_minutos] | converte_BCD[contador_dezena_minutos] << 4;
	PORTB = converte_BCD[contador_unidade_horas] | converte_BCD[contador_dezena_horas] << 4;
}

void modo_ajuste(void){

	if(botao){
		delay_s(1);
		if(botao){
			delay_s(1);
			if(botao){
				unsigned char aux = 1;
				// Usando auxiliares para guardar o valor dos contadores
			 	auxiliar_unidade_segundos = contador_unidade_segundos;
				auxiliar_dezena_segundos = contador_dezena_segundos;
				auxiliar_unidade_minutos = contador_unidade_minutos;
				auxiliar_dezena_minutos = contador_dezena_minutos;
				auxiliar_unidade_horas = contador_unidade_horas;
				auxiliar_dezena_horas = contador_dezena_horas;
				// Zerando os contadores
				contador_unidade_segundos = 0;
				contador_dezena_segundos = 0;
				contador_unidade_minutos = 0;
				contador_dezena_minutos = 0;
				contador_unidade_horas = 0;
				contador_dezena_horas = 0;
				mostrar();

				while(aux){
					if(chaveMin){
						// Ajuste dos Minutos para o alarme
						contar_minuto();
						delay_s(1);
						mostrar();
					}else if(chaveHr){
						// Ajuste das horas para o alarme
						contar_hora();
						delay_s(1);
						mostrar();
					}else{
						if(botao){
							delay_s(1);
							if(botao){
								delay_s(1);
								if(botao){
									// Guardando os valores do contador para o alarme
									alarme_unidade_minutos = contador_unidade_minutos;
                                    alarme_dezena_minutos = contador_dezena_minutos;
                                    alarme_unidade_horas = contador_unidade_horas;
                                    alarme_dezena_horas = contador_dezena_horas;
									// Retornado o Horario normal do painel
									contador_unidade_segundos = auxiliar_unidade_segundos;
									contador_dezena_segundos = auxiliar_dezena_segundos;
									contador_unidade_minutos = auxiliar_unidade_minutos;
									contador_dezena_minutos = auxiliar_dezena_minutos;
									contador_unidade_horas = auxiliar_unidade_horas;
									contador_dezena_horas = auxiliar_dezena_horas;
									aux = 0;
								}
							}
						}
						mostrar();
						delay_s(1);
					}
				}
			}
		}
	}
}

void alarme(void){
	
	// Se horario = a horario do alarme assiona o buzzer
	if((contador_unidade_minutos == alarme_unidade_minutos) 
		&& (contador_dezena_minutos == alarme_dezena_minutos)
		&& (contador_unidade_horas == alarme_unidade_horas) 
		&& (contador_dezena_horas == alarme_dezena_horas)){
		
			buzzer = 1;
			delay_s(1);
			buzzer = 0;
	}
}

main(){

	TRISAbits.RA1 = 1;
	TRISAbits.RA0 = 1;
	TRISAbits.RA2 = 1;
	TRISAbits.RA3 = 0;
	ADCON1 = 0b00001111;
	TRISC = 0b00000000;  // Display 7 segmentos como saída nas portas C (segundos)
	TRISD = 0b00000000;  // Display 7 segmentos como saída nas portas D (minutos)
	TRISB = 0b00000000;  // Display 7 segmentos como saída nas portas B (horas)
	while(1){
		if(chaveMin){
			contar_minuto();
			delay_s(1);
			mostrar();
		}else if(chaveHr){
			contar_hora();
			delay_s(1);
			mostrar();
		}else{
			modo_ajuste();
			alarme();
			contador_decimal();
			delay_s(1);
			mostrar();
		}
	}
}