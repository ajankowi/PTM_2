#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "StepMotor.h"





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



//	DODAJ TIMER0
//	POZMIENIAJ BITY
//
//


volatile uint8_t i = 0;


//Inicjalizacja Timer0 do wywolywania przerwania
void TimerInit() {
	//Wybranie trybu pracy CTC z TOP OCR1A
	sbi(TCCR0,WGM01);
	//Wybranie dzielnika czestotliwosci 256
	sbi(TCCR0,CS02);
	//Zapisanie do OCR1A wartosci
	OCR0=75;
	SREG=1<<7;
	//Uruchomienie przerwania OCIE1A
	sbi(TIMSK,OCIE0);
}




void half_step_motor_left(uint32_t angle, uint8_t number){


	TimerInit();			//Inicjalizuje Timer

	sei(); 					//funkcja uruchamia globalne przerwania

	//angle = 512*angle/360;

	uint32_t ac = 1;
	if(number == 1){



		sbi(SM_1_IN1_DIR,SM_1_IN1);
		sbi(SM_1_IN2_DIR,SM_1_IN2);
		sbi(SM_1_IN3_DIR,SM_1_IN3);
		sbi(SM_1_IN4_DIR,SM_1_IN4);

		for(;ac<=angle;) {



			if(i == 0){
				cbi(SM_1_IN4_PORT,SM_1_IN4);
			}
			if(i == 1){
				sbi(SM_1_IN2_PORT,SM_1_IN2);
			}
			if(i == 2){
				cbi(SM_1_IN1_PORT,SM_1_IN1);
			}
			if(i == 3){
				sbi(SM_1_IN3_PORT,SM_1_IN3);
			}
			if(i == 4){
				cbi(SM_1_IN2_PORT,SM_1_IN2);
			}
			if(i == 5){
				sbi(SM_1_IN4_PORT,SM_1_IN4);
			}
			if(i == 6){
				cbi(SM_1_IN3_PORT,SM_1_IN3);
			}
			if(i == 7){
				sbi(SM_1_IN1_PORT,SM_1_IN1);
			}

			if(i >= 8){
				i = 0;
				ac++;
			}
		}

	}
	else if(number == 2){
		sbi(SM_2_IN1_DIR,SM_2_IN1);
		sbi(SM_2_IN2_DIR,SM_2_IN2);
		sbi(SM_2_IN3_DIR,SM_2_IN3);
		sbi(SM_2_IN4_DIR,SM_2_IN4);

		for(;ac<=angle;) {

			if(i == 0){
				cbi(SM_2_IN4_PORT,SM_2_IN4);
				}
			if(i == 1){
				sbi(SM_2_IN2_PORT,SM_2_IN2);
			}
			if(i == 2){
				cbi(SM_2_IN1_PORT,SM_2_IN1);
			}
			if(i == 3){
				sbi(SM_2_IN3_PORT,SM_2_IN3);
			}
			if(i == 4){
				cbi(SM_2_IN2_PORT,SM_2_IN2);
			}
			if(i == 5){
				sbi(SM_2_IN4_PORT,SM_2_IN4);
			}
			if(i == 6){
				cbi(SM_2_IN3_PORT,SM_2_IN3);
			}
			if(i == 7){
				sbi(SM_2_IN1_PORT,SM_2_IN1);
			}

			if(i >= 8){
				i = 0;
				ac++;
			}
		}
	}
}

void half_step_motor_right(uint32_t angle, uint8_t number){


	TimerInit();

	sei(); //funkcja uruchamia globalne przerwania

	//angle = 512*angle/360;

	uint32_t ac = 0;

	if(number == 1){

		sbi(SM_1_IN1_DIR,SM_1_IN1);
		sbi(SM_1_IN2_DIR,SM_1_IN2);
		sbi(SM_1_IN3_DIR,SM_1_IN3);
		sbi(SM_1_IN4_DIR,SM_1_IN4);

		for (; ac <= angle;){

			if(i == 0){
				cbi(SM_1_IN1_PORT,SM_1_IN1);
			}
			if(i == 1){
				sbi(SM_1_IN3_PORT,SM_1_IN3);
			}
			if(i == 2){
				cbi(SM_1_IN4_PORT,SM_1_IN4);
			}
			if(i == 3){
				sbi(SM_1_IN2_PORT,SM_1_IN2);
			}
			if(i == 4){
				cbi(SM_1_IN3_PORT,SM_1_IN3);
			}
			if(i == 5){
				sbi(SM_1_IN1_PORT,SM_1_IN1);
			}
			if(i == 6){
				cbi(SM_1_IN2_PORT,SM_1_IN2);
			}
			if(i == 7){
				sbi(SM_1_IN4_PORT,SM_1_IN4);
			}
			if(i == 8){
				i = 0;
				ac++;
			}
		}

	}
	else if(number == 2){

		sbi(SM_2_IN1_DIR,SM_2_IN1);
		sbi(SM_2_IN2_DIR,SM_2_IN2);
		sbi(SM_2_IN3_DIR,SM_2_IN3);
		sbi(SM_2_IN4_DIR,SM_2_IN4);

		for (; ac <= angle;){

			if(i == 0){
				cbi(SM_2_IN1_PORT,SM_2_IN1);
			}
			if(i == 1){
				sbi(SM_2_IN3_PORT,SM_2_IN3);
			}
			if(i == 2){
				cbi(SM_2_IN4_PORT,SM_2_IN4);
			}
			if(i == 3){
				sbi(SM_2_IN2_PORT,SM_2_IN2);
			}
			if(i == 4){
				cbi(SM_2_IN3_PORT,SM_2_IN3);
			}
			if(i == 5){
				sbi(SM_2_IN1_PORT,SM_2_IN1);
			}
			if(i == 6){
				cbi(SM_2_IN2_PORT,SM_2_IN2);
			}
			if(i == 7){
				sbi(SM_2_IN4_PORT,SM_2_IN4);
			}
			if(i == 8){
				i = 0;
				ac++;
			}
		}
	}

}

void full_step_motor_left(uint32_t angle, uint8_t number){

	TimerInit();

	sei(); //funkcja uruchamia globalne przerwania
	sbi(DDRA,PA0);
	sbi(DDRA,PA1);
	sbi(DDRA,PA2);
	sbi(DDRA,PA3);

	angle = 512*angle/360;

	uint32_t ac = 0;

	for (; ac <= angle;) {

		if(i == 0){
			sbi(PORTA,PA0);
			cbi(PORTA,PA2);
		}
		if(i == 1){
			sbi(PORTA,PA1);
			cbi(PORTA,PA3);
		}
		if(i == 2){
			sbi(PORTA,PA2);
			cbi(PORTA,PA0);
		}
		if(i == 3){
			sbi(PORTA,PA3);
			cbi(PORTA,PA1);
		}
		if(i == 4){
			i = 0;
			ac++;
		}
	}
}

void full_step_motor_right(uint32_t angle, uint8_t number){



	TimerInit();

	sei(); //funkcja uruchamia globalne przerwania
	sbi(DDRA,PA0);
	sbi(DDRA,PA1);
	sbi(DDRA,PA2);
	sbi(DDRA,PA3);

	angle = 512*angle/360;

	uint32_t ac = 0;

	for (; ac <= angle;) {

		if(i == 0){
			sbi(PORTA,PA3);
			cbi(PORTA,PA1);
		}
		if(i == 1){
			sbi(PORTA,PA2);
			cbi(PORTA,PA0);
		}
		if(i == 2){
			sbi(PORTA,PA1);
			cbi(PORTA,PA3);
		}
		if(i == 3){
			sbi(PORTA,PA0);
			cbi(PORTA,PA2);
		}

		if(i == 4){
			i = 0;
			ac++;
		}
	}
}



int silnik() {


	//Nale¿y podac kat w X *  - 360/512      2 odpowiada 1,40625*
	uint16_t j = 1;
	uint32_t kat = 2;

	//half_step_motor_left(kat,szybkosc,1);
	//half_step_motor_left(kat,szybkosc,2);

	for(;j <= 256;){
		half_step_motor_right(kat,1);
		//half_step_motor_left(kat,2);
		j++;
	}


	//half_step_motor_right(kat);
	//full_step_motor_right(kat);
	//full_step_motor_left(kat);



	return 0;

}



//Funkcja uruchamiana z przerwaniem po przepelnieniu licznika w timer0
ISR(TIMER0_COMP_VECTOR) {

	i++;

}
