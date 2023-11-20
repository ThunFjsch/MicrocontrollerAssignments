#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

#define F_CPU (16000000UL)
#define debounceTime 300

// LED runner
int currentLED = 0b00000001;
int lastLED;
bool canSetLight = true;

// time in ms
volatile uint32_t ms = 0;

// initial time values
uint32_t previousmillis = 0;
uint32_t currentmillis = 0;
uint32_t interval = 100;

void millis_init(void){
	ms = 0;
	
	// Configure Timer/counter 0 to generate an interrupt every millisecond
	// T_events = T_CPU * N * (TOP + 1)
	//					= 1/16 MHz * 64 * (249 +1)
	//					= 1
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS01) | (1<<CS00);
	OCR0A = 249;
	// Timer/Counter0 Output compare match a interrupt enable
	TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect){
	ms++;
}

inline uint32_t millis(void){
	/* ms is a 32-bit variable (uint32_t). This means that multiple accesses
	are needed to read or write the value of ms. There is a chance that
	in the middle of these multiple accesses, the ms value is written due to
	the ISR being triggered. In order to make sure the value of ms is not
	updated when reading it, disable interrupts while reading the value.*/
	cli();
	uint32_t ret = ms;
	sei();
	
	return ret;
}

void ledRunnerDown(){
	if(canSetLight){
		lastLED = currentLED;
		PORTB |= currentLED;
		currentLED<<=1;
		if(currentLED >= 64){
			currentLED = 0b00000001;
		}
		canSetLight = false;
	}
	if ((currentmillis - previousmillis) >= interval){
		previousmillis = currentmillis;
		canSetLight = true;
		PORTB &= ~lastLED;
	}
}

void ledRunnerUp(){
	if(canSetLight){
		lastLED = currentLED;		// Saves the last LED light, so it can be turned off
		PORTB |= currentLED;		// light up the new LED
		currentLED>>=1;					// shifting the bit to the right
		if(currentLED <= 1){
			currentLED = 0b01000000;
		}
		canSetLight = false;
	}
	if ((currentmillis - previousmillis) >= interval){	// depending on interval the LED is on
		previousmillis = currentmillis;
		canSetLight = true;		// control variable set to restart the process of shifting etc.
		PORTB &= ~lastLED;		// turns off the LED
	}
}

int main(void){
	// Time setup
	millis_init();
	sei();	// Allow the interrupt
	
	// control variables
	uint32_t previousDebounce = 0;
	uint32_t currentDebounce = 0;
	bool isDirectionDown = true;
	
	//  PB5 output
	DDRB |= (1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	DDRD |= (1<<DDD7);

	// PD7 logic 0: pin value is equal to GND
	DDRB &= ~(1<<DDD7);
	PORTD |= (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3);

	while (1){
		currentmillis = millis();
		currentDebounce = millis();

		// Button selection
		int registerBtnLayout = 0b01111000;
		unsigned char switches = PIND & registerBtnLayout;
		if(!(switches & (1<<PIND3)) && (currentDebounce - previousDebounce) >= debounceTime){
			previousDebounce = currentDebounce;
			isDirectionDown = false;
		}
		else if(!(switches & (1<<PIND4)) && (currentDebounce - previousDebounce) >= debounceTime){
			previousDebounce = currentDebounce;
			isDirectionDown = true;
		}
		else if(!(switches & (1<<PIND5)) & (currentDebounce - previousDebounce) >= debounceTime){
			previousDebounce = currentDebounce;
			interval -= 100;
			if(interval < 100){
				interval = 100;
			}
		}
		else if(!(switches & (1<<PIND6)) & (currentDebounce - previousDebounce) >= debounceTime){
			previousDebounce = currentDebounce;
			interval += 100;
			if(interval > 1000){
				interval = 1000;
			}
		}
		
		if(isDirectionDown){
			ledRunnerDown();
		}
		else {
			ledRunnerUp();
		}
	}
}