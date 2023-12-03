#ifndef __TRACTION_H__
#define __TRACTION_H__

#include <Arduino.h>

// Setting PWM properties
#define LEDC_CHANNEL_MB3 2
#define LEDC_CHANNEL_MB4 3
#define LEDC_TIMER_8_BIT 8
#define LEDC_BASE_FREQ 5000

class Traction
{
private:
public:
    int speed = 0;

    Traction();
    void motorForward();
    void motorBack();
    void motorStop();
};

#endif // __TRACTION_H__