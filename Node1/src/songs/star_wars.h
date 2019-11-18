/**
 * @file star_wars.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Star Wars theme song implemented in the format used by @ref buzzer.h 
 *        to play it on the buzzer. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef STAR_WARS_H
#define STAR_WARS_H

#include "../notes.h"
#include <stdint.h>
#include <avr/pgmspace.h>


#define STAR_WARS_LENGTH 16
#define STAR_WARS_BAR_LENGTH_MS 800

const note_t star_wars_melody[] PROGMEM = {
    NOTE_C4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C5, NOTE_G4, NOTE_F4, 
    NOTE_E4, NOTE_D4, NOTE_C5, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4
};

const note_type_t star_wars_note_types[] PROGMEM = {
    1, 1, 5, 5, 5, 1, 2, 5, 
    5, 5, 1, 2, 5, 5, 5, 1
};

#endif // STAR_WARS_H
