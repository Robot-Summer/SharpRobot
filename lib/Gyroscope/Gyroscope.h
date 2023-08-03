#ifndef Gyroscope_h
#define Gyroscope_h

#include <Arduino.h>

class Gyro {
    


    public:

        /** 
         * Gyro class constructor
         * 
        */
        Gyro();

        /** 
         * gets the angle with respect to x axis
         * 
         * @return integer value between 0 to 360 degrees
        */

        float getXAngle();

        /** 
         * gets the angle with respect to y axis
         * 
         * @return integer value between 0 to 360 degrees
        */

        float getYAngle();

        /** 
         * gets the angle with respect to z axis
         * 
         * @return integer value between 0 to 360 degrees
        */

        float getZAngle();

        /** 
         * Reads and combines bytes received 
         * from the I2C communication.
        */
        void readWire();

        /** 
         * Begins transmission of signal with the gyroscope
        */

        void beginTransmission();


        int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;

    private:

    
};

#endif