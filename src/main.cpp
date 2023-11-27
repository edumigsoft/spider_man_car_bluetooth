#include "BluetoothSerial.h"
// #include <Servo.h>
#include "esp32-hal-ledc.h"
// #include "Melody.h"
//
// #include "sounds.h"
#include "sounds/CarHorn.h" // A boring car horn
// #include "sounds/VwBeetleidle.h"

// Engine parameters ----------------------------------------------------------------------------------------------------
// Engine max. RPM in % of idle RPM. About 200% for big Diesels, 400% for fast running motors.
uint32_t MAX_RPM_PERCENTAGE = 320;       // NOTE! Was called TOP_SPEED_MULTIPLIER (TSM) in earlier versions and was a multiplier instead of a percentage!
volatile int hornVolumePercentage = 100; // Adjust the horn volume (usually = 100%)

// Sound volumes
volatile int16_t masterVolume = 100; // Master volume percentage
volatile uint8_t dacOffset = 0;

// Sound
volatile boolean hornTrigger = false; // Trigger for horn on / off

// Sound latches
volatile boolean hornLatch = false; // Horn latch bit

// Sampling intervals for interrupt timer (adjusted according to your sound file sampling rate)
uint32_t maxSampleInterval = 4000000 / hornSampleRate;
uint32_t minSampleInterval = 4000000 / hornSampleRate * 100 / MAX_RPM_PERCENTAGE;

// Interrupt timer for fixed sample rate playback (horn etc., playing in parallel with engine sound)
hw_timer_t *fixedTimer = NULL;
portMUX_TYPE fixedTimerMux = portMUX_INITIALIZER_UNLOCKED;
volatile uint32_t fixedTimerTicks = maxSampleInterval;

void IRAM_ATTR fixedPlaybackTimer()
{
  static uint32_t curHornSample = 0; // Index of currently loaded horn sample
  static int32_t a, a1, a2 = 0;      // Input signals "a" for mixer
  static int32_t b = 0;              // Input signals "b" for mixer
  static int32_t c = 0;              // Input signals "c" for mixer
  static int32_t d = 0;              // Input signals "d" for mixer

  if (hornTrigger || hornLatch)
  {
    fixedTimerTicks = 4000000 / hornSampleRate;         // our fixed sampling rate
    timerAlarmWrite(fixedTimer, fixedTimerTicks, true); // // change timer ticks, autoreload true

    if (curHornSample < hornSampleCount - 1)
    {
      a1 = (hornSamples[curHornSample] * hornVolumePercentage / 100);
      curHornSample++;
#ifdef HORN_LOOP // Optional "endless loop" (points to be defined manually in horn file)
      if (hornTrigger && curHornSample == hornLoopEnd)
        curHornSample = hornLoopBegin; // Loop, if trigger still present
#endif
    }
    else
    { // End of sample
      curHornSample = 0;
      a1 = 0;
      hornLatch = false;
    }
  }

  // Mixing sounds together **********************************************************************
  a = a1 + a2; // Horn & siren
  if (a < 2 && a > -2)
    a = 0; // Remove noise floor TODO, experimental
  // DAC output (groups mixed together) ****************************************************************************
  dacWrite(DAC2, constrain(((a * 8 / 10) + (b * 2 / 10) + c + d) * masterVolume / 100 + dacOffset, 0, 255)); // Mix signals, add 128 offset, write result to DAC
}

void setupFixedPlaybackTimer()
{
  // Interrupt timer for fixed sample rate playback
  fixedTimer = timerBegin(1, 20, true);                        // timer 1, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 20 -> 250 ns = 0.25 us, countUp
  timerAttachInterrupt(fixedTimer, &fixedPlaybackTimer, true); // edge (not level) triggered
  timerAlarmWrite(fixedTimer, fixedTimerTicks, true);          // autoreload true
  timerAlarmEnable(fixedTimer);                                // enable
}

//
BluetoothSerial SerialBT;
char command;
char commandOld;
int speed = 0;

// TaskHandle_t TaskP;

// Setting PWM properties
#define LEDC_CHANNEL_MB3 2
#define LEDC_CHANNEL_MB4 3
// #define LEDC_CHANNEL_TONE 5
#define LEDC_TIMER_8_BIT 8
#define LEDC_BASE_FREQ 5000

// Melody darthVader(" (ggg e,-. b,-- | g e,-. b,-- g+ (ddde,-.)* b,--  | g, e,-. b,-- g+");
// Melody darthVader(" (ggg e,-. b,-- | g e,-. b,-- g+ (ddde,-.)* b,--  | g, e,-. b,-- g+ | g* g-.g--  (g g,-. f-- (ed#)-- e-)* r- g#- c#* b#-.b-- |  (b,a)-- b,- r- e,- g, e,-. g,-- | b, g-. b,-- d*+  | g* g-.g--  (g g,-. f-- (ed#)-- e-)* r- g#- c#* b#-.b-- |  (b,a)-- b,- r- e,- g, e,-. b,-- | g e,-. b,-- g+ |)<<_ ");

// Servo servoDir = Servo();

void motorForward()
{
  ledcWrite(LEDC_CHANNEL_MB3, speed);
  ledcWrite(LEDC_CHANNEL_MB4, 0);

  Serial.printf("Forward, speed: %i\n", speed);
}

void motorBack()
{
  ledcWrite(LEDC_CHANNEL_MB3, 0);
  ledcWrite(LEDC_CHANNEL_MB4, speed);

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
  // servoDir.write(SERVO_PIN, 0);

  Serial.println("Direction Right");
}

void directionLeft()
{
  // servoDir.write(SERVO_PIN, 80);

  Serial.println("Direction Left");
}

void directionCenter()
{
  // servoDir.write(SERVO_PIN, 48);

  Serial.println("Direction Center");
}

// void setLoudness(int loudness)
// {
//   // Loudness could be use with a mapping function, according to your buzzer or sound-producing hardware
// #define MIN_HARDWARE_LOUDNESS 0
// #define MAX_HARDWARE_LOUDNESS 16
//   ledcWrite(LEDC_CHANNEL_TONE, map(loudness, -4, 4, MIN_HARDWARE_LOUDNESS, MAX_HARDWARE_LOUDNESS));
// }

// void toneESP(int pin, int frequency) // FOR ESP Platform, pin is unused
// {
//   ledcWriteTone(LEDC_CHANNEL_TONE, frequency);
// }

// void noToneESP(int pin) // FOR ESP Platform, pin is unused
// {
//   ledcWrite(LEDC_CHANNEL_TONE, 0);
// }

// void play(Melody melody)
// {
//   Serial.print("Melody length : ");
//   Serial.println(melody.length()); // Get the total length (number of notes) of the melody.

//   melody.restart(); // The melody iterator is restarted at the beginning.

//   while (melody.hasNext()) // While there is a next note to play.
//   {
//     melody.next(); // Move the melody note iterator to the next one.

//     // printInfo(melody);

//     unsigned int frequency = melody.getFrequency(); // Get the frequency in Hz of the curent note.
//     unsigned long duration = melody.getDuration();  // Get the duration in ms of the curent note.
//     unsigned int loudness = melody.getLoudness();   // Get the loudness of the curent note (in a subjective relative scale from -3 to +3).
//                                                     // Common interpretation will be -3 is really soft (ppp), and 3 really loud (fff).

//     if (frequency > 0)
//     {
//       toneESP(TONE_PIN, frequency);
//       setLoudness(loudness);
//     }
//     else
//     {
//       noToneESP(TONE_PIN);
//     }

//     // delay(duration);
//     vTaskDelay(duration / portTICK_PERIOD_MS);

//     // This 1 ms delay with no tone is added to let a "breathing" time between each note.
//     // Without it, identical consecutives notes will sound like just one long note.
//     noToneESP(TONE_PIN);
//     // delay(1);
//     vTaskDelay(1 / portTICK_PERIOD_MS);
//   }

//   noToneESP(TONE_PIN);
//   // delay(1000);
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
// }

// void TaskPlayer(void *arg)
// {
//   play(darthVader);

//   vTaskDelete(NULL);
// }

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  SerialBT.begin("SpiderManCarBlue");
  // while (!SerialBT)
  //   ;

  delay(2000);
  Serial.println();
  Serial.println("Setup Init");

  //
  directionCenter();

  //
  pinMode(CONNECTED_PIN, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(LEDC_CHANNEL_MB3, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  ledcSetup(LEDC_CHANNEL_MB4, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  ledcAttachPin(MOTOR_B_3, LEDC_CHANNEL_MB3);
  ledcAttachPin(MOTOR_B_4, LEDC_CHANNEL_MB4);

  motorStop();

  //
  // ledcSetup(LEDC_CHANNEL_TONE, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  // ledcAttachPin(TONE_PIN, LEDC_CHANNEL_TONE);
  // ledcWrite(LEDC_CHANNEL_TONE, 0);
  
  // 
  setupFixedPlaybackTimer();

  delay(1000);
  Serial.println("Setup End");
}

void loop()
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
      // play(darthVader);
      // xTaskCreate(TaskPlayer, "TaskPlayer", 1024 * 3, NULL, 5, &TaskP);

      hornTrigger = true;
      hornLatch = true;

      Serial.println("Horn On");
      break;
    case 'v':
      // vTaskDelete(TaskP);
      // TaskP = NULL;

      hornTrigger = false;

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
      // digitalWrite(pin1, LOW);
      // digitalWrite(pin2, LOW);
      // digitalWrite(pin26, LOW);
      // digitalWrite(pin25, LOW);

      Serial.println("Everything OFF");
      break;
    }
    case 'S':
    default:
    {
      directionCenter();
      motorStop();
      break;
    }
    }
  }

  // digitalWrite(CONNECTED_PIN, LOW);
  // delay(20);
}
