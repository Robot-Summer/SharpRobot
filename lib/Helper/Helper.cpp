#include <Arduino.h>
#include <Constants.h>
#include <Helper.h>


int Helper::getAverageAnalog(int analogPin, int numReadings){
    int sensorValue = 0;

    for (int i = 0; i < numReadings; i++) {
        sensorValue += analogRead(analogPin);
    }

    return sensorValue / numReadings;
}