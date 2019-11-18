#include "highscore.h"


////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "../../lib/inc/defines.h"
#include <stdio.h>
#include <avr/eeprom.h> // For non-volatile storage


////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define HIGHSCORE_USE_EEPROM // Comment out to compile without using EEPROM

#ifdef HIGHSCORE_USE_EEPROM
#define HIGHSCORE_EEPROM_BASE (uint8_t *) 0x64
#endif /* HIGHSCORE_USE_EEPROM */


////////////////////////////////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////////////////////////////////

#ifndef HIGHSCORE_USE_EEPROM
static uint16_t _highscores[NUM_HIGHSCORES];
#endif /* HIGHSCORE_USE_EEPROM */


////////////////////////////////////////////////////////////////////////////////
// Private function declarations
////////////////////////////////////////////////////////////////////////////////

void _insert_score(uint8_t place, uint16_t score);
void _highscore_write(uint8_t place, uint16_t score);
uint16_t _highscore_read(uint8_t place);


////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void highscore_reset(void) {
    _highscore_write(1, 0);
    _highscore_write(2, 0);
    _highscore_write(3, 0);
    _highscore_write(4, 0);
    _highscore_write(5, 0);
}

uint16_t highscore_get(uint8_t place) {
    if (1 <= place && place <= NUM_HIGHSCORES) {
        return _highscore_read(place);
    }
    return 0;
};

void highscore_print_score(char * out, uint8_t place) {
    uint16_t score = highscore_get(place);
    printf("Updating score\n");

    if (score) { // != 0
        sprintf(out, "#%d: %d", place, score);
    } else {
        sprintf(out, "#%d: -", place);
    }
};

uint8_t highscore_nominate(uint16_t score) {
    // Assumes the highscore list is already sorted 
    for (uint8_t p = 1; p <= NUM_HIGHSCORES; ++p) { // p for place
        if (score > highscore_get(p)) {
            _insert_score(p, score);
            return highscore_get(p);
        }
    }
    return 0; // Score not good enough
}


////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////

void _insert_score(uint8_t place, uint16_t score) {
    // Inserts the score at the given position, discarding the last element
    // Note that place is not zero-indexed

    // EXAMPLE:
    // _highscores before:
    // [25, 20, 15, 10, 5]
    // _highscores after _insert_score(13, 4)
    // [25, 20, 15, 13, 10]

    for (uint8_t p = NUM_HIGHSCORES; p > place; --p) {
        _highscore_write(p, _highscore_read(p - 1));
    }
    _highscore_write(place, score);
}

void _highscore_write(uint8_t place, uint16_t score) {
    #ifdef HIGHSCORE_USE_EEPROM
    // Write to EEPROM. Use update function, which doesn't write if
    // the same data is already there to increase the lifetime of the EEPROM
    eeprom_update_byte(HIGHSCORE_EEPROM_BASE + place - 1, score);
    #else
    // Don't use EEPROM
    _highscores[place - 1] = score;
    #endif

}
uint16_t _highscore_read(uint8_t place) {
    #ifdef HIGHSCORE_USE_EEPROM
    // Read from EEPROM
    return eeprom_read_byte(HIGHSCORE_EEPROM_BASE + place - 1);
    #else
    // Don't use EEPROM, read from memory instead
    return _highscores[place - 1];
    #endif
}