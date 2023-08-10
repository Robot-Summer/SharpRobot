#ifndef PID_h
#define PID_h

#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>

class PID {
    public:

        /**
         * PID constructor
        */
        PID();

        /**
         * writes the angle of the servo
         * 
         * @param angle the angle we want the servo to turn. 
        */
        void writeServoAngle(int angle);

        /**
         * usePID makes the servos turn
         * 
        */
        void usePID();

    private: 

        /**
         * Calculates the current state of the control system. 
         * 
         * @param leftSensor2 The reading of the farthest left reflectance sensor
         * @param leftSensor1 The reading of the middle left reflectance sensor
         * @param rightSensor1 The reading of the middle right reflectance sensor
         * @param rightSensor2 The reading of the farthest right reflectance sensor
         * @param lastState
         * 
         * @return an integer value representing the state of the system
        */
        int getCurrentState(int leftSensor2, int leftSensor1, int rightSensor1, int rightSensor2, int lastState, int lastError);

        /**
         * limits the angle of the servo based on the geometry of the chasis so that it does not stall
         * 
         * @param angle the current servo angle that it currently should be 
         * 
         * @return an integer with the limited angle it ranges form PIDNS::MIN_ANGLE to PIDNS::MAX_ANGLE
        */
        int limitAngle(int angle);

        /**
         * converts the analog signal from the reflectance sensors to a digital reading
         * 
         * @param value the reading from the sensor (0 - 1023)
         * 
         * @return an integer of either 0 or 1. 0 if the value is equal to or below the specified threshold in constants or 1 if above. 
        */
        int getDigital(int value, int previousDigital);

        

        // class inits and other variables.

        // Motor leftMotor(MotorNS::LEFT_MOTOR_FWD, MotorNS::LEFT_MOTOR_BWD);
        // Motor rightMotor(MotorNS::RIGHT_MOTOR_FWD, MotorNS::RIGHT_MOTOR_BWD);

        int servoAngle;
        int lastState;
        int timeInCurrent;
        int timeInPrev;


        float integral;
        int lastError;
        
};


#endif