#ifndef __MERRYCHRISTMAS_H__
#define __MERRYCHRISTMAS_H__

#include "notes.h"

// change this to make the song slower or faster
int time_note = 140;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

    // We Wish You a Merry Christmas
    // Score available at https://musescore.com/user/6208766/scores/1497501

    NOTE_C5, 4, // 1
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,

    NOTE_F5, 2, NOTE_C5, 4, // 8
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,

    NOTE_F5, 4, NOTE_F5, 4, NOTE_F5, 4, // 17
    NOTE_E5, 2, NOTE_E5, 4,
    NOTE_F5, 4, NOTE_E5, 4, NOTE_D5, 4,
    NOTE_C5, 2, NOTE_A5, 4,
    NOTE_AS5, 4, NOTE_A5, 4, NOTE_G5, 4,
    NOTE_C6, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,

    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8, // 27
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,
    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8,
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,
    NOTE_F5, 4, NOTE_F5, 4, NOTE_F5, 4,
    NOTE_E5, 2, NOTE_E5, 4,
    NOTE_F5, 4, NOTE_E5, 4, NOTE_D5, 4,

    NOTE_C5, 2, NOTE_A5, 4, // 36
    NOTE_AS5, 4, NOTE_A5, 4, NOTE_G5, 4,
    NOTE_C6, 4, NOTE_C5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,

    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, // 45
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, NOTE_C5, 4,
    NOTE_F5, 4, NOTE_F5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_E5, 8,
    NOTE_D5, 4, NOTE_D5, 4, NOTE_D5, 4,
    NOTE_G5, 4, NOTE_G5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
    NOTE_E5, 4, NOTE_C5, 4, NOTE_C5, 4,

    NOTE_A5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, // 53
    NOTE_F5, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_C5, 8,
    NOTE_D5, 4, NOTE_G5, 4, NOTE_E5, 4,
    NOTE_F5, 2, REST, 4};

#endif // __MERRYCHRISTMAS_H__