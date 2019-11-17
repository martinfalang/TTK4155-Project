#ifndef BUZZER_H
#define BUZZER_H

#include "notes.h"
#include <stdint.h>

void buzzer_init();

// type is type of note (whole (1), half (2), quarter (4), etc.)
void buzzer_play_note(const note_t note, const note_type_t type, const uint16_t bar_length_ms);

void buzzer_stop();

void buzzer_play_song_P(const note_t* melody, 
                        const note_type_t* note_types, 
                        const uint16_t length,
                        const uint16_t bar_length_ms);

#endif // BUZZER_H