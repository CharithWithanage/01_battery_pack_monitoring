#ifndef ACTIVE_DRIVER_H
#define ACTIVE_DRIVER_H

#include "Arduino.h"
class ActiveDriver
{
private:
    uint8_t pin;
    bool driverStatus = false;

public:
    ActiveDriver(uint8_t _pin);
    void init();
    bool status();
    void activate();
    void deactivate();
};

#endif