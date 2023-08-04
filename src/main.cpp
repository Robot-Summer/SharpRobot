#include <Arduino.h>
#include <Wire.h>

#include <Constants.h>
#include <Helper.h>
#include <Master.h>
#include <PID.h>
#include <ReflectorSensors.h>
#include <Motor.h>
#include <MyServo.h>

HardwareSerial Serial3(PB11, PB10);

Reflectors myReflectors;

Motor leftMotor(MotorNS::LEFT_MOTOR_FWD, MotorNS::LEFT_MOTOR_BWD);
Motor rightMotor(MotorNS::RIGHT_MOTOR_FWD, MotorNS::RIGHT_MOTOR_BWD);

MyServo steeringServo(ServoNS::SERVO_PIN, ServoNS::MIN_ANGLE, ServoNS::MAX_ANGLE, ServoNS::INITIAL_ANGLE);


Master state(&myReflectors, &leftMotor, &rightMotor, &steeringServo);

void setup() {
    Serial3.begin(9600);
    state.setState(MasterState::DRV_TAPE_NORM);
    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);
}

void loop() {
    state.poll();
}