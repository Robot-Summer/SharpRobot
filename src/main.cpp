#include <Arduino.h>
#include <Wire.h>

#include <Constants.h>
#include <Helper.h>
#include <Master.h>
#include <PID.h>
#include <ReflectorSensors.h>
#include <Motor.h>
#include <MyServo.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET  -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

    // steeringServo.write(ServoNS::INITIAL_ANGLE);
    // pwm_start(MotorNS::LEFT_MOTOR_FWD, MotorNS::MOTOR_FREQ, 150, RESOLUTION_8B_COMPARE_FORMAT);
    // pwm_start(MotorNS::LEFT_MOTOR_FWD, MotorNS::MOTOR_FREQ, 150, RESOLUTION_8B_COMPARE_FORMAT);
}

void loop() {
    // steeringServo.write(ServoNS::INITIAL_ANGLE+2);


    state.poll();

    // steeringServo.write(ServoNS::INITIAL_ANGLE);
    // delay(1000);
    // steeringServo.write(ServoNS::MAX_ANGLE);
    // delay(1000);
    // steeringServo.write(ServoNS::MIN_ANGLE);
    // delay(3000);
}