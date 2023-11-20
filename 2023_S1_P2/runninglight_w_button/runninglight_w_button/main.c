#define F_CPU (16000000UL)
// TODO: Fix code :D
#include <avr/io.h>
#include <util/delay.h>

int delay_in_ms = 100;
int currentLED = 0b00000001;

int main(void){
	//  PB5 output
	DDRB |= (1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	DDRD |= (1<<DDD7);
	
	while(1){
			int lastLED = currentLED;		// Saves the last LED light, so it can be turned off
			PORTB |= currentLED;		// light up the new LED
			currentLED>>=1;					// shifting the bit to the right
			if(currentLED <= 1){
				currentLED = 0b01000000;
			}
			_delay_ms(delay_in_ms)			
			PORTB &= ~lastLED;		// turns off the LED
	}
}