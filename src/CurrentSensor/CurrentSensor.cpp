/******************************************************************
*********                       Includes                  *********
******************************************************************/
#include "CurrentSensor.h"

/**
 * CurrentSensor::CurrentSensor 
 * 
 * @param  {uint8_t} _Apin : CurrentSensor sensor Pin
 */
CurrentSensor::CurrentSensor(uint8_t _Apin)
{
    Apin = _Apin;
}

/**
 * CurrentSensor 
 * 
 * @param  {uint16_t} _sampleCount : Sample count 
 * @param  {float} _mVperAmpValue  : mV per Amp Value
 */
void CurrentSensor::init(uint16_t _sampleCount, float _mVperAmpValue)
{
    sampleCount = _sampleCount;
    mVperAmpValue = _mVperAmpValue;
}

/**
 * CurrentSensor 
 * 
 * @return {float}  : RMS Current Value
 */
float CurrentSensor::getSensor()
{
    float currentSampleRead;
    float currentSamplSum = 0;
    float RMSCurrentMean;
    float RMSCurrent;

    for (int i = 0; i < sampleCount; i++)
    {
        currentSampleRead = analogRead(Apin) - 512;
        currentSamplSum = currentSamplSum + sq(currentSampleRead);
    }

    RMSCurrentMean = sqrt(currentSamplSum);
    RMSCurrent = (((RMSCurrentMean / 1024) * readVcc()) / mVperAmpValue);
    return RMSCurrent;
}

/**
 * @brief Read the Reference Voltage
 * 
 * @return uint16_t 
 */
uint16_t CurrentSensor::readVcc()
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