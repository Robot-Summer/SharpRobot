#include <Arduino.h>

#include <IR.h>
#include <PID.h>
#include <Motor.h>
#include <Constants.h>
#include <Gyroscope.h>

#include <Master.h>

MasterState Master::poll() {
    
    switch(currentState){

        case MasterState::IDLE:
            //TODO: write code for the switch (maybe debouncing needed)
            if (true) {//change the part inside the if statment
                advanceState();
            } else {
                stop();
            }
            
            break;

        

        case MasterState::DRV_TAPE_NORM: 

            tapeFollow.usePID(MotorNS::MAX_SPEED);

            // reflectors -> printValues();

            // //i need to check if the prePreMarker is false and then if the preMarker is true and then if the current marker is true
            // if (!preMarker) { //checks if robot was previously previously on a marker
            //     if (reflectors -> bridgeMarker()) { //checks if the robot is currently on a marker      
            //         digitalWrite(PC13, !digitalRead(PC13));
            //         if (secondMarker == 3) { //checks if robot has crossed the bridge
            //             goToState(MasterState::DRV_TAPE_DOWN);
            //             secondMarker = 0;
            //             rampTimer = millis();
            //         } else {
            //             secondMarker++;
            //         }
            //     }
            // }

            // preMarker = reflectors -> bridgeMarker();
            break;

        case MasterState::DRV_TAPE_DOWN:
            
            tapeFollow.usePID(MotorNS::DOWN_RAMP_SPEED);

            if (millis() - rampTimer >= TimerNS::RAMP_TIMER) {
                goToState(MasterState::DRV_TAPE_NORM);
            }

            break;

        case MasterState::SHRP_TURN:
            goToState(MasterState::DRV_TAPE_NORM);
            break;

        case MasterState::OTHR_RBT:
            //TODO: add the code for when ir is sampling
            break;

        case MasterState::DRP_BAN:
            //TODO: add the code for when ir is sampling
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