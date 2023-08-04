#include <Arduino.h>
#include <Wire.h>

#include <Constants.h>
#include <IR.h>
#include <Helper.h>
#include <Master.h>
#include <PID.h>
#include <ReflectorSensors.h>

HardwareSerial Serial3(PB11, PB10);

Reflectors myReflectors;
Master state(&myReflectors);

void setup() {
    Serial3.begin(9600);
    state.setState(MasterState::DRV_TAPE_NORM);
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);
}

void loop() {
    state.poll();
}