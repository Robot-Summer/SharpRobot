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

int PID::getTotalState(int leftSensor2, int leftSensor1, int rightSensor1, int rightSensor2, int lastState, int lastError) {
    int state = 0;
    digitalWrite(PC13, HIGH);
    if (rightSensor1 == 1 && leftSensor1 == 1) {
        state = 0;
    } else if (rightSensor1 == 1) {
        if (rightSensor2 == 0) {
            state = 1;
        } else if (rightSensor2 == 1) {
            // state = 4;
            state = 2;
        }
    } else if (leftSensor1 == 1) {
        if (leftSensor2 == 0) {
            state = -1;
        } else if (leftSensor2 == 1) {
            // state = -4;
            state = -2;
        }
    } else if (rightSensor2 == 1) {
        // state = 6;
        state = 3;
    } else if (leftSensor2 == 1) {
        // state = -6;
        state = -3;
    } else {
        //state = lastState;
        if (lastState > 0) {
            // state = 8;
            state = 4;
            // digitalWrite(PC13, LOW);
        } else if (lastState < 0) {
            // state = -8;
            state = -4;
            // digitalWrite(PC13, LOW);
        } 
        else if (lastError > 0) {
            state = -4;
            digitalWrite(PC13, LOW);
        }
        else if (lastError < 0) {
            state = 4;
            digitalWrite(PC13, LOW);
        }
        else {
            state = 0;
        }
    }

    return state;
}

void PID::usePID(int speed) {

    // Get Line position (positive => drifiting right ; negative => drifiting left)
    int currentState = getTotalState(reflectors -> getReflectorValue(0), reflectors -> getReflectorValue(1), 
                                        reflectors -> getReflectorValue(2), reflectors -> getReflectorValue(3), lastState, lastError);

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

    float scalingFactor = 1;

    if (currentState == 4) {
        leftMotor -> speed((speed + 45));
        rightMotor -> speed(-(speed + 45));
    }
    else if (currentState == -4 ) {
        leftMotor -> speed(-(speed + 45));
        rightMotor -> speed((speed + 45)); 
    }
    else {
        leftMotor -> speed(speed + scalingFactor * adjustment/2);
        rightMotor -> speed(speed - scalingFactor * adjustment/2);
    }
}