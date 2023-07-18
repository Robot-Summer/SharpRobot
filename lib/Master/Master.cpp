#include <Arduino.h>

#include <IR.h>
#include <PID.h>
#include <Motors.h>
#include <Constants.h>
#include <Gyroscope.h>

#include <Master.h>

namespace Master {
    MasterState Master::poll() {
        
        switch(currentState){

            case MasterState::INACTIVE://might not need it depending if we have a switch or not
            //TODO: add the code for when it is inactive

            advanceState();
            break;

            case MasterState::IR_SAMPLING:
            //TODO: add the code for when ir is sampling

            advanceState();
            break;

            case MasterState::IR_WAITING:
            //TODO: add the code for when it is inactive

            advanceState();
            break;

            case MasterState::IR_PROCCESSING:
            //TODO: add the code for when ir is proccessing

            advanceState();
            break;

            case MasterState::DONE:
            //TODO: add the code for when it is done
            
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
        if (stopped){ 
            return;
        }
        stopped = true;
    }



}