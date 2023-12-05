#include <Arduino.h>
#include "battery.h"

const long interval_battery_read = 3000;
const long interval_battery_low = 50;
unsigned long previousMillisBattery = 0;
unsigned long previousMillisBatteryLow = 0;

Battery::Battery()
{
    pinMode(BATTERY_LOW_PIN, OUTPUT);
    digitalWrite(BATTERY_LOW_PIN, LOW);
    analogSetPinAttenuation(BATTERY_ADC_PIN, ADC_11db);
}

void Battery::loopBattery(unsigned long currentMillis)
{
    if (currentMillis - previousMillisBattery >= interval_battery_read && !battery_low)
    {
        previousMillisBattery = currentMillis;

        float value = analogRead(BATTERY_ADC_PIN);
        float batteryVolts = map(value, 0.0f, 4095.0f, 0.0f, BATTERY_VOLTS);
        float batteryLevel = map(value, 0.0f, 4095.0f, 0.0f, 100.0f);

        Serial.printf("Battery, value: %4.0f, level: %3.0f %%, volts: %1.2f V\n", value, batteryLevel, batteryVolts);

        if (value <= BATTERY_LIMIT_MIN)
        {
            battery_low = true;
            Serial.println("Alarm battery low!");
        }
    }

    if (currentMillis - previousMillisBatteryLow >= interval_battery_low && battery_low)
    {
        previousMillisBatteryLow = currentMillis;

        digitalWrite(BATTERY_LOW_PIN, !digitalRead(BATTERY_LOW_PIN));
    }
}
