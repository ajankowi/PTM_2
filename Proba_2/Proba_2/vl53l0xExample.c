/*
 * vl53l0xExample.c
 *
 *  Created on: July 3, 2017
 *      Author: michael
 *
 *  Demonstrate the VL53I0X distance sensor.
 *
 */
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/pgmspace.h>
#include "i2cmaster.h"
#include "millis.h"
#include "VL53L0X.h"
#include "vl53l0xExample.h"
#include "HD44780.h"


void init(void) {
	//--------------------------------------------------
	// GPIOs
	//--------------------------------------------------

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
	//statInfo_t xTraStats;
	//init();

	//initVL53L0X(1);
	// lower the return signal rate limit (default is 0.25 MCPS)
	// setSignalRateLimit(0.1);
	// increase laser pulse periods (defaults are 14 and 10 PCLKs)
	// setVcselPulsePeriod(VcselPeriodPreRange, 18);
	// setVcselPulsePeriod(VcselPeriodFinalRange, 14);
	//setMeasurementTimingBudget( 500 * 1000UL );		// integrate over 500 ms per measurement


	LCD_Initalize();
	LCD_Home();
//	char text[20];
	char proba[10];

	// Main loop
	while(1){
		LCD_Clear();
		LCD_GoTo(0, 0);
		sprintf(proba, "Proba");
		LCD_WriteText(proba);

		//readRangeSingleMillimeters( &xTraStats );	// blocks until measurement is finished
		//xTraStats.rawDistance
		//LCD_GoTo(0, 1);
		//sprintf(text, "%d", xTraStats.rawDistance);
		//LCD_WriteText(text);



		_delay_ms(1000);





	}
	return 0;
}

