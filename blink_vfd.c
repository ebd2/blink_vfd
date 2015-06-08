/*
	5-10-07
	Copyright Spark Fun Electronics© 2007
	Nathan Seidle
	nathan at sparkfun.com
	
	ATmega168
	
	Example Blink
	Toggles all IO pins at 1Hz
*/

/*
 * Copyright 2015-06-05 Eric Diven.
 */

#include <avr/io.h>

//Define functions
//======================
void ioinit(void);		//Initializes IO
void delay_ms(uint16_t x); //General purpose delay
void set_vfd(uint8_t state);
//======================

int main (void)
{
	ioinit(); //Setup IO pins and defaults

	while(1)
	{
		set_vfd(0);
		PORTC = 0xFF;
		PORTD = 0xFF;
		delay_ms(500);

		set_vfd(1);
		PORTC = 0x00;
		PORTD = 0x00;
		delay_ms(500);
	}
	return(0);
}


void set_vfd(uint8_t state) {
	uint8_t seg;
	/*
	 * ATmega328 <-> HV5812 pin mapping:
	 * PORTB0 <-> DATA_IN
	 * PORTB1 <-> CLOCK
	 * PORTB2 <-> STROBE
	 *
	 * Set data, then clock to allow for 75ns setup time on DATA_IN.
	 */
	for (seg = 1; seg <= 20; ++seg) {
		if (state) {
			PORTB = 0x01;
			PORTB = 0x03;
		} else {
			PORTB = 0x00;
			PORTB = 0x02;
		}
	}

	PORTB = 0x04;
	PORTB = 0x00;
}

void ioinit (void)
{
	//1 = output, 0 = input
	DDRB = 0b11111111; //All outputs
	DDRC = 0b11111111; //All outputs
	DDRD = 0b11111110; //PORTD (RX on PD0)
}

//General short delays
void delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
	for ( y = 0 ; y < 90 ; y++){
	  for ( z = 0 ; z < 6 ; z++){
		asm volatile ("nop");
	  }
	}
  }
}
