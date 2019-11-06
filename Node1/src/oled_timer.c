#include "../../lib/inc/defines.h"

#include <avr/interrupt.h>

#include "oled-menu.h"
#include "oled_timer.h"

void timer_init(void) {
    // Initializes a timer that raises an interrupt 
    // setting a flag telling if the screen should be updated

    // Set Force Output Compare high
    TCCR2 |= (1 << FOC2);

    // Set Clear-to-Clear mode for clock 2
    TCCR2 |= (1 << WGM21);
    TCCR2 &= ~(1 << WGM20);

    // Set the register to clear on match
    TCCR2 |= (1 << COM21);
    TCCR2 &= ~(1 << COM20);

    // Set clock prescaler to CLT_T2_S/1024
    TCCR2 |= (1 << CS20) | (1 << CS21) | (1 << CS22);

    // Set the timer counter register to 0
    TCNT2 = 0; 

    // Set output compare register to 80, which should amount to 
    // interrupts about 60 times per second
    OCR2 = 80;

    // Activate Timer2 Output Compare in interrupt mask
    TIMSK |= (1 << OCIE2);

    // Enable interrupts globally
    SREG |= (1 << SREG_I);
}

ISR(TIMER2_COMP_vect) {
    // Interrupt service routine for checking joystick if new input has occured
    // s.t. the screen should be updated
    oled_menu_check_if_needs_update();
}