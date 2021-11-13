/******************************************************************
*********                       Includes                  *********
******************************************************************/
#include "VoltageSensor.h"

/**
 * VoltageSensor::VoltageSensor 
 * 
 * @param  {uint8_t} _Vpin : VoltageSensor sensor Pin
 */
VoltageSensor::VoltageSensor(uint8_t _Vpin)
{
    Vpin = _Vpin;
}

/**
 * VoltageSensor 
 * 
 * @param  {uint16_t} _sampleCount : Sample count 
 */
void VoltageSensor::init(uint16_t _sampleCount)
{
    sampleCount = _sampleCount;
}

/**
 * VoltageSensor 
 * 
 * @return {float}  : RMS Current Value
 */
float VoltageSensor::getSensor()
{
    float voltageSampleRead;
    float voltageSamplSum = 0;
    float RMSVoltageMean;
    float RMSVoltage;

    for (int i = 0; i < sampleCount; i++)
    {
        voltageSampleRead = analogRead(Vpin) - 512;
        voltageSamplSum = voltageSamplSum + sq(voltageSampleRead);
    }

    RMSVoltageMean = sqrt(voltageSamplSum);
    RMSVoltage = ((RMSVoltageMean / 1024) * readVcc());
    return RMSVoltage;
}

/**
 * @brief Read the Reference Voltage
 * 
 * @return uint16_t 
 */
uint16_t VoltageSensor::readVcc()
{
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny167__) || defined(__AVR_ATtiny87__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
#else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif

    delay(2);            // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Start conversion
    while (bit_is_set(ADCSRA, ADSC))
        ; // measuring

    uint8_t low = ADCL;  // must read ADCL first - it then locks ADCH
    uint8_t high = ADCH; // unlocks both

    long result = (high << 8) | low;

    result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000

    return result - 0; // hard-coded calibration
}