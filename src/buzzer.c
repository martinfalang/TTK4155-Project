#include "buzzer.h"
#include "pwm0.h"
#include "defines.h"
#include <avr/pgmspace.h>
#include "delay.h"

#include <stdio.h>


void buzzer_init() {
    // prescaler of 256 gives a frequency range of
    // 37.5 Hz to 9 600 Hz
    // pwm0_set_prescaler(PRE256);
}


void buzzer_play_note(const note_t note, const uint8_t type) {
    pwm0_set_freq(note);
    // to calculate note duration in ms, take 1 sec and divide by 
    // note type (half = 2, fourth = 4, etc.)
    uint16_t note_duration = BAR_LENGTH_MS / type;
    var_delay_ms(note_duration);
    // buzzer_stop();
}


void buzzer_stop() {
    pwm0_set_prescaler(PREOFF);
}


void buzzer_play_song_P(const note_t* melody, 
                        const note_type_t* notes_types, 
                        const uint16_t length) {
    // plays song stored in PROGMEM
    printf("Playing song...\n");
    for (uint16_t i = 0; i < length; ++i) {
        uint8_t type = pgm_read_byte(&notes_types[i]);
        note_t note = pgm_read_word(&melody[i]);

#if DEBUG
        printf("Inside song loop. \tfreq: %d \ttype: %d\n", note,type);
#endif
        buzzer_play_note(note, type);
        
        // +30% seemed to be a suitable pause duration
        uint16_t pause_between_notes = 1.3 * BAR_LENGTH_MS / type;
        var_delay_ms(pause_between_notes);
    }
    buzzer_stop();
}
