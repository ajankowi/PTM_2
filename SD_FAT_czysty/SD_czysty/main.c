#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "ff.h"
#include "diskio.h"
#include "mmc_avr.h"



FATFS FatFs;

FIL Fil;
unsigned int bw;


// Constants
#define BAUD 			115200	// Serial baudrate for user interface


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

FILINFO Finfo;

volatile UINT Timer;	/* Performance timer (100Hz increment) */



static
void ioinit (void)
{
	/* Timer 2 - co 10ms, dla karty SD */
		TCCR2 |= ((1 << WGM21 | 1 << CS22 | 1 << CS21) | (1 << CS20));				//preskaler 1024, tryb CTC
		OCR2 = 78;
		TIMSK |= (1 << OCIE2);								//zezwolenie na przerwanie od Timera 0
		sei();
}





int main(){

	 ioinit();											// Inicjalizacja po??czenia z kart?
	 disk_initialize(0);								// inicjalizacja karty SD


	 //char text[20];										// Tablica pomocnicza


	 FRESULT fr;     									// Zmienna dla inicjalizacji karty SD
	 char name[20];										// Bufory
	 char buf[50];
	 int b = 0;



	_delay_ms(5000);

	fr = f_mount(&FatFs, "", 1);						// Po??czenie si? z kart? SD
	_delay_ms(50);

	if(fr != 0){										// Wy?wietlenie komunikatu o b?dzie

		//LCD_WriteText("f_mount_FAILL");


		//sprintf(text, "Blad nr - %d",fr);				// Zwraca numer b??du



	}

	else{


	}
	do{


		sprintf(name, "skaner%d.txt",b);				// Tworzenie nowego pliku o danej nazwie


		fr = f_open(&Fil, name, FA_WRITE | FA_CREATE_NEW);
		f_sync(&Fil);									// Tworzenie pliku tekstowego
		b++;

	}while(fr!=0);








	sprintf(buf, "Tekst!\n" );	// Zapisanie wspolrzednych do bufora
	f_write(&Fil, buf, sizeof(char)*strlen(buf), &bw);	// Zapisanie bufora na karte SD

	f_sync(&Fil);							// Funkcja zabezpieczajaca otwerty plik txt w razie naglego unieruchomienia







	 f_close(&Fil);										// Zamyka plik txt

	 return 0;
}




ISR(TIMER2_COMP_VECTOR)
{
	Timer++;			/* Performance counter for this module */
	disk_timerproc();	/* Drive timer procedure of low level disk I/O module */
}






							// Fukcja zwracajaca RTC do zapisu plikow
DWORD get_fattime(void)
{
 return ((DWORD)(2013 - 1980) << 25) /*Year 2013*/
				| ((DWORD)7 << 21)   /*Month 6*/
				| ((DWORD)28 << 16)  /*Mday 28*/
				| ((DWORD)0 << 11)   /*Hour 0*/
				| ((DWORD)0 << 5)    /*Min 0*/
				| ((DWORD)0 << 1);    /*Sec 0*/
}
