#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ff.h"
#include "diskio.h"
#include "HD44780.h"
#include "mmc_avr.h"


FATFS FatFs;

FIL Fil;
unsigned int bw;

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


//BYTE Buff[4096];	/* Working buffer */
//
//FATFS FatFs[2];		/* Filesystem object for each logical drive */
//FIL File[2];		/* File object */
//DIR Dir;			/* Directory object */
FILINFO Finfo;
//
////BYTE RtcOk;				/* RTC is available */
volatile UINT Timer;	/* Performance timer (100Hz increment) */






/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */









//static
//void ioinit (void)
//{
//	/* Timer 0 - co 10ms, dla karty SD */
//		TCCR0 |= ((1 << WGM01 | 1 << CS02) | (1 << CS00));				//preskaler 1024, tryb CTC
//		OCR0 = 78;
//		TIMSK |= (1 << OCIE0);								//zezwolenie na przerwanie od Timera 0
//		sei();
//}




static
void ioinit (void)
{
	/* Timer 2 - co 10ms, dla karty SD */
		TCCR2 |= ((1 << WGM21 | 1 << CS22 | 1 << CS21) | (1 << CS20));				//preskaler 1024, tryb CTC
		OCR2 = 78;
		TIMSK |= (1 << OCIE2);								//zezwolenie na przerwanie od Timera 0
		sei();
}



int main (void){

	LCD_Initalize();
	LCD_Home();

	//Karta
	ioinit();
	disk_initialize(0);

	char text[20];
	char buf[20];
	char name[12];

	FRESULT fr;     /* FatFs return code */
	int a = 0;
	int b = 0;



	sprintf(text, "TEST");
	LCD_Clear();
	LCD_GoTo(0, 0);
	LCD_WriteText(text);


	_delay_ms(5000);

		fr = f_mount(&FatFs, "", 1);

		while(fr != 0){
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("f_mount_FAILL");
			sprintf(text, "Blad nr - %d",fr);
			LCD_GoTo(0,1);
			LCD_WriteText(text);
			_delay_ms(4000);
			disk_initialize(0);

			
		}


		do{
			sprintf(name, "skaner%d.txt",b);
			fr = f_open(&Fil, name, FA_WRITE | FA_CREATE_NEW);
			f_sync(&Fil);
			b++;
			if(b>9){
				LCD_Clear();
				LCD_GoTo(0,0);
				LCD_WriteText("f_open_ERR");
				LCD_GoTo(0,1);
				LCD_WriteText("New_file");

				

			}
		}while(fr!=0);


		f_sync(&Fil);



		while(fr != 0){
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("Open_f_FAILL");
			sprintf(text, "Blad nr - %d",fr);
			LCD_GoTo(0,1);
			LCD_WriteText(text);
			_delay_ms(4000);
			disk_initialize(0);

			return 0;
		}


		for(;a<11;a++){
			sprintf(buf, "Dane - %d\n",a);
			f_write(&Fil, buf, sizeof(char)*strlen(buf), &bw);
			f_sync(&Fil);
			_delay_ms(20);
		}

		f_close(&Fil);

		LCD_Clear();
		LCD_GoTo(0,0);
		LCD_WriteText("Udalo sie!");


return 0;


}








ISR(TIMER2_COMP_VECTOR)
{
	Timer++;			/* Performance counter for this module */
	disk_timerproc();	/* Drive timer procedure of low level disk I/O module */
}







DWORD get_fattime(void)
{
 return ((DWORD)(2013 - 1980) << 25) /*Year 2013*/
				| ((DWORD)7 << 21)   /*Month 6*/
				| ((DWORD)28 << 16)  /*Mday 28*/
				| ((DWORD)0 << 11)   /*Hour 0*/
				| ((DWORD)0 << 5)    /*Min 0*/
				| ((DWORD)0 << 1);    /*Sec 0*/
}
