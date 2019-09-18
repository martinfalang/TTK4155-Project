#ifndef BUZZER_H
#define BUZZER_H

#include "pitches.h"

void buzzer_init();

void buzzer_play_note(note_t note);

void buzzer_stop();

void buzzer_play_nyan_cat();

#endif // BUZZER_H