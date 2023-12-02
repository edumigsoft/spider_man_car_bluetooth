#include "songs_notes.h"

// // #include "songs/harrypotter.h"
// // #include "songs/startrek.h"
// // #include "songs/pacman.h"
// // #include "songs/pinkpanther.h"
// // #include "songs/thegodfather.h"
// #include "songs/happybirthday.h"
// // #include "songs/merrychristmas.h"

// SongsNotes songsNotes = SongsNotes();

// int _melody[600] = {0};
// int len_melody = 0;
int _wholenote = 0;
int _notes = 0;
int _channel = 0;
int _pin = 0;
bool _play_notes = false;

void SongsNotes::_play_song(void *arg)
{
    int _divider = 0;
    int _noteDuration = 0;

    // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < _notes * 2; thisNote = thisNote + 2)
    {
        if (!_play_notes)
        {
            ledcWriteTone(_channel, 0);
            vTaskDelete(NULL);
        }

        // calculates the duration of each note
        // _divider = _melody[thisNote + 1];
        _divider = melody[thisNote + 1];
        if (_divider > 0)
        {
            // regular note, just proceed
            _noteDuration = (_wholenote) / _divider;
        }
        else if (_divider < 0)
        {
            // dotted notes are represented with negative durations!!
            _noteDuration = (_wholenote) / abs(_divider);
            _noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        // ledcWriteTone(_channel, _melody[thisNote]);
        ledcWriteTone(_channel, melody[thisNote]);
        vTaskDelay((_noteDuration * 0.9) / portTICK_PERIOD_MS);

        // Wait for the specief duration before playing the next note.
        vTaskDelay(_noteDuration / portTICK_PERIOD_MS);

        // stop the waveform generation before the next note.
        ledcWriteTone(_channel, 0);
    }

    ledcWriteTone(_channel, 0);
    vTaskDelete(NULL);
}

SongsNotes::SongsNotes(int channel, int pin, int timer_bit, int base_freq)
{
    _channel = channel;
    _pin = pin;
    // pinMode(_pin, OUTPUT);
    ledcSetup(_channel, base_freq, timer_bit);
    ledcAttachPin(_pin, _channel);
}

void SongsNotes::setMellody(int number)
{
    switch (number)
    {
    case 1:
        // time_note = harrypotter_time_note;
        // len_melody = sizeof(harrypotter) / sizeof(int);
        // for (size_t i = 0; i < len_melody; i++)
        // {
        //     _melody[i] = harrypotter[i];
        // }
        break;
    case 2:
        // time_note = startrek_time_note;
        // len_melody = sizeof(startrek) / sizeof(int);
        // for (size_t i = 0; i < len_melody; i++)
        // {
        //     _melody[i] = startrek[i];
        // }
        break;
    case 3:
        // time_note = pacman_time_note;
        // len_melody = sizeof(pacman) / sizeof(int);
        // for (size_t i = 0; i < len_melody; i++)
        // {
        //     _melody[i] = pacman[i];
        // }
        break;
    case 4:
        // time_note = pinkpanther_time_note;
        // len_melody = sizeof(pinkpanther) / sizeof(int);
        // for (size_t i = 0; i < len_melody; i++)
        // {
        //     _melody[i] = pinkpanther[i];
        // }
        break;
    case 5:
        // time_note = thegodfather_time_note;
        // len_melody = sizeof(thegodfather) / sizeof(int);
        // for (size_t i = 0; i < len_melody; i++)
        // {
        //     _melody[i] = thegodfather[i];
        // }
        break;
    case 6:
        // time_note = happybirthday_time_note;
        // len_melody = sizeof(happybirthday) / sizeof(int);
        // for (size_t i = 0; i < len_melody; i++)
        // {
        //     _melody[i] = happybirthday[i];
        // }
        break;
    default:
        break;
    }

    // _notes = len_melody / 2;
    // _wholenote = (60000 * 4) / time_note;
    _notes = sizeof(melody) / sizeof(melody[0] / 2);
    _wholenote = (60000 * 4) / time_note;
}

void SongsNotes::playSong()
{
    _play_notes = true;
    xTaskCreate(_play_song, "Play Song", 1024 * 4, NULL, 5, NULL);
}

void SongsNotes::stopSong()
{
    _play_notes = false;
}
