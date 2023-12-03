#include "songs_melody.h"
// #include "pitches.h"
#include "themes.h"
#include "themes2.h"

int theme = 0;
volatile bool play_notes = false;

void SongsMelody::taskPlayNotes(void *)
{
    int len = 0;
    float scale_duration = 0;
    switch (theme)
    {
    case 0:
        len = sizeof(Pirates_note) / sizeof(int);
        scale_duration = Pirates_scale_duration;
        break;
    case 1:
        len = sizeof(CrazyFrog_note) / sizeof(int);
        scale_duration = CrazyFrog_scale_duration;
        break;
    case 2:
        len = sizeof(MarioUW_note) / sizeof(int);
        scale_duration = MarioUW_scale_duration;
        break;
    case 3:
        len = sizeof(Titanic_note) / sizeof(int);
        scale_duration = Titanic_scale_duration;
        break;
    case 4:
        len = sizeof(HomeAlone_note) / sizeof(int);
        scale_duration = HomeAlone_scale_duration;
        break;
    case 5:
        len = sizeof(PinkPanther_note) / sizeof(int);
        scale_duration = PinkPanther_scale_duration;
        break;
    case 6:
        len = sizeof(HappyBirthday_note) / sizeof(int);
        scale_duration = HappyBirthday_scale_duration;
        break;
    case 7:
        len = sizeof(Nokia_note) / sizeof(int);
        scale_duration = Nokia_scale_duration;
        break;

    default:
        break;
    }

    int melody[len] = {};
    int duration[len] = {};

    switch (theme)
    {
    case 0:
        for (size_t i = 0; i < len; i++)
        {
            melody[i] = Pirates_note[i];
            duration[i] = Pirates_duration[i];
        }
        break;
    case 1:
        for (size_t i = 0; i < len; i++)
        {
            melody[i] = CrazyFrog_note[i];
            duration[i] = CrazyFrog_duration[i];
        }
        break;
    case 2:
        for (size_t i = 0; i < len; i++)
        {
            melody[i] = MarioUW_note[i];
            duration[i] = MarioUW_duration[i];
        }
        break;
    case 3:
        for (size_t i = 0; i < len; i++)
        {
            melody[i] = Titanic_note[i];
            duration[i] = Titanic_duration[i];
        }
        break;
    case 4:
        for (size_t i = 0; i < len; i++)
        {
            melody[i] = HomeAlone_note[i];
            duration[i] = HomeAlone_duration[i];
        }
        break;
    case 5:
        for (size_t i = 0; i < len; i++)
        {
            melody[i] = PinkPanther_note[i];
            duration[i] = PinkPanther_duration[i];
        }
        break;
    case 6:
        for (size_t i = 0; i < len; i++)
        {
            melody[i] = HappyBirthday_note[i];
            duration[i] = HappyBirthday_duration[i];
        }
        break;
    case 7:
        for (size_t i = 0; i < len; i++)
        {
            melody[i] = Nokia_note[i];
            duration[i] = Nokia_duration[i];
        }
        break;

    default:
        break;
    }

    for (int thisNote = 0; thisNote < len; thisNote++)
    {
        if (!play_notes)
        {
            ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
            vTaskDelete(NULL);
        }

        int noteDuration = 1000 / duration[thisNote]; // convert duration to time delay
        ledcWriteTone(LEDC_CHANNEL_BUZZER, melody[thisNote]);
        vTaskDelay(noteDuration / portTICK_PERIOD_MS);

        int pauseBetweenNotes = noteDuration * scale_duration;
        // int pauseBetweenNotes = noteDuration * 1.05; // Here 1.05 is tempo, increase to play it slower
        // int pauseBetweenNotes = noteDuration * 1.30;
        ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
        vTaskDelay(pauseBetweenNotes / portTICK_PERIOD_MS);
    }

    ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
    vTaskDelete(NULL);
}

SongsMelody::SongsMelody()
{
    ledcSetup(LEDC_CHANNEL_BUZZER, LEDC_BASE_FREQ_BUZZER, LEDC_TIMER_BUZZER_BIT);
    ledcAttachPin(BUZZER_PIN, LEDC_CHANNEL_BUZZER);
}

void SongsMelody::setMelody(int melody)
{
    theme = melody;
}

void SongsMelody::playMelody()
{
    play_notes = true;
    xTaskCreate(taskPlayNotes, "Play Notes", 1024 * 4, NULL, 5, NULL);
}

void SongsMelody::stopMelody()
{
    play_notes = false;
}
