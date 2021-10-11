/******************************************************************
*********                       Includes                  *********
******************************************************************/
#include "ActiveDriver.h"

/**
 * ActiveDriver::ActiveDriver 
 * 
 * @param  {uint8_t} _pin : Signal Pin Of The Active Device
 */
ActiveDriver::ActiveDriver(uint8_t _pin)
{
    pin = _pin;
}

/**
 * ActiveDriver initialization
 * 
 */
void ActiveDriver::init()
{
    pinMode(pin, INPUT);
}

/**
 * ActiveDriver 
 * 
 * @return {bool}  : return the status of the driver
 */
bool ActiveDriver::status()
{
    return driverStatus;
}

/**
 * ActiveDriver activate
 * 
 */
void ActiveDriver::activate()
{
    pinMode(pin,OUTPUT);
    digitalWrite(pin, LOW);
    driverStatus = true;
}

/**
 * ActiveDriver Deactivate
 * 
 */
void ActiveDriver::deactivate()
{
    digitalWrite(pin, HIGH);
    pinMode(pin,INPUT);
    driverStatus = false;
}