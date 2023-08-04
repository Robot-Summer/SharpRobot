#include <Arduino.h>
#include <ReflectorSensors.h>
#include <Constants.h>


Reflectors::Reflectors() : l2(0), l1(0), r1(0), r2(0) {}

int Reflectors::getDigital(int value) {
    if (value > ReflectorsNS::DIGITAL_THRESHOLD) {
        return 1;
    }
    else {
        return 0;
    }
}

int Reflectors::getReflectorValue(int sensor) {
    if (sensor == 0) {
        l2 = getDigital(analogRead(ReflectorsNS::LEFT_SENSOR_TWO));
        return l2;

    } else if (sensor == 1) {
        l1 = getDigital(analogRead(ReflectorsNS::LEFT_SENSOR_ONE));
        return l1;

    } else if (sensor == 2) {
        r1 = getDigital(analogRead(ReflectorsNS::RIGHT_SENSOR_ONE));
        return r1;

    } else if (sensor == 3) {
        r2 = getDigital(analogRead(ReflectorsNS::RIGHT_SENSOR_TWO));
        return r2;

    } else {
        return -1;

    }
}

bool Reflectors::bridgeMarker() {
    if (l2 == 1 && l1 == 1 && r1 == 1 && r2 == 1) {       
        return true;
    } else {
        return false;
    }
}

void Reflectors::printValues() {
    Serial3.print(analogRead(ReflectorsNS::LEFT_SENSOR_TWO));
    Serial3.print(",   ");
    Serial3.print(analogRead(ReflectorsNS::LEFT_SENSOR_ONE));
    Serial3.print(",   ");
    Serial3.print(analogRead(ReflectorsNS::RIGHT_SENSOR_ONE));
    Serial3.print(",   ");
    Serial3.print(analogRead(ReflectorsNS::RIGHT_SENSOR_TWO));
    Serial3.println("   ");

}
