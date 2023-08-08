#ifndef Sonar_h
#define Sonar_h

#include <Arduino.h>

class Sonar {
    public:

        /**
         * Sonar constructor
         * 
         * @param sonarEcho the echo pin 
         * @param sonarTrig the trigger pin
        */
        Sonar(int sonarEcho, int sonarTrig);

        /**
         * getDistance returns the distance in cm
         * 
         * @return the distance in cm
        */
        int getDistance();


    private:

    int sonarTrig, sonarEcho;


};


#endif