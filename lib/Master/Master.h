#ifndef Master_h
#define Master_h

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>


#include <PID.h>
#include <Motor.h>
#include <Constants.h>

//States
enum class MasterState { //TODO: change as needed
    IDLE,
    DRV_IR,
    DRV_TAPE_NORM,
    DRV_TAPE_DOWN,
    SHRP_TURN,
    OTHR_RBT,
    DRP_BAN,
    DONE
};

class Master { 
    public:
        
        /**
         * Master class constructor
         * 
         * @param refl a pointer to the reflectors that will be used.
         * @param leftMotor a pointer to the left motor that will be used.
         * @param rightMotor a pointer to the right motor that will be used.
        */
        Master(Reflectors* refl, Motor* leftMotor, Motor* rightMotor) : 
                preMarker(false), prePreMarker(false), 
                secondMarker(false), reflectors(refl), 
                tapeFollow(refl, leftMotor, rightMotor),
                leftMotor(leftMotor), rightMotor(rightMotor) {};

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
        
        Reflectors* reflectors;
        Motor* leftMotor;
        Motor* rightMotor;

        PID tapeFollow;

        unsigned long rampTimer;

        bool preMarker, prePreMarker, secondMarker;

        bool stopped;

};

#endif