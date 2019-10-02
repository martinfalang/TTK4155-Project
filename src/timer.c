#include "defines.h"

#include <avr/io.h>

void timer_init(void) {
    // Initializes a timer that raises an interrupt calling a function
    // reading the joystick and setting a flag telling if the screen should be updated

    // Enable interrupts globally
    SREG |= SREG_I;

    // Set Clear-to-Clear mode for clock 2
    TCCR2 |= (1 << WGM21);
    TCCR2 &= ~(1 << WGM20);

    

}
