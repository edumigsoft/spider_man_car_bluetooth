#include "BluetoothSerial.h"
#include <Servo.h>

BluetoothSerial SerialBT;
char command;
char commandOld;
int speed = 0;

// Setting PWM properties
#define LEDC_CHANNEL_MB3 2
#define LEDC_CHANNEL_MB4 3
#define LEDC_CHANNEL_BUZZER 5
#define LEDC_TIMER_8_BIT 8
#define LEDC_TIMER_13_BIT 13
#define LEDC_BASE_FREQ 5000
#define LEDC_BASE_FREQ_BUZZER 5000 // 2000

// const char *tetris = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
// const char *arkanoid = "Arkanoid:d=4,o=5,b=140:8g6,16p,16g.6,2a#6,32p,8a6,8g6,8f6,8a6,2g6";
// const char *mario = "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
// const char *barbie = "Barbie:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#";
// const char *coca_cola = "Coca cola:d=4,o=5,b=125:8f#6,8f#6,8f#6,8f#6,g6,8f#6,e6,8e6,8a6,f#6,d6,2p";
// const char *funk_town = "FunkyTown:d=4,o=4,b=125:8c6,8c6,8a#5,8c6,8p,8g5,8p,8g5,8c6,8f6,8e6,8c6,2p,8c6,8c6,8a#5,8c6,8p,8g5,8p,8g5,8c6,8f6,8e6,8c6";
// const char *spider_man = "Spiderman:d=4,o=6,b=200:c,8d#,g.,p,f#,8d#,c.,p,c,8d#,g,8g#,g,f#,8d#,c.,p,f,8g#,c7.,p,a#,8g#,f.,p,c,8d#,g.,p,f#,8d#,c,p,8g#,2g,p,8f#,f#,8d#,f,8d#,2c";
// const char *macgyver = "McGyver:d=4,o=4,b=160:8c5,8c5,8c5,8c5,2b,8f#,a,2g,8c5,c5,b,8a,8b,8a,g,e5,2a,b.,8p,8c5,8b,8a,c5,8b,8a,d5,8c5,8b,d5,8c5,8b,e5,8d5,8e5,f#5,b,1g5,8p,8g5,8e5,8c5,8f#5,8d5,8b,8e5,8c5,8a,8d5,8b,8g,c5,b,8c5,8b,8a,8g,a#,a,8g.";

// 262 //DO
// 294 //RE
// 330 //MI
// 349 //FA
// 392 //SOL
// 440 //LA
// 494 //SI

// Melody Super Mario World
int melody[] = {660, 660, 660, 510, 660, 770, 380, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 500, 760, 720, 680, 620, 650, 1020, 1020, 1020, 380, 500, 760, 720, 680, 620, 650, 380, 430, 500, 430, 500, 570, 585, 550, 500, 380, 500, 500, 500, 500, 500, 500, 500, 580, 660, 500, 430, 380, 500, 500, 500, 500, 580, 660, 870, 760, 500, 500, 500, 500, 580, 660, 500, 430, 380, 660, 660, 660, 510, 660, 770, 380};

int duration_of_notes[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 80, 100, 100, 100, 80, 50, 100, 80, 50, 80, 80, 80, 80, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 150, 200, 80, 80, 80, 100, 100, 100, 100, 100, 150, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 60, 80, 60, 80, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 60, 80, 60, 80, 80, 80, 80, 80, 80, 100, 100, 100, 100, 100, 100, 100};
int pause_after_notes[] = {150, 300, 300, 100, 300, 550, 575, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 450, 400, 500, 300, 330, 150, 300, 200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 360, 300, 300, 150, 300, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 350, 150, 150, 550, 325, 600, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 300, 100, 300, 550, 575};

const int count_notes = 156;
volatile bool play_notes = false;

void taskPlayNotes(void *)
{
  for (int i = 0; i < count_notes; i++)
  {
    if (!play_notes)
    {
      ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
      vTaskDelete(NULL);
    }

    ledcWriteTone(LEDC_CHANNEL_BUZZER, melody[i]);
    vTaskDelay(duration_of_notes[i] / portTICK_PERIOD_MS);
    ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
    vTaskDelay(pause_after_notes[i] / portTICK_PERIOD_MS);
  }

  ledcWriteTone(LEDC_CHANNEL_BUZZER, 0);
  vTaskDelete(NULL);
}

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
  ledcSetup(LEDC_CHANNEL_BUZZER, LEDC_BASE_FREQ_BUZZER, LEDC_TIMER_13_BIT); // LEDC_TIMER_8_BIT);
  ledcAttachPin(BUZZER_PIN, LEDC_CHANNEL_BUZZER);

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
        xTaskCreate(taskPlayNotes, "Play Notes", 1024 * 4, NULL, 5, NULL);

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
