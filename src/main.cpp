/**
 * reference
 * https://autocorerobotica.blog.br/aprenda-a-reproduzir-musicas-com-o-modulo-buzzer-2/
 */

#include "BluetoothSerial.h"
#include <Servo.h>

BluetoothSerial SerialBT;
char command;
char commandOld;
int speed = 0;

// Setting PWM properties
#define LEDC_CHANNEL_MB3 2
#define LEDC_CHANNEL_MB4 3
#define LEDC_TIMER_8_BIT 8
#define LEDC_BASE_FREQ 5000

// Buzzer / Mellody
#define LEDC_CHANNEL_BUZZER 5
// #define LEDC_TIMER_BUZZER_BIT 8
// #define LEDC_TIMER_BUZZER_BIT 10
#define LEDC_TIMER_BUZZER_BIT 13
// #define LEDC_BASE_FREQ_BUZZER 1000
// #define LEDC_BASE_FREQ_BUZZER 2000
#define LEDC_BASE_FREQ_BUZZER 5000

// Melody
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#define OITAVA_OFFSET 0

int notas[] = {0,
               NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
               NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
               NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
               NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7};

#define ehDigito(n) (n >= '0' && n <= '9')

volatile bool play_notes = false;

// const char *song = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
// const char *song = "Arkanoid:d=4,o=5,b=140:8g6,16p,16g.6,2a#6,32p,8a6,8g6,8f6,8a6,2g6";
// const char *song = "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
// const char *song = "Barbie:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#";
// const char *song = "Coca cola:d=4,o=5,b=125:8f#6,8f#6,8f#6,8f#6,g6,8f#6,e6,8e6,8a6,f#6,d6,2p";
// const char *song = "FunkyTown:d=4,o=4,b=125:8c6,8c6,8a#5,8c6,8p,8g5,8p,8g5,8c6,8f6,8e6,8c6,2p,8c6,8c6,8a#5,8c6,8p,8g5,8p,8g5,8c6,8f6,8e6,8c6";
// const char *song = "MASH:d=8,o=5,b=140:4a,4g,f#,g,p,f#,p,g,p,f#,p,2e.,p,f#,e,4f#,e,f#,p,e,p,4d.,p,f#,4e,d,e,p,d,p,e,p,d,p,2c#.,p,d,c#,4d,c#,d,p,e,p,4f#,p,a,p,4b,a,b,p,a,p,b,p,2a.,4p,a,b,a,4b,a,b,p,2a.,a,4f#,a,b,p,d6,p,4e.6,d6,b,p,a,p,2b";
// const char *song = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
// const char *song = "Spiderman:d=4,o=6,b=200:c,8d#,g.,p,f#,8d#,c.,p,c,8d#,g,8g#,g,f#,8d#,c.,p,f,8g#,c7.,p,a#,8g#,f.,p,c,8d#,g.,p,f#,8d#,c,p,8g#,2g,p,8f#,f#,8d#,f,8d#,2c";
// const char *song = "McGyver:d=4,o=4,b=160:8c5,8c5,8c5,8c5,2b,8f#,a,2g,8c5,c5,b,8a,8b,8a,g,e5,2a,b.,8p,8c5,8b,8a,c5,8b,8a,d5,8c5,8b,d5,8c5,8b,e5,8d5,8e5,f#5,b,1g5,8p,8g5,8e5,8c5,8f#5,8d5,8b,8e5,8c5,8a,8d5,8b,8g,c5,b,8c5,8b,8a,8g,a#,a,8g.";
const char *song = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
// const char *song = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
// const char *song = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
// const char *song = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
// const char *song = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
// const char *song = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
// const char *song = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
// const char *song = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
// const char *song = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
// const char *song = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
// const char *song = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
// const char *song = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";

void play_rtttl(void *arg)
{
  char *p = (char *)arg;

  while (true)
  {
    byte vazia_dur = 4;
    byte vazia_oct = 6;
    int bpm = 63;
    int num;
    long notaInteira;
    long duracao;
    long pausa;
    byte note;
    byte escala;

    while (*p != ':')
      p++;
    p++;

    // get default duracao
    if (*p == 'd')
    {
      p++;
      p++; // pula "d="
      num = 0;
      while (ehDigito(*p))
      {
        num = (num * 10) + (*p++ - '0');
      }
      if (num > 0)
        vazia_dur = num;
      p++;
    }

    Serial.print("dur: ");
    Serial.println(vazia_dur, 10);

    // obtive uma oitava padrão
    if (*p == 'o')
    {
      p++;
      p++; // pula "o="
      num = *p++ - '0';
      if (num >= 3 && num <= 7)
        vazia_oct = num;
      p++;
    }

    Serial.print("doct: ");
    Serial.println(vazia_oct, 10);

    // obtem o BPM
    if (*p == 'b')
    {
      p++;
      p++; // pula "b="
      num = 0;
      while (ehDigito(*p))
      {
        num = (num * 10) + (*p++ - '0');
      }
      bpm = num;
      p++; // skip colon
    }

    Serial.print("bpm: ");
    Serial.println(bpm, 10);

    // O BPM geralmente expressa o número de quartas notas por minuto
    notaInteira = (60 * 1000L / bpm) * 4; // este é o momento da nota inteira (em milissegundos)

    Serial.print("wn: ");
    Serial.println(notaInteira, 10);

    // agora começa o loop de notas
    while (*p)
    {
      if (!play_notes)
      {
        ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
        vTaskDelete(NULL);
      }

      // primeiro, obtem a nota duracao, se possível
      num = 0;
      while (ehDigito(*p))
      {
        num = (num * 10) + (*p++ - '0');
      }

      if (num)
        duracao = notaInteira / num;
      else
        duracao = notaInteira / vazia_dur; // precisamos verificar se somos uma nota pontilhada após

      // now get the note
      note = 0;

      switch (*p)
      {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
      }
      p++;

      // obtem o sustenido
      if (*p == '#')
      {
        note++;
        p++;
      }

      // obtenha opcional '.' nota pontilhada
      if (*p == '.')
      {
        duracao += duracao / 2;
        p++;
      }

      pausa = duracao * 0.9;         // 10;
      duracao = duracao * 0.9; // 5;

      // obtenha escalar
      if (ehDigito(*p))
      {
        escala = *p - '0';
        p++;
      }
      else
      {
        escala = vazia_oct;
      }

      escala += OITAVA_OFFSET;

      if (*p == ',')
        p++; // skip comma for next note (or we may be at the end)

      // now play the note

      if (note)
      {
        Serial.print("Tocando: ");
        Serial.print(escala, 10);
        Serial.print(' ');
        Serial.print(note, 10);
        Serial.print(" (");
        Serial.print(notas[(escala - 4) * 12 + note], 10);
        Serial.print(") ");
        Serial.println(duracao, 10);
        // tonalidade.play(notas[(escala - 4) * 12 + note]);
        ledcWriteTone(LEDC_CHANNEL_BUZZER, notas[(escala - 4) * 12 + note]);
        // delay(duracao);
        vTaskDelay(duracao / portTICK_PERIOD_MS);
        ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
      }
      else
      {
        Serial.print("Pausando: ");
        // Serial.println(duracao, 10);
        Serial.println(pausa, 10);
        // delay(duracao);
        // vTaskDelay(duracao / portTICK_PERIOD_MS);
        vTaskDelay(pausa / portTICK_PERIOD_MS);
      }
    }
  }

  ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
  vTaskDelete(NULL);
}

// 262 //DO
// 294 //RE
// 330 //MI
// 349 //FA
// 392 //SOL
// 440 //LA
// 494 //SI

// Melody Super Mario World
// int melody[] = {660, 660, 660, 510, 660, 770, 380, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 500, 500, 500, 580, 660, 500, 430, 380, 500, 500, 500, 500, 580, 660, 870, 760, 500, 500, 500, 500, 580, 660, 500, 430, 380, 660, 660, 660, 510, 660, 770, 380};

// int duration_of_notes[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 60, 80, 60, 80, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 80, 100, 100, 100, 100, 100, 100, 100};
// int pause_after_notes[] = {150, 300, 300, 100, 300, 550, 575, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 350, 150, 150, 550, 325, 600, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 300, 100, 300, 550, 575};

// const int count_notes = 156;
// volatile bool play_notes = false;

// void taskPlayNotes(void *)
// {
//   for (int i = 0; i < count_notes; i++)
//   {
//     if (!play_notes)
//     {
//       ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
//       vTaskDelete(NULL);
//     }

//     ledcWriteTone(LEDC_CHANNEL_BUZZER, melody[i]);
//     vTaskDelay(duration_of_notes[i] / portTICK_PERIOD_MS);
//     ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
//     vTaskDelay(pause_after_notes[i] / portTICK_PERIOD_MS);
//   }

//   ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
//   vTaskDelete(NULL);
// }

//
const long interval_status = 100;
unsigned long previousMillisStatus = 0;
bool status_connected = false;

//
Servo servoDir = Servo();

void motorForward()
{
  ledcWrite(LEDC_CHANNEL_MB3, 0);
  ledcWrite(LEDC_CHANNEL_MB4, speed);

  Serial.printf("Forward, speed: %i\n", speed);
}

void motorBack()
{
  ledcWrite(LEDC_CHANNEL_MB3, speed);
  ledcWrite(LEDC_CHANNEL_MB4, 0);

  Serial.printf("Back, speed: %i\n", speed);
}

void motorStop()
{
  ledcWrite(LEDC_CHANNEL_MB3, 0);
  ledcWrite(LEDC_CHANNEL_MB4, 0);

  Serial.println("Stop");
}

void directionRight()
{
  servoDir.write(SERVO_PIN, 0);

  Serial.println("Direction Right");
}

void directionLeft()
{
  servoDir.write(SERVO_PIN, 80);

  Serial.println("Direction Left");
}

void directionCenter()
{
  servoDir.write(SERVO_PIN, 48);

  Serial.println("Direction Center");
}

// Battery
const long interval_battery_read = 3000;
const long interval_battery_low = 50;
unsigned long previousMillisBattery = 0;
unsigned long previousMillisBatteryLow = 0;
bool battery_low = false;

void loopBattery()
{
  float value = analogRead(BATTERY_PIN);
  float batteryVolts = map(value, 0.0f, 4095.0f, 0.0f, BATTERY_VOLTS);
  float batteryLevel = map(value, 0.0f, 4095.0f, 0.0f, 100.0f);

  Serial.printf("Battery1, value: %4.0f, level: %3.0f %%, volts: %1.2f V\n", value, batteryLevel, batteryVolts);

  if (value <= BATTERY_LIMIT_MIN)
  {
    battery_low = true;
    Serial.println("Alarm battery low!");
  }
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  SerialBT.begin("SpiderManCarBlue");

  delay(1000);
  Serial.println();
  Serial.println("Setup Init");

  //
  pinMode(CONNECTED_PIN, OUTPUT);
  digitalWrite(CONNECTED_PIN, LOW);

  // configure Motor PWM functionalitites
  ledcSetup(LEDC_CHANNEL_MB3, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  ledcSetup(LEDC_CHANNEL_MB4, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  ledcAttachPin(MOTOR_B_3, LEDC_CHANNEL_MB3);
  ledcAttachPin(MOTOR_B_4, LEDC_CHANNEL_MB4);

  // Buzzer
  pinMode(LEDC_CHANNEL_BUZZER, OUTPUT);
  ledcSetup(LEDC_CHANNEL_BUZZER, LEDC_BASE_FREQ_BUZZER, LEDC_TIMER_BUZZER_BIT);
  ledcAttachPin(BUZZER_PIN, LEDC_CHANNEL_BUZZER);
  ledcWrite(LEDC_CHANNEL_BUZZER, 10); // 255);

  // Battery
  analogSetPinAttenuation(BATTERY_PIN, ADC_11db);

  //
  directionCenter();
  motorStop();

  delay(1000);
  Serial.println("Setup End");
}

void loop()
{
  unsigned long currentMillis = millis();

  if (!battery_low)
  {
    /*
    Forward------------------F

    Back---------------------B

    Left---------------------L

    Right--------------------R

    Forward Left-------------G

    Forward Right------------I

    Back Left----------------H

    Back Right---------------J

    Stop---------------------S

    Front Lights On----------W

    Front Lights Off---------w (lower case)

    Back Lights On-----------U

    Back Lights Off----------u (lower case)

    Horn On------------------V

    Horn Off-----------------v (lower case)

    Extra On-----------------X

    Extra Off----------------x (lower case)

    Speed 0------------------0

    Speed 10-----------------1

    Speed 20-----------------2

    Speed 30-----------------3

    Speed 40-----------------4

    Speed 50-----------------5

    Speed 60-----------------6

    Speed 70-----------------7

    Speed 80-----------------8

    Speed 90-----------------9

    Speed 100----------------q

    Everything OFF-----------D (Tudo desligado)
    */

    if (SerialBT.available())
    {
      command = SerialBT.read();

      // Serial.print("command: ");
      // Serial.println(command);
    }

    if (command != commandOld)
    {
      commandOld = command;

      Serial.print("command: ");
      Serial.println(command);

      switch (command)
      {
      case 'F':
      { // move frente
        motorForward();
        directionCenter();
        break;
      }
      case 'I':
      { // frente direita
        motorForward();
        directionRight();

        Serial.println("Forward Right");
        break;
      }
      case 'G':
      { // frente esquerda
        motorForward();
        directionLeft();

        Serial.println("Forward Left");
        break;
      }
      case 'R':
      { // direita
        motorStop();
        directionRight();
        break;
      }
      case 'L':
      { // esquerda
        motorStop();
        directionLeft();
        break;
      }
      case 'B':
      { // ré
        motorBack();
        directionCenter();
        break;
      }
      case 'H':
      { // ré esquerda
        motorBack();
        directionLeft();

        Serial.println("Back Left");
        break;
      }
      case 'J':
      { // ré direita
        motorBack();
        directionRight();

        Serial.println("Back Right");
        break;
      }
      case 'W':
        Serial.println("Front Lights");
        break;
      case 'w':
        Serial.println("Front Lights Off");
        break;
      case 'U':
        Serial.println("Back Lights On");
        break;
      case 'u':
        Serial.println("Back Lights Off");
        break;
      case 'V':
        play_notes = true;
        // xTaskCreate(taskPlayNotes, "Play Notes", 1024 * 4, NULL, 5, NULL);
        xTaskCreate(play_rtttl, "Play RTTTL", 1024 * 4, &song, 5, NULL);

        Serial.println("Horn On");
        break;
      case 'v':
        play_notes = false;

        Serial.println("Horn Off");
        break;
      case 'X':
        Serial.println("Extra On");
        break;
      case 'x':
        Serial.println("Extra Off");
        break;
      case '0':
      {
        speed = 0;
        Serial.printf("Speed 0: %i\n", speed);
        break;
      }
      case '1':
      {
        speed = 120;
        Serial.printf("Speed 1: %i\n", speed);
        break;
      }
      case '2':
      {
        speed = 130;
        Serial.printf("Speed 2: %i\n", speed);
        break;
      }
      case '3':
      {
        speed = 140;
        Serial.printf("Speed 3: %i\n", speed);
        break;
      }
      case '4':
      {
        speed = 160;
        Serial.printf("Speed 4: %i\n", speed);
        break;
      }
      case '5':
      {
        speed = 180;
        Serial.printf("Speed 5: %i\n", speed);
        break;
      }
      case '6':
      {
        speed = 200;
        Serial.printf("Speed 6: %i\n", speed);
        break;
      }
      case '7':
      {
        speed = 210;
        Serial.printf("Speed 7: %i\n", speed);
        break;
      }
      case '8':
      {
        speed = 220;
        Serial.printf("Speed 8: %i\n", speed);
        break;
      }
      case '9':
      {
        speed = 240;
        Serial.printf("Speed 9: %i\n", speed);
        break;
      }
      case 'q':
      {
        speed = 255;
        Serial.printf("Speed 10: %i\n", speed);
        break;
      }
      case 'D':
      { // desliga
        status_connected = false;

        Serial.println("Everything OFF");
        break;
      }
      case 'S':
      default:
      {
        status_connected = true;
        digitalWrite(CONNECTED_PIN, LOW);
        directionCenter();
        motorStop();
        break;
      }
      }
    }

    if (currentMillis - previousMillisStatus >= interval_status && !status_connected)
    {
      previousMillisStatus = currentMillis;

      digitalWrite(CONNECTED_PIN, !digitalRead(CONNECTED_PIN));
    }

    if (currentMillis - previousMillisBattery >= interval_battery_read && !battery_low)
    {
      previousMillisBattery = currentMillis;

      // loopBattery();
    }
  }

  if (currentMillis - previousMillisBatteryLow >= interval_battery_low && battery_low)
  {
    previousMillisBatteryLow = currentMillis;

    digitalWrite(CONNECTED_PIN, !digitalRead(CONNECTED_PIN));
  }
}
