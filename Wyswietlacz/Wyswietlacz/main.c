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


int main() {

		/*******************
		 ****   ZEGAR   ****
		 *******************
		 * */

	LCD_Initalize();
	LCD_Home();
	char text[20];
	char sek[5];
	char min[5];
	char godz[5];

	uint16_t s = 54;
	uint16_t m = 59;
	uint16_t h = 23;

	//sbi(PORTD, PD6); //Ustawia pull Up
	//sbi(PORTC, PC0);

	while (1) {
		s++;			//Dodawanie 1sek po przejœciu pêtli
		if(s == 60){
			m ++;		//Dodaje 1min po dojsciu do 60sek
			s = 0;		//Wyzerowuje sekundy
		}
		if(m == 60){
			h ++;		//Dodaje 1h po dojsciu do 60min
			m = 0;		//Wyzerowuje minuty
		}
		if(h == 24){
			h = 0 ;		//Wyzerowuje godziny
		}


		if(s < 10){
			sprintf(sek, ":0%d", s);
		}
		else{
			sprintf(sek, ":%d", s);
		}

		if(m < 10){
			sprintf(min, ":0%d", m);
		}
		else{
			sprintf(min, ":%d", m);
				}
		if(h < 10){
			sprintf(godz, "0%d", h);
		}
		else{
			sprintf(godz, "%d", h);
		}

		sprintf(text, "Clock");

		LCD_Clear();

		LCD_GoTo(12, 0);
		LCD_WriteText(sek);			//Wyswietla sekundy

		LCD_GoTo(9, 0);
		LCD_WriteText(min);			//Wyswietla minuty

		LCD_GoTo(7, 0);
		LCD_WriteText(godz);		//Wyswietla godziny

		LCD_GoTo(0, 0);
		LCD_WriteText(text);		//Wyswietla napis "Clock"

		LCD_GoTo(0, 1);
		sprintf(text, "Dziala");
		LCD_WriteText(text);

		_delay_ms(1000);
	}
}
