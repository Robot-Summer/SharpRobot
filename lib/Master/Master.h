#ifndef Master_h
#define Master_h

#include <Arduino.h>
#include <IR.h>
#include <PID.h>
#include <Motors.h>
#include <Constants.h>
#include <Gyroscope.h>

namespace Master {

    //States
    enum class MasterState { //TODO: change as needed
        INACTIVE,
        IR_SAMPLING,
        IR_WAITING,
        IR_PROCCESSING,
        DONE
    };

    class Master { 
        public:

            /**
             * returns current state of the robot.
            */
            MasterState poll();

        private: 

            /**
             * advance State advances the master state
             * 
             * @return true if the function was succesful in advancing state, false otherwise
            */
            bool advanceState();

            /**
             * goes to a specific state
             * 
             * @param fututreState is the state which the robot will go to next
             * 
             * @return true if the function was succesful in advancing state, false otherwise
            */
            bool goToState(MasterState futureState);

            /**
             * stops the robot 
            */   
            void stop();

            //TODO add all other variables and class instances as this master class will be called at the beggining of the run.
        
            MasterState currentState;
            bool stopped;
            IR ir;

    };

}//master namespace


#endif