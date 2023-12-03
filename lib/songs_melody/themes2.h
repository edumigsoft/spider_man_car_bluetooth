// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

// -------------------------------------------------
// HomeAlone
// -------------------------------------------------

float HomeAlone_scale_duration = 1.30;

int HomeAlone_note[] = {
    NOTE_E4, NOTE_C5, NOTE_B4, NOTE_B4,
    NOTE_C5, NOTE_B4, NOTE_F4, NOTE_G4,
    NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4,
    NOTE_C5, NOTE_G4,
    NOTE_D4, NOTE_A4, NOTE_G4, NOTE_C4, NOTE_F4,
    NOTE_E4, NOTE_D4,
    NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4,
    NOTE_C5, NOTE_G4,
    NOTE_A4, NOTE_C5, NOTE_F4, NOTE_E4, NOTE_G4, NOTE_C4,
    NOTE_E4, NOTE_D4,
    REST, NOTE_E4, NOTE_C4, NOTE_F4, NOTE_D4,
    REST, NOTE_FS4, NOTE_D4, NOTE_A4, NOTE_G4,
    REST, NOTE_GS5, NOTE_E4, NOTE_B4, NOTE_A4,
    NOTE_F4, NOTE_C5, NOTE_A4, NOTE_B4,
    NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4,
    NOTE_C5, NOTE_G4,
    NOTE_D4, NOTE_A4, NOTE_G4, NOTE_C4, NOTE_F4,
    NOTE_E4, NOTE_D4,
    NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4,
    NOTE_C5, NOTE_G4,
    REST, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_G4, NOTE_E4,
    REST, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_G4, NOTE_E4,
    REST, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_G4, NOTE_E4,
    NOTE_C4, NOTE_C5, NOTE_B4,
    NOTE_D5, NOTE_E4, NOTE_G4, NOTE_E4,
    NOTE_C5, NOTE_G4,
    NOTE_C5};

int HomeAlone_duration[] = {
    4, 8, 8, 2,
    8, 8, 4, 4,
    4, 4, 4, 4,
    2, 2,
    4, 4, 4, 8, 8,
    2, 2,
    4, 4, 4, 4,
    2, 2,
    8, 8, 4, 8, 8, 4,
    2, 2,
    4, 8, 8, 4, 4,
    4, 8, 8, 4, 4,
    4, 8, 8, 4, 4,
    4, 8, 8, 2,
    4, 4, 4, 4,
    2, 2,
    4, 4, 4, 8, 8,
    2, 2,
    4, 4, 4, 4,
    2, 2,
    4, 16, 16, 8, 4, 4,
    4, 16, 16, 8, 4, 4,
    4, 16, 16, 8, 4, 4,
    4, 2, 4,
    4, 4, 4, 4,
    2, 2,
    1};

// -------------------------------------------------
// PinkPanther
// -------------------------------------------------

float PinkPanther_scale_duration = 1.30;

int PinkPanther_note[] = {
    REST, REST, REST, NOTE_DS4,
    NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
    NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,
    NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4,
    NOTE_E4, REST, REST, NOTE_DS4,

    NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
    NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5,
    NOTE_DS5,
    NOTE_D5, REST, REST, NOTE_DS4,
    NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
    NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,

    NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4,
    NOTE_E4, REST,
    REST, NOTE_E5, NOTE_D5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4,
    NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4};

int PinkPanther_duration[] = {
    2, 4, 8, 8,
    4, 8, 8, 4, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    2, 16, 16, 16, 16,
    2, 4, 8, 4,

    4, 8, 8, 4, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    1,
    2, 4, 8, 8,
    4, 8, 8, 4, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,

    2, 16, 16, 16, 16,
    4, 4,
    4, 8, 8, 8, 8, 8, 8,
    16, 8, 16, 8, 16, 8, 16, 8,
    16, 16, 16, 16, 16, 2};

// -------------------------------------------------
// HappyBirthday
// -------------------------------------------------

float HappyBirthday_scale_duration = 1.30;

int HappyBirthday_note[] = {
    NOTE_C4, NOTE_C4,
    NOTE_D4, NOTE_C4, NOTE_F4,
    NOTE_E4, NOTE_C4, NOTE_C4,
    NOTE_D4, NOTE_C4, NOTE_G4,
    NOTE_F4, NOTE_C4, NOTE_C4,

    NOTE_C5, NOTE_A4, NOTE_F4,
    NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4,
    NOTE_A4, NOTE_F4, NOTE_G4,
    NOTE_F4};

int HappyBirthday_duration[] = {
    4, 8,
    4, 4, 4,
    2, 4, 8,
    4, 4, 4,
    2, 4, 8,

    4, 4, 4,
    4, 4, 4, 8,
    4, 4, 4,
    2};

// -------------------------------------------------
// Nokia
// -------------------------------------------------

float Nokia_scale_duration = 1.30;

int Nokia_note[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4, 
  NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4, 
  NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
  NOTE_A4
};

int Nokia_duration[] = {
  8, 8, 4, 4,
  8, 8, 4, 4,
  8, 8, 4, 4,
  2
};

// -------------------------------------------------
// 
// -------------------------------------------------