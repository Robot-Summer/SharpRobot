#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>
#include <ReflectorSensors.h>


#include <PID.h>

//TODO: implement the motor class
PID::PID(Reflectors* sensors, Motor* leftMotor, Motor* rightMotor) : 
    servoAngle(PIDNS::INITIAL_ANGLE),
    lastState(0),
    timeInCurrent(0),
    timeInPrev(0),
    integral(0.0F),
    lastError(0),
    reflectors(sensors),
    leftMotor(leftMotor),
    rightMotor(rightMotor)
    {
    
    //servo pin declarations
    pinMode(PIDNS::SERVO_PIN, OUTPUT);

    //motor pin declarations
    pinMode(MotorNS::LEFT_MOTOR_BWD, OUTPUT);
    pinMode(MotorNS::LEFT_MOTOR_FWD, OUTPUT);
    pinMode(MotorNS::RIGHT_MOTOR_FWD, OUTPUT);
    pinMode(MotorNS::RIGHT_MOTOR_BWD, OUTPUT);

}

int PID::getTotalState(int leftSensor2, int leftSensor1, int rightSensor1, int rightSensor2, int lastState) {
    int state = 0;
  
    if (rightSensor1 == 1 && leftSensor1 == 1) {
        state = 0;
    } else if (rightSensor1 == 1) {
        if (rightSensor2 == 0) {
            state = 1;
        } else if (rightSensor2 == 1) {
            state = 2;
        }
    } else if (leftSensor1 == 1) {
        if (leftSensor2 == 0) {
            state = -1;
        } else if (leftSensor2 == 1) {
            state = -2;
        }
    } else if (rightSensor2 == 1) {
        state = 3;
    } else if (leftSensor2 == 1) {
        state = -3;
    } else {
        //state = lastState;
        if (lastState > 0) {
            state = 4;
        } else if (lastState < 0) {
            state = -4;
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

void PID::writeServoAngle(int angle) {
    int pwmSignal = angle * 11;
    pwm_start(PIDNS::SERVO_PIN, 50, pwmSignal, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}

void PID::usePID(int speed) {

    // Get Line position (positive => drifiting right ; negative => drifiting left)
    int currentState = getTotalState(reflectors -> getReflectorValue(0), reflectors -> getReflectorValue(1), 
                                        reflectors -> getReflectorValue(2), reflectors -> getReflectorValue(3), lastState);

    // reflectors.printValues();

    if (currentState != lastState) {
        timeInPrev = timeInCurrent;  
        timeInCurrent = 0;
        lastError = lastState;
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
    float adjustment = PIDNS::KP * currentState + PIDNS::KD * derivative + PIDNS::KI * integral; 

    servoAngle = PIDNS::INITIAL_ANGLE + adjustment;  
    servoAngle = limitAngle(servoAngle);
    writeServoAngle(servoAngle);

    lastState = currentState;

    if (currentState == 4) {
        leftMotor -> speed((speed + 20));
        rightMotor -> speed(-(speed + 20));
    }
    else if (currentState == -4 ) {
        leftMotor -> speed(-(speed + 20));
        rightMotor -> speed((speed + 20)); 
    }
    else {
        leftMotor -> speed(speed + adjustment);
        rightMotor -> speed(speed - adjustment);
    }
}