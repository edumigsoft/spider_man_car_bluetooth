#ifndef __BATTERY_H__
#define __BATTERY_H__

class Battery
{
private:
    /* data */
public:
    bool battery_low = false;
    Battery();
    void loopBattery(unsigned long currentMillis);
};

#endif // __BATTERY_H__