#ifndef Helper_h
#define Helper_h

#include <Arduino.h>

class Helper {
    public:
    
    /**
     * getAverageAnalog gives an integer value for the average reading of a specified analog pin.
     * 
     * @param analogPin the analalog pin that will be read
     * @param numReadings the number of readings done for the average must be greater than 0
     * 
     * @return integer value of the average sensor's value
    */
   static int getAverageAnalog(int analogPin, int numReadings);

};

#endif