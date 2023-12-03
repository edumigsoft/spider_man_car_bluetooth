#include "BluetoothSerial.h"
#include "direction.h"
#include "traction.h"
#include "battery.h"
#include "songs_melody.h"

BluetoothSerial SerialBT;
char command;
char commandOld;

// Direction
Direction direction = Direction();

// Traction
Traction traction = Traction();

// Buzzer / Mellody
SongsMelody songsMelody = SongsMelody();

// Battery
Battery battery = Battery();

//
const long interval_status = 100;
const long interval_status_connected = 1000;
unsigned long previousMillisStatus = 0;
unsigned long previousMillisStatusConnected = 0;
bool status_connected = false;

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

  // Direction
  direction.directionCenter();

  // Traction
  traction.motorStop();

  // Buzzer
  songsMelody.setMelody(5);

  //
  delay(1000);
  Serial.println("Setup End");
}

void loop()
{
  unsigned long currentMillis = millis();

  if (!battery.battery_low)
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
        traction.motorForward();
        direction.directionCenter();
        break;
      }
      case 'I':
      { // frente direita
        traction.motorForward();
        direction.directionRight();

        Serial.println("Forward Right");
        break;
      }
      case 'G':
      { // frente esquerda
        traction.motorForward();
        direction.directionLeft();

        Serial.println("Forward Left");
        break;
      }
      case 'R':
      { // direita
        traction.motorStop();
        direction.directionRight();
        break;
      }
      case 'L':
      { // esquerda
        traction.motorStop();
        direction.directionLeft();
        break;
      }
      case 'B':
      { // ré
        traction.motorBack();
        direction.directionCenter();
        break;
      }
      case 'H':
      { // ré esquerda
        traction.motorBack();
        direction.directionLeft();

        Serial.println("Back Left");
        break;
      }
      case 'J':
      { // ré direita
        traction.motorBack();
        direction.directionRight();

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
        songsMelody.playMelody();

        Serial.println("Horn On");
        break;
      case 'v':
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
        traction.speed = 0;
        Serial.printf("Speed 0: %i\n", traction.speed);
        break;
      }
      case '1':
      {
        traction.speed = 120;
        Serial.printf("Speed 1: %i\n", traction.speed);
        break;
      }
      case '2':
      {
        traction.speed = 130;
        Serial.printf("Speed 2: %i\n", traction.speed);
        break;
      }
      case '3':
      {
        traction.speed = 140;
        Serial.printf("Speed 3: %i\n", traction.speed);
        break;
      }
      case '4':
      {
        traction.speed = 160;
        Serial.printf("Speed 4: %i\n", traction.speed);
        break;
      }
      case '5':
      {
        traction.speed = 180;
        Serial.printf("Speed 5: %i\n", traction.speed);
        break;
      }
      case '6':
      {
        traction.speed = 200;
        Serial.printf("Speed 6: %i\n", traction.speed);
        break;
      }
      case '7':
      {
        traction.speed = 210;
        Serial.printf("Speed 7: %i\n", traction.speed);
        break;
      }
      case '8':
      {
        traction.speed = 220;
        Serial.printf("Speed 8: %i\n", traction.speed);
        break;
      }
      case '9':
      {
        traction.speed = 240;
        Serial.printf("Speed 9: %i\n", traction.speed);
        break;
      }
      case 'q':
      {
        traction.speed = 255;
        Serial.printf("Speed 10: %i\n", traction.speed);
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
        direction.directionCenter();
        traction.motorStop();
        break;
      }
      }
    }
    
    if (currentMillis - previousMillisStatus >= interval_status && !status_connected)
    {
      previousMillisStatus = currentMillis;

      digitalWrite(CONNECTED_PIN, !digitalRead(CONNECTED_PIN));
    }

    if (currentMillis - previousMillisStatusConnected >= interval_status_connected && status_connected)
    {
      previousMillisStatusConnected = currentMillis;

      digitalWrite(CONNECTED_PIN, !digitalRead(CONNECTED_PIN));
    }
  }

  battery.loopBattery(currentMillis);
}
