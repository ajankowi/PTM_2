#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#ifndef _BV
#define _BV(bit)				(1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)		reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)		reg &= ~(_BV(bit))
#endif

/*-  Defination of Vectors----------------------------------------*/

#define TIMER0_COMP_VECTOR		__vector_10
#define TIMER1_COMPA_VECTOR  	__vector_7
#define TIMER1_COMPB_VECTOR 	__vector_8
#define TIMER2_COMP_VECTOR      __vector_4
#define TIMER2_OVF			    __vector_5

/*-  Definition of ISR -------------------------------------------*/

#define Timer_ISR(N)            \
void N (void)__attribute((signal,used)); \
void N (void)

#define 	bit_is_set(sfr, bit)   (_SFR_BYTE(sfr) & _BV(bit))
#define 	bit_is_clear(sfr, bit)   (!(_SFR_BYTE(sfr) & _BV(bit)))

#define BUAD 9600
#define BRC ((F_CPU/16/BUAD)-1)

#define BUFF 128

char tab[BUFF];

uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;

void appendSerial(char c);
void serialWrite(char c[]);

int main() {



	UBRRH = (BRC >> 8);
	UBRRL = BRC;

	UCSRB = (1<<RXEN) | (1<<TXEN) | (1<<TXCIE);
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);



	serialWrite("Halo\n\r");

	serialWrite("xD\n\r");


	_delay_ms(2000);

	serialWrite("Elo\n\r");

	while(1){

	}

}

void appendSerial(char c){

	tab[serialWritePos] = c;
	serialWritePos++;

	if(serialWritePos >= BUFF){

		serialWritePos = 0;
	}

}

void serialWrite(char c[]){

	for(uint8_t i = 0; i < strlen(c); i++ ){

		appendSerial(c[i]);
	}

	if(UCSRA & (1<<UDRE)){

		UDR = 0;

	}

}


ISR(USART_TXC_vect){

	if(serialReadPos != serialWritePos){
		UDR = tab[serialReadPos];
		serialReadPos++;

		if(serialReadPos >= BUFF){

			serialReadPos++;
		}
	}

}

































	// Dziala!

//	UBRRH = (BRC >> 8);
//	UBRRL = BRC;
//
//	UCSRB = (1<<RXEN) | (1<<TXEN);
//	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
//
//	while(1){
//
//		UDR = 'D';
//
//		_delay_ms(10);
//
//	}



//	cbi(DDRD, PD7);
//	sbi(DDRD, PD6);
//
//	sbi(PORTD, PD7);
//
//	while (1) {
//
//		if(bit_is_clear(PIND,7)){
//			cbi(PORTD,PD6);
//		}
//		else{
//			sbi(PORTD,PD6);
//		}
//
//
//		_delay_ms(2);
//
//	}



