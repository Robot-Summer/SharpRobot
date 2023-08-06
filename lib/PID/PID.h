#ifndef PID_h
#define PID_h

#include <Arduino.h>
#include <Constants.h>


#include <ReflectorSensors.h>
#include <MyServo.h>

class PID {
    public:

        /**
         * PID constructor
         * 
         * @param sensors a pointer to the sensors that will be used.
         * @param leftMotor a pointer to the left motor that will be used.
         * @param rightMotor a pointer to the right motor that will be used.
        */
        PID(Reflectors* sensors, Motor* leftMotor, Motor* rightMotor, MyServo* steeringServo);

        /**
         * usePID makes the servos turn
         * 
         * @param speed the speed at which the motors will run. (0 to 255)
        */
        void usePID(int speed);

        // class inits and other variables.

        int servoAngle;
        int lastState;
        int timeInCurrent;
        int timeInPrev;
        float integral;
        int lastError;
        int bridgeMarker;
        bool previousMarker;
        int currentSpeed;

        Reflectors* reflectors;
        Motor* leftMotor;
        Motor* rightMotor;
        MyServo* steeringServo;
        
};