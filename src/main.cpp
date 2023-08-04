#include <Arduino.h>

#include <Constants.h>
#include <Helper.h>
#include <Master.h>
#include <PID.h>
#include <ReflectorSensors.h>

HardwareSerial Serial3(PB11, PB10);

Reflectors myReflectors;
Motor leftMotor(MotorNS::LEFT_MOTOR_FWD, MotorNS::LEFT_MOTOR_BWD);
Motor rightMotor(MotorNS::RIGHT_MOTOR_FWD, MotorNS::RIGHT_MOTOR_BWD);

Master state(&myReflectors, &leftMotor, &rightMotor);

void setup() {
    Serial3.begin(9600);
    state.setState(MasterState::DRV_TAPE_NORM);
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);
}

void loop() {
    state.poll();
}