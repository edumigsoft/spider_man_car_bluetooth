#ifndef __HAPPYBIRTHDAY_H__
#define __HAPPYBIRTHDAY_H__

#include "notes.h"

// change this to make the song slower or faster
int time_note = 140;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

    // Happy Birthday
    // Score available at https://musescore.com/user/8221/scores/26906

    NOTE_C4,
    4,
    NOTE_C4,
    8,
    NOTE_D4,
    -4,
    NOTE_C4,
    -4,
    NOTE_F4,
    -4,
    NOTE_E4,
    -2,
    NOTE_C4,
    4,
    NOTE_C4,
    8,
    NOTE_D4,
    -4,
    NOTE_C4,
    -4,
    NOTE_G4,
    -4,
    NOTE_F4,
    -2,
    NOTE_C4,
    4,
    NOTE_C4,
    8,

    NOTE_C5,
    -4,
    NOTE_A4,
    -4,
    NOTE_F4,
    -4,
    NOTE_E4,
    -4,
    NOTE_D4,
    -4,
    NOTE_AS4,
    4,
    NOTE_AS4,
    8,
    NOTE_A4,
    -4,
    NOTE_F4,
    -4,
    NOTE_G4,
    -4,
    NOTE_F4,
    -2,

};

#endif // __HAPPYBIRTHDAY_H__