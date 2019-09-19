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


void buzzer_play_note(note_t note, uint8_t duration) {
    pwm0_set_freq(note);
    // to calculate note duration in ms, take 1 sec and divide by 
    // note type (half = 2, fourth = 4, etc.)
    int note_duration = 1000 / duration;
    _delay_ms(note_duration);
    buzzer_stop();
}


void buzzer_stop() {
    pwm0_set_prescaler(PREOFF);
}


void buzzer_play_song(uint16_t* melody, uint8_t* durations) {

}
