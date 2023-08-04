#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>
#include <ReflectorSensors.h>


#include <PID.h>

//TODO: implement the motor class
PID::PID(Reflectors* sensors, Motor* leftMotor, Motor* rightMotor, MyServo* steeringServo) : 
    servoAngle(ServoNS::INITIAL_ANGLE),
    lastState(0),
    timeInCurrent(0),
    timeInPrev(0),
    integral(0.0F),
    lastError(0),
    reflectors(sensors),
    leftMotor(leftMotor),
    rightMotor(rightMotor),
    steeringServo(steeringServo) {}

int PID::getTotalState(int leftSensor2, int leftSensor1, int rightSensor1, int rightSensor2, int lastState) {
    int state = 0;
  
    if (rightSensor1 == 1 && leftSensor1 == 1) {
        state = 0;
    } else if (rightSensor1 == 1) {
        if (rightSensor2 == 0) {
            state = 1;
        } else if (rightSensor2 == 1) {
            state = 4;
        }
    } else if (leftSensor1 == 1) {
        if (leftSensor2 == 0) {
            state = -1;
        } else if (leftSensor2 == 1) {
            state = -4;
        }
    } else if (rightSensor2 == 1) {
        state = 6;
    } else if (leftSensor2 == 1) {
        state = -6;
    } else {
        //state = lastState;
        if (lastState > 0) {
            state = 8;
        } else if (lastState < 0) {
            state = -8;
        } 
    }

    return state;
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

    steeringServo -> write(ServoNS::INITIAL_ANGLE + adjustment);

    lastState = currentState;

    if (currentState == 8) {
        leftMotor -> speed((speed + 20));
        rightMotor -> speed(-(speed + 20));
    }
    else if (currentState == -8 ) {
        leftMotor -> speed(-(speed + 20));
        rightMotor -> speed((speed + 20)); 
    }
    else {
        leftMotor -> speed(speed + adjustment);
        rightMotor -> speed(speed - adjustment);
    }
}