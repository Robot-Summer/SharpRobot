#ifndef Master_h
#define Master_h

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>


#include <IR.h>
#include <PID.h>
#include <Motor.h>
#include <Constants.h>
#include <Gyroscope.h>

//namespace Master {

    //States
    enum class MasterState { //TODO: change as needed
        IDLE,
        DRV_IR,
        DRV_TAPE,
        SHRP_TURN,
        OTHR_RBT,
        DRP_BAN,
        DONE
    };

    class Master { 
        public:

            /**
             * masterstate pole
             * 
             * @return the current state of the robot.
            */
            MasterState poll();

            /**
             * Set the state. ONLY FOR DEBUGGING. Do not use on competition day
            */
            void setState(MasterState state) { this -> currentState = state; }

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
            PID tapeFollow;

    };

//}//master namespace

#endif