#ifndef STAR_WARS_H
#define STAR_WARS_H

#include "../notes.h"
#include <stdint.h>
#include <avr/pgmspace.h>


#define STAR_WARS_LENGTH 16

const note_t star_wars_melody[] PROGMEM = {
    NOTE_C4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C5, NOTE_G4, NOTE_F4, 
    NOTE_E4, NOTE_D4, NOTE_C5, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4
};

const note_type_t star_wars_note_types[] PROGMEM = {
    2, 2, 6, 6, 6, 2, 2, 6, 
    6, 6, 2, 2, 6, 6, 6, 2
};

#endif // STAR_WARS_H
