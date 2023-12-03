#include "direction.h"

Servo servoDir = Servo();

Direction::Direction()
{
    ledcSetup(LEDC_CHANNEL_MB3, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
    ledcSetup(LEDC_CHANNEL_MB4, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
    ledcAttachPin(MOTOR_B_3, LEDC_CHANNEL_MB3);
    ledcAttachPin(MOTOR_B_4, LEDC_CHANNEL_MB4);
}

void Direction::directionRight()
{
    servoDir.write(SERVO_PIN, 0);

    Serial.println("Direction Right");
}

void Direction::directionLeft()
{
    servoDir.write(SERVO_PIN, 80);

    Serial.println("Direction Left");
}

void Direction::directionCenter()
{
    servoDir.write(SERVO_PIN, 48);

    Serial.println("Direction Center");
}
