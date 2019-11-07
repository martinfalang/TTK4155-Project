
/*
    This module handles the timing of the Atmega162. It makes it possible for 
    the oled screen to be updated with 60 Hz, a CAN message with joystick and 
    touch button signals to be sent with 10 Hz, and a heartbeat led to flash 
    with 1 Hz frequency.
*/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Private variables
////////////////////////////////////////////////////////////////////////////////

static bool timeout = false;
static unsigned char heartbeat_counter = 0;
static unsigned char can_counter = 0;        

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

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
    sei();
}

ISR(TIMER2_COMP_vect) {
    timeout = true;
    can_counter++;
    heartbeat_counter++;
}

bool timer_get_oled_timeout(void) {
    return timeout;
}

bool timer_get_heartbeat_timeout(void) {
    if (heartbeat_counter >= HEARTBEAT_FREQ) {
        heartbeat_counter = 0;
        return true;
    }
    return false;
}
bool timer_get_can_timeout(void) {

    if (can_counter >= CAN_FREQ) {
        can_counter = 0;
        return true;
    }
    return false;
}