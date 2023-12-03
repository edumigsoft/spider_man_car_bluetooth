#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <Arduino.h>
#include <Servo.h>

// Setting PWM properties
#define LEDC_CHANNEL_MB3 2
#define LEDC_CHANNEL_MB4 3
#define LEDC_TIMER_8_BIT 8
#define LEDC_BASE_FREQ 5000

class Direction
{
private:
    int speed = 0;

public:
    Direction();
    void directionRight();
    void directionLeft();
    void directionCenter();
};

#endif // __DIRECTION_H__