#include "BluetoothSerial.h"
#include <Servo.h>
// #include "pitches.h"
// #include "themes.h"
#include "songs_melody.h"

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
SongsMelody songsMelody = SongsMelody();
// #define LEDC_CHANNEL_BUZZER 5
// // #define LEDC_TIMER_BUZZER_BIT 8
// // #define LEDC_TIMER_BUZZER_BIT 10
// #define LEDC_TIMER_BUZZER_BIT 13
// // #define LEDC_BASE_FREQ_BUZZER 1000
// // #define LEDC_BASE_FREQ_BUZZER 2000
// #define LEDC_BASE_FREQ_BUZZER 5000

// int theme = 2;
// volatile bool play_notes = false;

// void taskPlayNotes(void *)
// {
//   int len = 0;

//   switch (theme)
//   {
//   case 0:
//     len = sizeof(Pirates_note) / sizeof(int);
//     break;
//   case 1:
//     len = sizeof(CrazyFrog_note) / sizeof(int);
//     break;
//   case 2:
//     len = sizeof(MarioUW_note) / sizeof(int);
//     break;
//   case 3:
//     len = sizeof(Titanic_note) / sizeof(int);
//     break;

//   default:
//     break;
//   }

//   int melody[len] = {};
//   int duration[len] = {};

//   switch (theme)
//   {
//   case 0:
//     for (size_t i = 0; i < len; i++)
//     {
//       melody[i] = Pirates_note[i];
//       duration[i] = Pirates_duration[i];
//     }
//     break;
//   case 1:
//     for (size_t i = 0; i < len; i++)
//     {
//       melody[i] = CrazyFrog_note[i];
//       duration[i] = CrazyFrog_duration[i];
//     }
//     break;
//   case 2:
//     for (size_t i = 0; i < len; i++)
//     {
//       melody[i] = MarioUW_note[i];
//       duration[i] = MarioUW_duration[i];
//     }
//     break;
//   case 3:
//     for (size_t i = 0; i < len; i++)
//     {
//       melody[i] = Titanic_note[i];
//       duration[i] = Titanic_duration[i];
//     }
//     break;

//   default:
//     break;
//   }

//   for (int thisNote = 0; thisNote < len; thisNote++)
//   {
//     if (!play_notes)
//     {
//       ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
//       vTaskDelete(NULL);
//     }

//     int noteDuration = 1000 / duration[thisNote]; // convert duration to time delay
//     ledcWriteTone(LEDC_CHANNEL_BUZZER, melody[thisNote]);
//     vTaskDelay(noteDuration / portTICK_PERIOD_MS);

//     int pauseBetweenNotes = noteDuration * 1.05; // Here 1.05 is tempo, increase to play it slower
//     // int pauseBetweenNotes = noteDuration * 1.30;
//     ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
//     vTaskDelay(pauseBetweenNotes / portTICK_PERIOD_MS);
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
  // ledcSetup(LEDC_CHANNEL_BUZZER, LEDC_BASE_FREQ_BUZZER, LEDC_TIMER_BUZZER_BIT);
  // ledcAttachPin(BUZZER_PIN, LEDC_CHANNEL_BUZZER);
  songsMelody.setMelody(5);

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
        // play_notes = true;
        // xTaskCreate(taskPlayNotes, "Play Notes", 1024 * 4, NULL, 5, NULL);
        songsMelody.playMelody();

        Serial.println("Horn On");
        break;
      case 'v':
        // play_notes = false;
        songsMelody.stopMelody();

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
