#ifndef CurrentSensor_H
#define CurrentSensor_H

#include "Arduino.h"

class CurrentSensor
{
private:
    uint8_t Apin;
    float Vsensor, Asensor,mVperAmpValue;
    uint16_t sampleCount;
    uint16_t readVcc();

public:
    CurrentSensor(uint8_t _Apin);
    void init(uint16_t _sampleCount, float _mVperAmpValue);
    float getSensor();
};

#endif