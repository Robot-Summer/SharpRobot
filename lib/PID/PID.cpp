#include <Arduino.h>
#include <Constants.h>
// #include <Motor.h>

#include <PID.h>

//TODO: implement the motor class
PID::PID() : 
    servoAngle(PIDNS::INITIAL_ANGLE),
    lastState(0),
    timeInCurrent(0),
    timeInPrev(0),
    integral(0.0F),
    lastError(0) 
    {

    pinMode(PIDNS::SERVO_PIN, OUTPUT);

    pinMode(MotorNS::LEFT_MOTOR_BWD, OUTPUT);
    pinMode(MotorNS::LEFT_MOTOR_FWD, OUTPUT);

    pinMode(MotorNS::RIGHT_MOTOR_FWD, OUTPUT);
    pinMode(MotorNS::RIGHT_MOTOR_BWD, OUTPUT);


}


int PID::getCurrentState(int leftSensor2, int leftSensor1, int rightSensor1, int rightSensor2, int lastState, int lastError) {
    int state = 0;
  
    if (rightSensor1 == 1 && leftSensor1 == 1) {
        state = 0;
    } 
    else if (rightSensor1 == 1) {
        if (rightSensor2 == 0) {
            state = 1;
            // digitalWrite(PC13, HIGH);
        } 
        else if (rightSensor2 == 1) {
            state = 2;
            // digitalWrite(PC13, HIGH);
        }
    }
    else if (leftSensor1 == 1) {
        if (leftSensor2 == 0) {
            state = -1;
            // digitalWrite(PC13, LOW);
        }
        else if (leftSensor2 == 1) {
            state = -2;
            // digitalWrite(PC13, LOW);
        }
    }
    else if (rightSensor2 == 1) {
        state = 3;
        // digitalWrite(PC13, HIGH);
    }
    else if (leftSensor2 == 1) {
        state = -3;
        // digitalWrite(PC13, LOW);
    }
    else {
        //state = lastState;
        if (lastState > 0) {
            state = 4;
            // digitalWrite(PC13, HIGH);
        } else if (lastState < 0) {
            state = -4;
            // digitalWrite(PC13, LOW);
        } else if (lastError > 0) {
            state = -4;
            // digitalWrite(PC13, LOW);
        } else if (lastError < 0) {
            state = 4;
            // digitalWrite(PC13, HIGH);
        }
    
    }
    return state;
}


int PID::limitAngle(int angle) {
    if (angle > PIDNS::MAX_ANGLE){
        return PIDNS::MAX_ANGLE;
    }

    if (angle < PIDNS::MIN_ANGLE){
        return PIDNS::MIN_ANGLE;
    }
    return angle;
}

int PID::getDigital(int value, int previousDigital) {
    if (previousDigital == 1) {
        if (value < 150) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        if (value > 300) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

void PID::writeServoAngle(int angle) {
    int pwmSignal = angle * 11;
    pwm_start(PIDNS::SERVO_PIN, 50, pwmSignal, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}

int count = 0;
int l1pd = 0;
int r1pd = 0;   
int l2pd = 0;
int r2pd = 0;

void PID::usePID() {

    int l1 = analogRead(PIDNS::LEFT_SENSOR_ONE);
    int r1 = analogRead(PIDNS::RIGHT_SENSOR_ONE);
    int l2 = analogRead(PIDNS::LEFT_SENSOR_TWO);
    int r2 = analogRead(PIDNS::RIGHT_SENSOR_TWO);


    int l1d = getDigital(analogRead(PIDNS::LEFT_SENSOR_ONE), l1pd);
    int r1d = getDigital(analogRead(PIDNS::RIGHT_SENSOR_ONE), r1pd);
    int l2d = getDigital(analogRead(PIDNS::LEFT_SENSOR_TWO), l2pd);
    int r2d = getDigital(analogRead(PIDNS::RIGHT_SENSOR_TWO), r2pd);

    // Get Line position (positive => drifiting right ; negative => drifiting left)
    int currentState = getCurrentState(l2d, l1d, r1d, r2d, lastState, lastError);

    if (currentState != lastState) {
        timeInPrev = timeInCurrent;  
        timeInCurrent = 0;
        lastError = lastState;
        digitalWrite(PC13, !digitalRead(PC13));
    }   
    timeInCurrent++;

    // Compute derivative of error 
    float derivative = (float) (currentState - lastError) / (timeInCurrent + timeInPrev);

    // Compute sum of errors
    if (currentState == 0) {
        integral = 0;
    }
    else {
        integral += currentState;
    }
 
    // Compute Servo adjustment, positive means robot drifiting to the left, negative means robot drifiting to the right
    float adjustment = PIDNS::KP * currentState; // + PIDNS::KD * derivative + PIDNS::KI * integral; 

    servoAngle = PIDNS::INITIAL_ANGLE + adjustment;  
    servoAngle = limitAngle(servoAngle);
    writeServoAngle(servoAngle);
    
    lastState = currentState;

    // if (l1d == 1) {
    //     digitalWrite(PC13, LOW);
    // }
    // else {
    //     digitalWrite(PC13, HIGH);
    // }


    if (currentState == 4) {
        pwm_start(MotorNS::RIGHT_MOTOR_FWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::LEFT_MOTOR_BWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::LEFT_MOTOR_FWD, MotorNS::MOTOR_FREQ, MotorNS::MAX_SPEED + 30, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::RIGHT_MOTOR_BWD, MotorNS::MOTOR_FREQ, MotorNS::MAX_SPEED + 30, RESOLUTION_8B_COMPARE_FORMAT);
    }
    else if (currentState == -4 ) {
        pwm_start(MotorNS::LEFT_MOTOR_FWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::RIGHT_MOTOR_BWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::RIGHT_MOTOR_FWD, MotorNS::MOTOR_FREQ, MotorNS::MAX_SPEED + 30, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::LEFT_MOTOR_BWD, MotorNS::MOTOR_FREQ, MotorNS::MAX_SPEED + 30, RESOLUTION_8B_COMPARE_FORMAT);
    }
    else {
        pwm_start(MotorNS::LEFT_MOTOR_BWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::RIGHT_MOTOR_BWD, MotorNS::MOTOR_FREQ, 0, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::RIGHT_MOTOR_FWD, MotorNS::MOTOR_FREQ, MotorNS::MAX_SPEED + adjustment/2, RESOLUTION_8B_COMPARE_FORMAT);
        pwm_start(MotorNS::LEFT_MOTOR_FWD, MotorNS::MOTOR_FREQ, MotorNS::MAX_SPEED + adjustment/2, RESOLUTION_8B_COMPARE_FORMAT);
    }   
    
    count++;

    l1pd = l1d;
    r1pd = r1d;
    l2pd = l2d;
    r2pd = r2d; 

}