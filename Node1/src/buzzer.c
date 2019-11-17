#include "../../lib/inc/defines.h"
#include "buzzer.h"
#include "pwm0.h"
#include "delay.h"

#include <avr/pgmspace.h>
#include <stdio.h>


void buzzer_init() {
    // prescaler of 256 gives a frequency range of
    // 37.5 Hz to 9 600 Hz
    // pwm0_set_prescaler(PRE256);
    pwm0_init();
}


void buzzer_play_note(const note_t note, const uint8_t type, 
                      const uint16_t bar_length_ms) {
    pwm0_set_freq(note);
    // to calculate note duration in ms, take 1 sec and divide by 
    // note type (half = 2, fourth = 4, etc.)
    uint16_t note_duration = bar_length_ms / type;
    var_delay_ms(note_duration);
    // buzzer_stop();
}


void buzzer_stop() {
    // pwm0_set_prescaler(PREOFF);
    pwm0_stop();
}


void buzzer_play_song_P(const note_t* melody, 
                        const note_type_t* notes_types, 
                        const uint16_t length,
                        const uint16_t bar_length_ms) {
    // plays song stored in PROGMEM
    printf("Playing song...\n");
    for (uint16_t i = 0; i < length; ++i) {
        uint8_t type = pgm_read_byte(&notes_types[i]);
        note_t note = pgm_read_word(&melody[i]);
        buzzer_play_note(note, type, bar_length_ms);
    }
    buzzer_stop();
}
