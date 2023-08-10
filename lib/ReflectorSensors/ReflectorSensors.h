#ifndef ReflectorSensors_h
#define ReflectorSensors_h

#include <Arduino.h>

class Reflectors {
    public:

        /**
         * reflectors constructor
        */
        Reflectors();

        /**
         * gets the state from the reflector
         * 
         * @param sensor 0 for far left, 1 for middle left, 2 for middle right, 3 for far right.
         * 
         * @return the state of the sensor. 0 if on white 1 if on black, -1 if invalid input.
        */
        int getReflectorValue(int sensor);

        /**
         * checks if all sensors are on the bridge marker
         * 
         * @return true if the tape sensors were on a marker and false otherwise.
        */
        bool bridgeMarker();

        /**
         * USED FOR DEBUGGING AND CALLIBRATION.
         * 
         * prints all sensor values on the serial monitor.
        */
        void printValues();

    private: 

        /**
         * converts the analog signal from the reflectance sensors to a digital reading
         * 
         * @param value the reading from the sensor (0 - 1023)
         * @param previousState the digital value for the sensor in the previous state
         * 
         * @return an integer of either 0 or 1. 0 if the value is equal to or below the specified 
         *          threshold in constants or 1 if above. -1 if wrong parameter. 
        */
        int getDigital(int value, int previousState);
        
        int l2, l1, r1, r2; //an integer value for the state of each sensor. 
        int pl2, pl1, pr1, pr2; //previous states for all the sensors. 

};

#endif