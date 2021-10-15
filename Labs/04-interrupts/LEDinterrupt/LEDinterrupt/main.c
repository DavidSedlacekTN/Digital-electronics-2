/***********************************************************************
 * 
 * Control LEDs using functions from GPIO and Timer libraries. Do not 
 * use delay library any more.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_C1  PC1
#define LED_C2  PC2
#define LED_C3  PC3
#define LED_C4  PC4
#define BUTTON_INPUT  PD1

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED on the Multi-function shield using 
             the internal 8- or 16-bit Timer/Counter.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Configuration of LED(s) at port B
    GPIO_config_output(&DDRC, LED_C1);
    GPIO_write_low(&PORTC, LED_C1);
	GPIO_config_input_pullup(&DDRD, BUTTON_INPUT);
    //GPIO_config_output(&DDRC, LED_C2);
    //GPIO_write_low(&PORTC, LED_C2);
    //GPIO_config_output(&DDRC, LED_C3);
    //GPIO_write_low(&PORTC, LED_C3);
    //GPIO_config_output(&DDRC, LED_C4);
    //GPIO_write_low(&PORTC, LED_C4);
	
    // Configuration of 16-bit Timer/Counter1 for LED blinking
    // Set the overflow prescaler to 262 ms and enable interrupt
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Toggle D1 LED on Multi-function shield.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
	static uint16_t i = 0;
	if(GPIO_read(&PIND, BUTTON_INPUT) == 0){
		if(i==3){
			i = 0;
			GPIO_toggle(&PORTC, LED_C1);
		}
		else{
			i++;
		}
	}
	else{
		if(i != 0){
			i = 0;
		}
		else{
			GPIO_toggle(&PORTC, LED_C1);
		}
	}
}


/*
ISR(TIMER1_OVF_vect)
{
	static uint16_t i=0;
	static uint16_t a=1;
	if(i>=3){
		a = -1;
		GPIO_write_high(&DDRB, LED_D4);
		GPIO_write_low(&DDRB, LED_D3);
		i--;
	}
	else if(i==2){
		if(a==1){
			GPIO_write_high(&DDRB, LED_D3);
			GPIO_write_low(&DDRB, LED_D2);
			i++;
		}
		else{
			GPIO_write_high(&DDRB, LED_D3);
			GPIO_write_low(&DDRB, LED_D4);
			i--;
		}
	}
	else if(i==1){
		if(a==1){
			GPIO_write_high(&DDRB, LED_D2);
			GPIO_write_low(&DDRB, LED_D1);
			i++;
		}
		else{
			GPIO_write_high(&DDRB, LED_D2);
			GPIO_write_low(&DDRB, LED_D3);
			i--;
		}
	}
	else{
		a = 1;
		GPIO_write_high(&DDRB, LED_D1);
		GPIO_write_low(&DDRB, LED_D2);
		i++;
	}


}
*/