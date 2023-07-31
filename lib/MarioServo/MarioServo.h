#ifndef MarioServo_h
#define MarioServo_h

#include <Arduino.h>

class MarioServo {
    public:

        /**
         * constructor for the servo
         * 
         * @param pin integer for the servo
        */
        MarioServo(int servoPin);

        /**
         * moves the servo to a specific angle.
         * 
         * @param angle the angle at which you want the servo
        */
        void writeAngle(int angle);

    private:

    int servoPin;
};

#endif

