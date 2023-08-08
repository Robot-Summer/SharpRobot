#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>

Motor::Motor(PinName forwardPin, PinName backwardPin) : forwardPin(forwardPin), backwardPin(backwardPin) {
    pinMode(forwardPin, OUTPUT);
    pinMode(backwardPin, OUTPUT);
}

void Motor::stop() {
    pwm_start(forwardPin, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
    pwm_start(backwardPin, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
}

void Motor::speed(int speed) {
    //TODO: if we change the resolution of the pwm function the limits must change too
    // Limits
    if (speed > 255) {
        speed = 255;
    } if (speed < -255) {
        speed = -255;
    }
    
    // Write the speeds to the motors
    if (speed > 0) {
        pwm_start(backwardPin, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(forwardPin, MotorNS::MOTOR_FREQ, speed, RESOLUTION_8B_COMPARE_FORMAT);
    }  else if (speed == 0){
        stop();
    } else{
        pwm_start(forwardPin, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(backwardPin, MotorNS::MOTOR_FREQ, -1*speed, RESOLUTION_8B_COMPARE_FORMAT);
    }

}
