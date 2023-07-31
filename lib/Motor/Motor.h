#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor {
    public:

        /**
         * Constructor for the motor class
        */
        Motor(PinName forwardPin, PinName backwardPin);

        /**
         * stops the motor from moving 
        */
        void stop();

        /**
         * sets the motor to a certain speed
         * 
         * @param speed of the motor. (-255 <= speed <= 255) if negative motor goes backwards. if positive it goes forward.
        */
        void speed(int speed);


    private:

    PinName forwardPin;
    PinName backwardPin;

};

#endif