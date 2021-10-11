#include "Board.h"
#include "src/CurrentSensor/CurrentSensor.h"
#include "src/VoltageSensor/VoltageSensor.h"
#include "src/Relay/ActiveDriver.h"

CurrentSensor chargerCurrent(CS_CURRENT_SENSOR_PIN);
CurrentSensor loadCurrent(CS_VOLTAGE_SENSOR_PIN);

VoltageSensor chargerVoltage(LS_CURRENT_SENSOR_PIN);
VoltageSensor batteryVoltage(LS_VOLTAGE_SENSOR_PIN);

ActiveDriver chargingSideRelay(CS_RELAY_PIN);
ActiveDriver loadSideRelay(LS_RELAY_PIN);


void setup()
{
    chargerCurrent.init(100,185);
    loadCurrent.init(100,185);
    chargerVoltage.init(100);
    batteryVoltage.init(100);
    chargingSideRelay.init();
    loadSideRelay,init();

}

void loop()
{
    if(Serial.available() > 0)
    {
        char reading = Serial.read();
        if(reading == '1')
        {
            chargingSideRelay.activate();
        }
        if(reading == '2')
        {
            chargingSideRelay.deactivate();
        }
        if(reading == '3')
        {
            loadSideRelay.activate();
        }
        if(reading == '4')
        {
            loadSideRelay.deactivate();
        }
        
    }

    Serial.print("Charging Current : ");
    Serial.print(chargerCurrent.getSensor());
    Serial.print(" A ");
    Serial.print("Charging Voltage : ");
    Serial.print(chargerVoltage.getSensor());
    Serial.println(" mV ");
    Serial.print("Load Current : ");
    Serial.print(loadCurrent.getSensor());
    Serial.print(" A ");
    Serial.print("Load Voltage : ");
    Serial.print(batteryVoltage.getSensor());
    Serial.println(" mV ");

}