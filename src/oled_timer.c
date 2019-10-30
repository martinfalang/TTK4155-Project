#include <stdio.h>

#include "defines.h"

#include "oled_timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "oled-menu.h"

void oled_timer_init(void) {
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

    // Set initial value of counter to 0
    TCNT2 = 0; 

    // Set output compare register to 80, which should amount to 
    // interrupts about 60 times per second
    OCR2 = 80;

    // Enable interrupts globally
    SREG |= SREG_I;

    // Enable the interrupt mask bit
    TIMSK |= OCIE2;

    // Set CLT_T2_S/1024
    TCCR2 |= CS20 | CS21 | CS22;
}

ISR(TIMER2_COMP_vect) {
    // Interrupt service routine for checking joystick if new input has occured
    // s.t. the screen should be updated
    oled_menu_check_if_needs_update();
    printf("Timer2 interrupt!");
}