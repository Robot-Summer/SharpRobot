#include <Arduino.h>
#include <Constants.h>
#include <TiltSensor.h>

TiltSensor::TiltSensor(){

}

bool TiltSensor::readTiltSensor(){
    return digitalRead(TiltNS::TILT_SENSOR_PIN);
}



