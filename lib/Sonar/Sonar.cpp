#include <Sonar.h>

#include <Arduino.h>

Sonar::Sonar(int sonarEcho, int sonarTrig) : sonarEcho(sonarEcho), sonarTrig(sonarTrig) {
    pinMode(sonarEcho, INPUT);
    pinMode(sonarTrig, OUTPUT);
}

int Sonar::getDistance() {
    int distance;

    digitalWrite(sonarTrig, LOW);    
    digitalWrite(sonarTrig, HIGH);   
    digitalWrite(sonarEcho, LOW);  

    distance = (pulseIn(sonarEcho, HIGH) / 2) / 29.1;

    return distance;

}