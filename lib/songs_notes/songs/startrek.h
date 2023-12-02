#ifndef __STARTREK_H__
#define __STARTREK_H__

#include "notes.h"

// change this to make the song slower or faster
int startrek_time_note = 80;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int startrek[] = {

    // Star Trek Intro
    // Score available at https://musescore.com/user/10768291/scores/4594271

    NOTE_D4,
    -8,
    NOTE_G4,
    16,
    NOTE_C5,
    -4,
    NOTE_B4,
    8,
    NOTE_G4,
    -16,
    NOTE_E4,
    -16,
    NOTE_A4,
    -16,
    NOTE_D5,
    2,

};

#endif // __STARTREK_H__