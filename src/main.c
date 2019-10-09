/*
 * TestProject.c
 *
 * Created: 28.08.2019 12.19.50
 * Author : eirik
 */

#include "defines.h"

#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "xmem.h"
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "oled-buffer.h"
#include "oled.h"
#include "oled-menu.h"
// #include "timer.h"

void heartbeat_init()
{
    DDRB |= 1 << DDB0;
}

void heartbeat()
{
    PORTB ^= 1 << PB0;
}

void oled_test_screen_2(void)
{
    uint8_t *buffer = OLED_BUFFER_BASE;
    oled_buffer_clear_screen(buffer);
    // Try to write some strings

    oled_buffer_print_string("asdf", MEDIUM, 0, buffer);
    oled_buffer_print_string("sdfg", MEDIUM, 1, buffer);
    oled_buffer_print_string("dfhh", MEDIUM, 2, buffer);
    oled_buffer_print_string("fgjj", MEDIUM, 3, buffer);
    oled_buffer_print_string("ghjk", MEDIUM, 4, buffer);
    oled_buffer_print_string("hjkl", MEDIUM, 5, buffer);
    oled_buffer_print_string("nytt", MEDIUM, 6, buffer);
    oled_buffer_print_string("jaja", MEDIUM, 7, buffer);

    // Print buffer to screen
    oled_draw_screen(buffer);
}

void timer_init(void) {
    // Initializes a timer that raises an interrupt calling a function
    // reading the joystick and setting a flag telling if the screen should be updated


    // Set Force Output Compare high
    TCCR2 |= (1 << FOC2);

    // Set Clear-to-Clear mode for clock 2
    TCCR2 |= (1 << WGM21);
    TCCR2 &= ~(1 << WGM20);

    // Set the register to clear on match
    TCCR2 |= (1 << COM21);
    TCCR2 &= ~(1 << COM20);

    // Set CLT_T2_S/1024
    TCCR2 |= (1 << CS20) | (1 << CS21) | (1 << CS22);

    // Set the timer counter register to 0
    TCNT2 = 0; 

    // Set output compare register to 80, which should amount to 
    // interrupts about 60 times per second
    OCR2 = 80;

    // TODO:
    TIMSK |= (1 << OCIE2);
    // 

    // Enable interrupts globally
    SREG |= (1 << SREG_I);
}

ISR(TIMER2_COMP_vect) {
    // Interrupt service routine for checking joystick if new input has occured
    // s.t. the screen should be updated
    
    // oled_menu_check_if_needs_update();
    heartbeat();
    printf("Timer2 interrupt!\n");
}

int main(void)
{
    heartbeat_init();
    uart_init(); // So we can communicate with the terminal connected via JTAG
    xmem_init();
    adc_init();
    joystick_init();
    touch_init();
    oled_init();

    printf("Print test\n");

    // oled_test_screen_2();
    // oled_menu_init(OLED_BUFFER_BASE);
    timer_init();
    printf("All inits ran successfully!\n");


    
    while(1){}
    // oled_test_screen_2();

    // while (1)
    // {
    //     heartbeat();
        // _delay_ms(100);
    // }
}
