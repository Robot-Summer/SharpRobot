#ifndef MyServo_h
#define MyServo_h

#include <Arduino.h>

class MyServo {
    public:

        /**
         * MyServo constructor
         * 
         * @param pin the pin that the servo is connected to
        */
        MyServo(PinName pin, int minAngle, int maxAngle, int initialAngle);

        /**
         * write writes the angle of the servo
         * 
         * @param angle the angle we want the servo to turn. 
        */
        void write(int angle);

    private:

        /**
         * limits the angle of the servo based on the geometry of the chasis so that it does not stall
         * 
         * @param angle the current servo angle that it currently should be
        */
        int limitAngle(int angle);

        PinName servoPin;

        const int MAX_ANGLE, MIN_ANGLE, INITIAL_ANGLE;

};

#endif