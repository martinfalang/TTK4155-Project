#ifndef MARIO_H
#define MARIO_H

#include "notes.h"
#include <stdint.h>
#include <avr/pgmspace.h>

#define MARIO_LENGTH 78

const note_t mario_melody[] PROGMEM = {
  NOTE_E5, NOTE_E5, 0, NOTE_E5,
  0, NOTE_C5, NOTE_E5, 0,
  NOTE_G5, 0, 0,  0,
  NOTE_G4, 0, 0, 0,
 
  NOTE_C5, 0, 0, NOTE_G4,
  0, 0, NOTE_E4, 0,
  0, NOTE_A4, 0, NOTE_B4,
  0, NOTE_AS4, NOTE_A4, 0,
 
  NOTE_G4, NOTE_E5, NOTE_G5,
  NOTE_A5, 0, NOTE_F5, NOTE_G5,
  0, NOTE_E5, 0, NOTE_C5,
  NOTE_D5, NOTE_B4, 0, 0,
 
  NOTE_C5, 0, 0, NOTE_G4,
  0, 0, NOTE_E4, 0,
  0, NOTE_A4, 0, NOTE_B4,
  0, NOTE_AS4, NOTE_A4, 0,
 
  NOTE_G4, NOTE_E5, NOTE_G5,
  NOTE_A5, 0, NOTE_F5, NOTE_G5,
  0, NOTE_E5, 0, NOTE_C5,
  NOTE_D5, NOTE_B4, 0, 0
};
//Mario main them tempo
const note_type_t mario_tempo[] PROGMEM = {
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
 
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
 
  4, 4, 4,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
 
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
 
  4, 4, 4,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
};

#endif // MARIO_H