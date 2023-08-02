#ifndef Gyroscope_h
#define Gyroscope_h

#include <Arduino.h>

class Gyro {
    /** 
     * Gyro class constructor
     * 
    */
    Gyro();


    public:

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


   int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;



    
};

#endif