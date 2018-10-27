/*
* PWM-T1.cpp
*
* Created: 26/10/2018 6:20:45 PM
* Author : clint
*/

# define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint-gcc.h>


#define PIN PB1
#define DELAY 2
#define _BV(bit) (1 << (bit))

void initTimer1 (void);

int main(void)
{
 
	DDRB = _BV(PB0);
	DDRB |= _BV(PIN);
	

	initTimer1();

	int8_t direction = 1;
	uint8_t count = 0x7F;

	while (1)
	{
		_delay_ms(DELAY);

		PORTB ^= _BV(PB0);
		
		count += direction;
		
		if (count == 0xEF) {  // higher - darker
			
			direction = -1;

		} else if (count == 0x1f) { // Lower - brighter
			
			direction = 1;

		}
	
		OCR1A = count;

	}
}

void initTimer1 (void) {
	
	
	
	TCCR1 |= (_BV(CS10) | _BV(CS10) | _BV(CS10) | _BV(CS10));
	//TCCR1 |= _BV(CTC1);

	 //PWM mode

	TCCR1 |= _BV(PWM1A);

	// Note! PB1 is OC1x. As PB1 is set as an output there's no need to set PORTB.

	// OC1x (PB1) Set on compare match. Cleared when TCNT1= $00.

	TCCR1 |= _BV(COM1A0);

	// NOT (PB0) OC1x not connected because it's used to show main loop speed.

	TCCR1 |= _BV(COM1A1);


	OCR1A = 0x1F;
	//OCR1B = 0x77;
	OCR1C = 0xFF;


	TIMSK = 0;
	TIMSK = _BV(TOIE1);
	TIMSK |= _BV(OCIE1A);

	//sei();
	
}

ISR(TIMER1_COMPA_vect) {

	// Not required as PB1 is OC1x. As PB1 is set as an output there's no need to set PORTB.

	//PORTB ^= _BV(PIN);


}
