#include "buzzer.h"
#include "pwm0.h"
#include "defines.h"
#include <util/delay.h>

#include "nyan_cat.h"


void buzzer_init() {
    // prescaler of 256 gives a frequency range of
    // 37.5 Hz to 9 600 Hz
    pwm0_set_prescaler(PRE256);
}


void buzzer_play_note(note_t note) {
    pwm0_set_freq(note);
}


void buzzer_stop() {
    pwm0_set_prescaler(PREOFF);
}


void buzzer_play_nyan_cat() {

}
