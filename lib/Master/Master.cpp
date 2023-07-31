#include <Arduino.h>

#include <IR.h>
#include <PID.h>
#include <Motor.h>
#include <Constants.h>
#include <Gyroscope.h>

#include <Master.h>

//namespace Master {

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

            case MasterState::DRV_TAPE:  
                tapeFollow.usePID();
                break;

            case MasterState::DRV_IR:
                //TODO: add the code for when ir is sampling

                float waveform[IRNS::NUM_READINGS];
                ir.waveformSample(waveform);
                ir.maxCorrelationOneK(waveform);

                advanceState();
                break;

            case MasterState::SHRP_TURN:
                //TODO: add the code for when ir is sampling

                advanceState();
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

            return;
        }
        stopped = true;
    }



//}