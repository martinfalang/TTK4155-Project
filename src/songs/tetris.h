#ifndef TETRIS_THEME_H
#define TETRIS_THEME_H

#include "../notes.h"
#include <stdint.h>
#include <avr/pgmspace.h>


#define TETRIS_THEME_LENGTH 40

const note_t tetris_theme_melody[] PROGMEM = {
    NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, 0,
    NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, 0,
};

const note_type_t tetris_theme_note_types[] PROGMEM = {
    4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 4, 4, 4, 4, 4,
    2, 8, 4, 8, 8, 2, 8, 4, 8, 8, 4, 8, 8, 4, 4, 4, 4, 4, 4
};

#endif // TETRIS_THEME_H