#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "StepMotor.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


int main(){

	uint32_t kat = 512;

	for(int i=0; i<kat;i++){
		half_step_motor_right(1,1);
		half_step_motor_right(1,2);

	}

	return 0;
}
