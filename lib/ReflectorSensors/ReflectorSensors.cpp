#include <Arduino.h>
#include <ReflectorSensors.h>
#include <Constants.h>

int count = 0;
Reflectors::Reflectors() : 
        l2(0), l1(0), r1(0), r2(0), 
        pl2(0), pl1(0), pr1(0), pr2(0) {}

int Reflectors::getDigital(int value, int* previousState) {
    if (*previousState == 0) {
        if (value > ReflectorsNS::DIGITAL_THRESHOLD_HIGH) {
            *previousState = 1;
            return 1;
        }
        else {
            *previousState = 0;
            return 0;
        }
    } else if (*previousState == 1) {
        if (value < ReflectorsNS::DIGITAL_THRESHOLD_LOW) {
            *previousState = 1;
            return 1;
        }
        else {
            *previousState = 0;
            return 0;
        }
    } else {
        return -1;
    }
}

int Reflectors::getReflectorValue(int sensor) {
    if (sensor == 0) {
        l2 = getDigital(analogRead(ReflectorsNS::LEFT_SENSOR_TWO), &pl2);
        return l2;

    } else if (sensor == 1) {
        l1 = getDigital(analogRead(ReflectorsNS::LEFT_SENSOR_ONE), &pl1);
        return l1;

    } else if (sensor == 2) {
        r1 = getDigital(analogRead(ReflectorsNS::RIGHT_SENSOR_ONE), &pr1);
        return r1;

    } else if (sensor == 3) {
        r2 = getDigital(analogRead(ReflectorsNS::RIGHT_SENSOR_TWO), &pr2);
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
    Serial3.print(count);
    Serial3.print("- ");
    Serial3.print(analogRead(ReflectorsNS::LEFT_SENSOR_TWO));
    Serial3.print(",   ");
    Serial3.print(analogRead(ReflectorsNS::LEFT_SENSOR_ONE));
    Serial3.print(",   ");
    Serial3.print(analogRead(ReflectorsNS::RIGHT_SENSOR_ONE));
    Serial3.print(",   ");
    Serial3.print(analogRead(ReflectorsNS::RIGHT_SENSOR_TWO));
    Serial3.println("   ");
    count++;
}
