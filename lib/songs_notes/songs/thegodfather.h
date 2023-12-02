#ifndef __THEGODFATHER_H__
#define __THEGODFATHER_H__

#include "notes.h"

// change this to make the song slower or faster
int thegodfather_time_note = 80;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int thegodfather[] = {

    // The Godfather theme
    // Score available at https://musescore.com/user/35463/scores/55160

    REST, 4, REST, 8, REST, 8, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8, // 1
    NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8,
    NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
    NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,

    NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8, // 5
    NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
    NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8,
    NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,

    NOTE_A4, 2, REST, 8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8, // 9
    NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8,
    NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
    NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8,

    NOTE_E4, 2, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8, // 13

    // repeats from 2
    NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8, // 2
    NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
    NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,

    NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8, // 5
    NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
    NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8,
    NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,

    NOTE_A4, 2, REST, 8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8, // 9
    NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8,
    NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
    NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8,

    NOTE_E4, 2 // 13
};

#endif // __THEGODFATHER_H__