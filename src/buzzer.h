#ifndef BUZZER_H
#define BUZZER_H

#include "pitches.h"
#include <stdint.h>

void buzzer_init();

// type is type of note (whole (1), half (2), quarter (4), etc.)
void buzzer_play_note(const note_t note, const uint8_t type);

void buzzer_stop();

void buzzer_play_song_P(const uint16_t* melody, 
                        const uint8_t* durations, 
                        const uint16_t length);

#endif // BUZZER_H