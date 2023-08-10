#include <Arduino.h>

#include <IR.h>
#include <PID.h>
#include <Motor.h>
#include <Constants.h>
#include <Gyroscope.h>
#include <TiltSensor.h>

#include <Master.h>

MasterState Master::poll() {
    
    switch(currentState){
        case MasterState::START_LEFT:
            steeringServo -> write(ServoNS::INITIAL_ANGLE);
            leftMotor -> speed(MotorNS::MAX_SPEED);
            rightMotor -> speed(MotorNS::MAX_SPEED);
            delay(500);
            leftMotor -> stop();
            rightMotor -> stop();
            steeringServo -> write(60);
            leftMotor -> speed(-MotorNS::MAX_SPEED);
            rightMotor -> speed(MotorNS::MAX_SPEED);
            delay(525);
            leftMotor -> stop();
            rightMotor -> stop();
            steeringServo -> write(ServoNS::INITIAL_ANGLE);
            leftMotor -> speed(MotorNS::MAX_SPEED);
            rightMotor -> speed(MotorNS::MAX_SPEED);
            delay(500);

            goToState(MasterState::DRV_TAPE_NORM);
            break;

        case MasterState::START_RIGHT:

            steeringServo -> write(ServoNS::INITIAL_ANGLE);
            leftMotor -> speed(MotorNS::MAX_SPEED);
            rightMotor -> speed(MotorNS::MAX_SPEED);
            delay(500);


            goToState(MasterState::DRV_TAPE_NORM);
            break;        

        case MasterState::DRV_TAPE_NORM:

            tapeFollow.usePID(MotorNS::MAX_SPEED);

            break;

        case MasterState::DRV_TAPE_DOWN:
            
            tapeFollow.usePID(MotorNS::DOWN_RAMP_SPEED);
            

            if (!tiltSensor.readTiltSensor()){
                tiltCount++;
                if (true){
                    goToState(MasterState::DRV_TAPE_DOWN);
                    digitalWrite(PC13, LOW);
                }
            } else {
                tiltCount = 0;
            }

            break;

        case MasterState::DONE:                
            stop();
            break;

    }

    return currentState;
}

bool Master::advanceState() {
    if (currentState == MasterState::DONE){
        return false;
    }
    currentState = static_cast<MasterState>(static_cast<int>(currentState) + 1);
    return true;
}

bool Master::goToState(MasterState futureState) {
    if (currentState == MasterState::DONE){
        return false;
    }
    currentState = futureState;
    return true;
}

void Master::stop() {
    if (stopped){ //add the code to stop the motors. 
        leftMotor -> stop();
        rightMotor -> stop();
        return;
    }
    stopped = true;
}