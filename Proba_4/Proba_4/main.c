#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "HD44780.h"

#ifndef _BV
#define _BV(bit)				(1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)		reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)		reg &= ~(_BV(bit))
#endif




void err(){
	char text[20];
	LCD_Initalize();
	LCD_Home();
	LCD_Clear();

	LCD_GoTo(0, 0);
	sprintf(text, " Blad! ");
	LCD_WriteText(text);
	_delay_ms(1000);

}


void i2c(){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		//1

	while(!(TWCR&(1<<TWINT)));					//2

	if ((TWSR & 0xF8) != START){				//3
		err();
	}

	TWDR = SLA_W;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while (!(TWCR & (1<<TWINT)));				//4

	if ((TWSR & 0xF8) != MT_SLA_ACK)			//5
	err();

	TWDR = DATA;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while (!(TWCR & (1<<TWINT)));				//6

	if ((TWSR & 0xF8) != MT_DATA_ACK)
	err();


	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);		//7





}

int main() {

	while(1){
		err();
	}


}
