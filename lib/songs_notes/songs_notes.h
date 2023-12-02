/*****************************************
 * Reference
 * https://github.com/robsoncouto/arduino-songs
 *
 ******************************************/

#ifndef __SONGS_NOTES_H__
#define __SONGS_NOTES_H__

#include <Arduino.h>
// #include "songs/harrypotter.h"
// #include "songs/startrek.h"
// #include "songs/pacman.h"
// #include "songs/pinkpanther.h"
// #include "songs/thegodfather.h"
#include "songs/happybirthday.h"
// #include "songs/merrychristmas.h"

class SongsNotes
{
private:
    int time_note;
    static void _play_song(void *arg);

public:
    SongsNotes(int channel, int pin, int timer_bit, int base_freq);
    void setMellody(int number);
    void playSong();
    void stopSong();
};

// extern SongsNotes songsNotes = SongsNotes();

#endif // __SONGS_NOTES_H__