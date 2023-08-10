#include <Arduino.h>
#include <Wire.h>

#include <Constants.h>
#include <IR.h>
#include <Helper.h>
#include <Master.h>
#include <PID.h>

HardwareSerial Serial3(PB11, PB10);

#include <Adafruit_SSD1306.h>
 
Master state;

void setup() {
    // Serial3.begin(9600);
    
    state.setState(MasterState::DRV_TAPE);

    pwm_start(MotorNS::RIGHT_MOTOR_FWD, MotorNS::MOTOR_FREQ, MotorNS::MAX_SPEED + 50, RESOLUTION_8B_COMPARE_FORMAT);
    pwm_start(MotorNS::LEFT_MOTOR_BWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
    pwm_start(MotorNS::LEFT_MOTOR_FWD, MotorNS::MOTOR_FREQ, MotorNS::MAX_SPEED + 50, RESOLUTION_8B_COMPARE_FORMAT);
    pwm_start(MotorNS::RIGHT_MOTOR_BWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
    delay(200);

    pwm_start(MotorNS::RIGHT_MOTOR_FWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
    pwm_start(MotorNS::LEFT_MOTOR_FWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
    servoW
    delay(5000);

    pinMode(PC13, OUTPUT);
    digitalWrite(PC13, HIGH);

}



void loop() {
    state.poll();
}