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
            goToState(MasterState::DRV_TAPE_NORM);
            break;

        case MasterState::START_RIGHT:
            goToState(MasterState::DRV_TAPE_NORM);
            break;        

        case MasterState::DRV_TAPE_NORM: 

            tapeFollow.usePID(MotorNS::MAX_SPEED);

            // if (tiltSensor.readTiltSensor()){
            //     goToState(MasterState::DRV_TAPE_DOWN);
            //     digitalWrite(PC13, HIGH);
            // }

            if (reflectors -> bridgeMarker()) {
                goToState(MasterState::DRV_TAPE_DOWN);
                rampTimer = millis();
                digitalWrite(PC13, LOW);
            }

            break;

        case MasterState::DRV_TAPE_DOWN:
            
            tapeFollow.usePID(MotorNS::DOWN_RAMP_SPEED);

            // if (!tiltSensor.readTiltSensor()){
            //     goToState(MasterState::DRV_TAPE_NORM);
            //     digitalWrite(PC13, LOW);
            // }

            if (millis() - rampTimer >= TimerNS::RAMP_TIMER) {
                goToState(MasterState::DRV_TAPE_NORM);
                digitalWrite(PC13, HIGH);
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