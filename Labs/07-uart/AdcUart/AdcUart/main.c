/***********************************************************************
 * 
 * Analog-to-digital conversion with displaying result on LCD and 
 * transmitting via UART.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#include <stdio.h>

#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Function definitions ----------------------------------------------*/

uint8_t get_parity(uint8_t data, uint8_t type) {
	// Imagine 8-bit integer with bits (a b c d e f g h)
	data ^= (data >> 4); // (a b c d e f g h) ^ (0 0 0 0 a b c d) -> (a b c d ae bf cg dh)
	data ^= (data >> 2); // (a b c d ae bf cg dh) ^ (0 0 a b c d ae bf) -> (a b ac bd ace bdf aceg bdfh)
	data ^= (data >> 1); // (a b ac bd ace bdf aceg bdfh) ^ (0 a b ac bd ace bdf aceg) -> (a ab abc abcde abcdef abcdefg abcdefgh)
	data &= 1;
	if (type == 0) {
		return data; // returns 1 when type is set to even parity and has odd number of ones
	}
	else if (type == 1) {
		return (~data); // returns 1 when type is set to odd parity and has even number of ones
	}
}

/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and start ADC conversion four times 
 *           per second. Send value to LCD and UART.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(1, 0); lcd_puts("value:");
    lcd_gotoxy(3, 1); lcd_puts("key:");
    lcd_gotoxy(8, 0); lcd_puts("a");    // Put ADC value in decimal
    lcd_gotoxy(13,0); lcd_puts("b");    // Put ADC value in hexadecimal
    lcd_gotoxy(8, 1); lcd_puts("c");    // Put button name here

    // Configure ADC to convert PC0[A0] analog value
    // Set ADC reference to AVcc
	ADMUX |= (1<<REFS0); ADMUX &= ~(1<<REFS1); 

    // Set input channel to ADC0
	ADMUX &= ~(1<<MUX0); ADMUX &= ~(1<<MUX1); ADMUX &= ~(1<<MUX2); ADMUX &= ~(1<<MUX3); 
	
    // Enable ADC module
	ADCSRA |= (1<<ADEN);

    // Enable conversion complete interrupt
	ADCSRA |= (1<<ADIE);

    // Set clock prescaler to 128
	ADCSRA |= (1<<ADPS0); ADCSRA |= (1<<ADPS1); ADCSRA |= (1<<ADPS2);

    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Set prescaler to 262 ms and enable overflow interrupt
	TIM1_overflow_262ms();
	TIM1_overflow_interrupt_enable();

    // Initialize UART to asynchronous, 8N1, 9600
	uart_init(UART_BAUD_SELECT(9600, F_CPU));

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
 * Purpose:  Use single conversion mode and start conversion four times
 *           per second.
 **********************************************************************/

ISR(TIMER1_OVF_vect)
{
    // Start ADC conversion
	ADCSRA |= (1<<ADSC);
}


/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Display value on LCD and send it to UART.
 **********************************************************************/

ISR(ADC_vect)
{
    uint16_t value = 0;
    char lcd_string[] = "0000";

    value = ADC;                  // Copy ADC result to 16-bit variable
    itoa(value, lcd_string, 10);  // Convert decimal value to string
	
    lcd_gotoxy(8, 0); lcd_puts("    ");
	lcd_gotoxy(8, 0); lcd_puts(lcd_string);
	uart_puts("Button pressed: ");
	uart_puts(lcd_string);
	uart_puts("\n\r");
	
	// uart_putc('\n');
	// uart_putc('\r');
	
	itoa(value, lcd_string, 16);
	
	lcd_gotoxy(13,0); lcd_puts("    ");
    lcd_gotoxy(13,0); lcd_puts(lcd_string); 
	
	lcd_gotoxy(8, 1); lcd_puts("None");
}

