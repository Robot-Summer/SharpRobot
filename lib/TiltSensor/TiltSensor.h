#ifndef TiltSensor_h
#define TiltSensor_h

#include <Arduino.h>

class TiltSensor {
    public:

    /** 
     * Constructor of Tiltsensor Class
     * 
    */

    TiltSensor();

    /** 
     * Reads the state of the tilt sensor. 
     * 
     * Gives HIGH if the tiltSensor is triggered (Robot moving down the ramp) and LOW otherwise.
    */
    bool readTiltSensor();

           
    
};

#endif