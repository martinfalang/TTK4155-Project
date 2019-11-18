
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "solenoid.h"
#include "../../lib/inc/defines.h"
#include <util/delay.h>

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void solenoid_init(void) {
    DDRE |= (1 << SOLENOID_PIN);  // set pin as output
    PORTE |= (1 << SOLENOID_PIN);  // set high as the solenoid is active low
}


void solenoid_give_pulse(void) {
    // TODO: change this to timer with interrupt, not delay
    PORTE &= ~(1 << SOLENOID_PIN);  // set low
    _delay_ms(20);  // give the pulse for a small duration
    PORTE |= (1 << SOLENOID_PIN);  // set high
}

