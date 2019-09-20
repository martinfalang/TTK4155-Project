#include "buzzer.h"
#include "pwm0.h"
#include "defines.h"
#include <avr/pgmspace.h>
#include "delay.h"

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
    var_delay_ms(note_duration);
    buzzer_stop();
}


void buzzer_stop() {
    pwm0_set_prescaler(PREOFF);
}


void buzzer_play_song_P(uint16_t* melody, uint8_t* durations, uint16_t length) {
    // plays song stored in PROGMEM
    for (uint16_t i = 0; i < length; ++i) {
        uint16_t note_duration = 1000 / pgm_read_byte(&durations[i]);
        buzzer_play_note(pgm_read_word(&melody[i]), note_duration);
        
        // +30% seemed to be a suitable pause duration
        uint16_t pause_between_notes = note_duration * 1.3;
        var_delay_ms(pause_between_notes);
        
        buzzer_stop();
    }
}
