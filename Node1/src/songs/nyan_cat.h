#ifndef NYAN_CAT_H
#define NYAN_CAT_H

#include "../notes.h"
#include <stdint.h>
#include <avr/pgmspace.h>

// sheet music: https://musescore.com/namvet/scores/50457 
// these notes are not based off of that link. they were instead
// found on a github project

#define NYAN_CAT_LENGTH 428  // words (2 bytes)

//notes in the melody:
const note_t nyan_cat_melody[] PROGMEM = {
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_B3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_AS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_CS4,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
  NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_B3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_AS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
  NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
  NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
  NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_CS4,
};

// note durations: 4 = quarter note, 8 = eighth note, etc
const note_type_t nyan_cat_note_types[] PROGMEM = {
  4,4,8,8,8,8,8,8,4,4,4,
  4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,8,8,8,8,8,8,8,8,
  4,8,8,8,8,8,8,8,8,4,4,4,
  4,4,8,8,8,8,8,8,4,4,4,
  4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,8,8,8,8,8,8,8,8,
  4,8,8,8,8,8,8,8,8,4,4,4,
  4,8,8,4,8,8,8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,8,8,8,8,8,8,8,8,
  4,8,8,4,8,8,8,8,8,8,8,8,8,8,
  4,8,8,8,8,8,8,8,8,8,8,4,4,
  4,8,8,4,8,8,8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,8,8,8,8,8,8,8,8,
  4,8,8,4,8,8,8,8,8,8,8,8,8,8,
  4,8,8,8,8,8,8,8,8,8,8,4,4,
  4,4,8,8,8,8,8,8,4,4,4,
  4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,8,8,8,8,8,8,8,8,
  4,8,8,8,8,8,8,8,8,4,4,4,
  4,4,8,8,8,8,8,8,4,4,4,
  4,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,8,8,8,8,8,8,8,8,
  4,8,8,8,8,8,8,8,8,4,4,4,
  4,8,8,4,8,8,8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,8,8,8,8,8,8,8,8,
  4,8,8,4,8,8,8,8,8,8,8,8,8,8,
  4,8,8,8,8,8,8,8,8,8,8,4,4,
  4,8,8,4,8,8,8,8,8,8,8,8,8,8,
  4,4,8,8,8,8,8,8,8,8,8,8,8,8,
  4,8,8,4,8,8,8,8,8,8,8,8,8,8,
  4,8,8,8,8,8,8,8,8,8,8,4,4,
};


#endif // NYAN_CAT_H