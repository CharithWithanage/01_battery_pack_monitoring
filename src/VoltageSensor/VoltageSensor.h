#ifndef VoltageSensor_H
#define VoltageSensor_H

#include "Arduino.h"

class VoltageSensor
{
private:
    uint8_t Vpin;
    float Vsensor, Asensor;
    uint16_t sampleCount;
    uint16_t readVcc();

public:
    VoltageSensor(uint8_t _Apin);
    void init(uint16_t _sampleCount);
    float getSensor();
};

#endif