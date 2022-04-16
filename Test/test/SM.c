#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "SM.h"



volatile uint8_t i = 0;

//Inicjalizacja Timer1 do wywolywania przerwania
void TimerInit() {
	//Wybranie trybu pracy CTC z TOP OCR1A
	sbi(TCCR1B,WGM12);
	//Wybranie dzielnika czestotliwosci 256
	sbi(TCCR1B,CS12);
	//Zapisanie do OCR1A wartosci
	OCR1A=50;
	//Uruchomienie przerwania OCIE1A
	sbi(TIMSK,OCIE1A);
}



void half_step_motor_left(uint32_t angle, uint16_t speed, uint8_t number){


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

void half_step_motor_right(uint32_t angle, uint16_t speed, uint8_t number){


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

void full_step_motor_left(uint32_t angle, uint16_t speed, uint8_t number){

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

void full_step_motor_right(uint32_t angle, uint16_t speed, uint8_t number){



	TimerInit(speed);

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



int main() {

	//Ustawienie PD0 jako PULL-UP
	cbi(DDRA,7);
	sbi(PORTA,7);

	TimerInit();
	//Nale¿y podac kat w X *  - 360/512      2 odpowiada 1,40625*

	//uint16_t j = 1;
	//uint32_t kat = 2;
	//uint16_t szybkosc = 31250;

	//half_step_motor_left(kat,szybkosc,1);
	//half_step_motor_left(kat,szybkosc,2);


	while(!bit_is_clear(PINA,7)){		//Sprawdza czy przycisk zosta³ wcisniety
		half_step_motor_left(2,1,1);
	}


	half_step_motor_right(256,1,1);


//	for(int j = 0; j<10 ; j++){
//		for(int i = 0; i<64; i++){
//			half_step_motor_right(7,1,1);
//		}
//	}

	//for(;j <= 256;){
	//	half_step_motor_left(kat,szybkosc,1);
	//	j++;
	//}


	//half_step_motor_right(kat);
	//full_step_motor_right(kat);
	//full_step_motor_left(kat);



	return 0;

}


//Funkcja uruchamiana z przerwaniem po przepelnieniu licznika w timer1
ISR(TIMER1_COMPA_vect) {

	i++;

}
