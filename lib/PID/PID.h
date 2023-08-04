#ifndef PID_h
#define PID_h

#include <Arduino.h>
#include <Constants.h>
#include <Motor.h>
#include <ReflectorSensors.h>

class PID {
    public:

        /**
         * PID constructor
         * 
         * @param sensors the sensors that will be used.
        */
        PID(Reflectors* sensors);

        /**
         * usePID makes the servos turn
         * 
         * @param speed the speed at which the motors will run. (0 to 255)
        */
        void usePID(int speed);

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
        int getTotalState(int leftSensor2, int leftSensor1, int rightSensor1, int rightSensor2, int lastState);

        /**
         * limits the angle of the servo based on the geometry of the chasis so that it does not stall
         * 
         * @param angle the current servo angle that it currently should be 
         * 
         * @return an integer with the limited angle it ranges form PIDNS::MIN_ANGLE to PIDNS::MAX_ANGLE
        */
        int limitAngle(int angle);

        /**
         * writes the angle of the servo
         * 
         * @param angle the angle we want the servo to turn. 
        */
        void writeServoAngle(int angle);

        // class inits and other variables.

        // Motor leftMotor(MotorNS::LEFT_MOTOR_FWD, MotorNS::LEFT_MOTOR_BWD);
        // Motor rightMotor(MotorNS::RIGHT_MOTOR_FWD, MotorNS::RIGHT_MOTOR_BWD);

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
        
};


#endif