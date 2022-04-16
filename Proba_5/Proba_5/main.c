#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/i2cmaster.h"
#include "util/millis.h"
#include "VL53L0X.h"
#include "HD44780.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "StepMotor.h"


//--------------------------------------------------
// Global Defines
//--------------------------------------------------
// GPIO
#define PIN_UART_TX		PD1
#define PIN_I2C_SDA 	PC1
#define PIN_I2C_SCL 	PC0

// Constants
#define BAUD 			115200	// Serial baudrate for user interface

// Pseudo functions for Clearing, Setting and Testing bits
#define sbi(reg, bit) 		( reg |=  ( 1 << bit ) )
#define cbi(reg, bit) 		( reg &= ~( 1 << bit ) )
#define ibi(reg, bit) 		( (reg&(1<<bit)) != 0 )


void init(void) {
	//debugInit();
	//--------------------------------------------------
	// GPIOs
	//--------------------------------------------------
	cbi( UCSRB, RXEN );		// Disable UART RX
	DDRD =  (1<<PIN_UART_TX);	// Set UART TX as output
	// Enable weak pullups on I2C lines
	PORTC = (1<<PIN_I2C_SCL) | (1<<PIN_I2C_SDA);
	//--------------------------------------------------
	// Init the other modules
	//--------------------------------------------------
	i2c_init();
	initMillis();
	sei();
}

int main(){
	 statInfo_t xTraStats;
	 init();

	//debug_str("\n\n---------------------------------------\n");
	//debug_str(" Hello world, this is vl53l0xExample ! \n");
	//debug_str("---------------------------------------\nGit: ");
	//debug_str( GIT_VERSION );
	//debug_putc( '\n' );

	 initVL53L0X(1);
	// lower the return signal rate limit (default is 0.25 MCPS)
	// setSignalRateLimit(0.1);
	// increase laser pulse periods (defaults are 14 and 10 PCLKs)
	// setVcselPulsePeriod(VcselPeriodPreRange, 18);
	// setVcselPulsePeriod(VcselPeriodFinalRange, 14);

	 setMeasurementTimingBudget( 500 * 1000UL );		// integrate over 500 ms per measurement

	char text[20];
	LCD_Initalize();
	LCD_Home();

	uint16_t liczba = 0;

	// Main loop
	while(1){
		liczba = readRangeSingleMillimeters( &xTraStats );	// blocks until measurement is finished

		LCD_Clear();

		LCD_GoTo(0, 0);
		sprintf(text, " Dziala! %d ", liczba);
		LCD_WriteText(text);
		_delay_ms(100);


	}
	return 0;
}
