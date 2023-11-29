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

Servo servoDir = Servo();

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
  directionCenter();

  //
  pinMode(CONNECTED_PIN, OUTPUT);

  // configure Motor PWM functionalitites
  ledcSetup(LEDC_CHANNEL_MB3, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  ledcSetup(LEDC_CHANNEL_MB4, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  ledcAttachPin(MOTOR_B_3, LEDC_CHANNEL_MB3);
  ledcAttachPin(MOTOR_B_4, LEDC_CHANNEL_MB4);

  motorStop();

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
      Serial.println("Horn On");
      break;
    case 'v':
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
