#ifndef BUZZER_H
#define BUZZER_H

#include "pitches.h"
#include <stdint.h>

void buzzer_init();

void buzzer_play_note(note_t note, uint8_t duration);

void buzzer_stop();

void buzzer_play_song(uint16_t* melody, uint8_t* durations);

#endif // BUZZER_H