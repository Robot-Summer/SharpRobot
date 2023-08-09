#ifndef Master_h
#define Master_h

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>


#include <IR.h>
#include <PID.h>
#include <Motor.h>
#include <Constants.h>
#include <ReflectorSensors.h>
#include <MyServo.h>
#include <Sonar.h>

//States
enum class MasterState { //TODO: change as needed
    IDLE,
    START,
    DRV_TAPE_NORM,
    DRV_TAPE_DOWN,
    SHRP_TURN,
    AFTER_ARCH,
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
         * @param steeringServo a pointer to the steering servo that will be used.
        */
        Master(Reflectors* refl, Motor* leftMotor, Motor* rightMotor, MyServo* steeringServo) : 
                bridgeMarker(false), preMarker(false), 
                secondMarker(0), reflectors(refl), 
                tapeFollow(refl, leftMotor, rightMotor, steeringServo),
                leftMotor(leftMotor), rightMotor(rightMotor),
                steeringServo(steeringServo),
                sonar(SonarNS::ECHO, SonarNS::TRIG),
                sonarTimer(0) {};

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
        MyServo* steeringServo;

        Sonar sonar;


        IR ir;
        PID tapeFollow;

        unsigned long rampTimer, bridgeTimer, shrpTimer, sonarTimer, time;

        bool bridgeMarker, preMarker;
        int secondMarker;

        bool stopped;

};

#endif