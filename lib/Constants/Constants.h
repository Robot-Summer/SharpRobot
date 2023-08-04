#include <Arduino.h>

#ifndef Constants_h
#define Constants_h

//TODO: Make a namespace for each library and declare all constants for the library (stm32 pins)

//Motors Name Space
namespace MotorsNS {

    //Example:
    const int RIGHT_MOTOR = PA1;
    const int LEFT_MOTOR = PA2;
}


// Constants for the PID controller for tape following
namespace PIDNS {
    // Servo Constants
    const int MAX_ANGLE = 138;
    const int MIN_ANGLE = 52;
    const int INITIAL_ANGLE = 95;
    static const PinName SERVO_PIN = PA_0;

    // PID Constants
    const float KP = 12.0;
    const float KD = 0.5;  
    const float KI = 0.001; 

    const int DIGITAL_THRESHOLD = 185;

    // Reflectance sensors PINS
    const int LEFT_SENSOR_ONE = PB0;
    const int LEFT_SENSOR_TWO = PB1;
    const int RIGHT_SENSOR_ONE = PA5;
    const int RIGHT_SENSOR_TWO = PA4;

}

//Gyroscope Name Space
namespace GyroscopeNS {

}

//IR sensor Name Space
namespace IRNS {
    const int KHZ_WAVE = PA1;

    const int KHZ_WAVE_THRESHOLD = 300;
}

#endif