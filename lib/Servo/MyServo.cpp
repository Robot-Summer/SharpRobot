#include <MyServo.h>

#include <Arduino.h>

MyServo::MyServo(PinName pin, int minAngle, int maxAngle, int initialAngle) : 
                    servoPin(pin), 
                    MIN_ANGLE(minAngle), 
                    MAX_ANGLE(maxAngle), 
                    INITIAL_ANGLE(initialAngle) {
                        
    pinMode(servoPin, OUTPUT);
}

void MyServo::write(int angle) {
    angle = limitAngle(angle);
    pwm_start(servoPin, 50, angle * 11, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);

}

int MyServo::limitAngle(int angle) {
    if (angle > MAX_ANGLE){
        return MAX_ANGLE;
    }

    if (angle < MIN_ANGLE){
        return MIN_ANGLE;
    }

    return angle;
}

