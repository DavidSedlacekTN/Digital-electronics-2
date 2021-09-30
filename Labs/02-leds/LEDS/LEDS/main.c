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
#define LED_GREEN1   PB5     // AVR pin where green LED is connected
#define LED_GREEN2   PC5
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
    DDRB = DDRB | (1<<LED_GREEN1);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_GREEN1);

    // Configure the second LED at port C
	DDRC = DDRC | (1<<LED_GREEN2);
	PORTC = PORTC & ~(1<<LED_GREEN2);

    // Configure Push button at port D and enable internal pull-up resistor
	DDRD = DDRD & ~(1<<BUTTON);
	PORTD = PORTD | (1<<BUTTON);

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);

        // WRITE YOUR CODE HERE
		// PORTB = PORTB ^ (1<<LED_GREEN1);
		// PORTC = PORTC ^ (1<<LED_GREEN2);
		
		if(bit_is_clear(PIND, BUTTON))
		{
			PORTB = PORTB ^ (1<<LED_GREEN1);
			PORTC = PORTC ^ (1<<LED_GREEN2);
		}
		
    }

    // Will never reach this
    return 0;
}