/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN_1   PB5     // AVR pin where green LED is connected
#define LED_GREEN_2   PB4
#define LED_GREEN_3   PB3
#define LED_GREEN_4   PB2
#define LED_GREEN_5   PB1
#define BUTTON	PD5
#define BLINK_DELAY 500
#ifndef F_CPU
# define F_CPU 16000000     // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/sfr_defs.h> 

/* Functions ---------------------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle two LEDs when a push button is pressed.
 * Returns:  none
 **********************************************************************/

int main(void)
{
    // Green LED at port B
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_GREEN_1);
	DDRB = DDRB | (1<<LED_GREEN_2);
	DDRB = DDRB | (1<<LED_GREEN_3);
	DDRB = DDRB | (1<<LED_GREEN_4);
	DDRB = DDRB | (1<<LED_GREEN_5);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_GREEN_1);
	PORTB = PORTB & ~(1<<LED_GREEN_2);
	PORTB = PORTB & ~(1<<LED_GREEN_3);
	PORTB = PORTB & ~(1<<LED_GREEN_4);
	PORTB = PORTB & ~(1<<LED_GREEN_5);

    // Configure Push button at port D and enable internal pull-up resistor
	DDRD = DDRD & ~(1<<BUTTON);
	PORTD = PORTD | (1<<BUTTON);

    // Infinite loop
    while (1)
    {
        // WRITE YOUR CODE HERE	
		if(bit_is_clear(PIND, BUTTON))
		{
			loop_until_bit_is_set(PIND, BUTTON);
			
			while(bit_is_set(PIND, BUTTON))	
			{
				PORTB = PORTB ^ (1<<LED_GREEN_1);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_1);
				PORTB = PORTB ^ (1<<LED_GREEN_2);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_2);
				PORTB = PORTB ^ (1<<LED_GREEN_3);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_3);
				PORTB = PORTB ^ (1<<LED_GREEN_4);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_4);
				PORTB = PORTB ^ (1<<LED_GREEN_5);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_5);
				PORTB = PORTB ^ (1<<LED_GREEN_4);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_4);
				PORTB = PORTB ^ (1<<LED_GREEN_3);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_3);
				PORTB = PORTB ^ (1<<LED_GREEN_2);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_2);
			}
		}
		
    }

    // Will never reach this
    return 0;
}