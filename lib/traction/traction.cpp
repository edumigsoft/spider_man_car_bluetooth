#include "traction.h"

Traction::Traction()
{
}

void Traction::motorForward()
{
    ledcWrite(LEDC_CHANNEL_MB3, 0);
    ledcWrite(LEDC_CHANNEL_MB4, speed);

    Serial.printf("Forward, speed: %i\n", speed);
}

void Traction::motorBack()
{
    ledcWrite(LEDC_CHANNEL_MB3, speed);
    ledcWrite(LEDC_CHANNEL_MB4, 0);

    Serial.printf("Back, speed: %i\n", speed);
}

void Traction::motorStop()
{
    ledcWrite(LEDC_CHANNEL_MB3, 0);
    ledcWrite(LEDC_CHANNEL_MB4, 0);

    Serial.println("Stop");
}
