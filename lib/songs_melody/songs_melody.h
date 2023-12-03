#ifndef __SONGS_MELODY_H__
#define __SONGS_MELODY_H__

#include <Arduino.h>
// #include "pitches.h"
// #include "themes.h"

// Buzzer / Mellody
#define LEDC_CHANNEL_BUZZER 5
// #define LEDC_TIMER_BUZZER_BIT 8
// #define LEDC_TIMER_BUZZER_BIT 10
#define LEDC_TIMER_BUZZER_BIT 13
// #define LEDC_BASE_FREQ_BUZZER 1000
// #define LEDC_BASE_FREQ_BUZZER 2000
#define LEDC_BASE_FREQ_BUZZER 5000

class SongsMelody
{
private:
    static void taskPlayNotes(void *);
public:
    SongsMelody();
    void setMelody(int melody);
    void playMelody();
    void stopMelody();
};

#endif // __SONGS_MELODY_H__