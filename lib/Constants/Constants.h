#ifndef Constants_h
#define Constants_h

#include <Arduino.h>

//TODO: Make a namespace for each library and declare all constants for the library (stm32 pins)

//Motors Name Space
namespace MotorsNS {

    //Example:
    const int RIGHT_MOTOR = PA1;
    const int LEFT_MOTOR = PA2;
}


//Reflectance Sensors Name Space
namespace ReflectanceSensorsNS {

}

//Gyroscope Name Space
namespace GyroscopeNS {

}

//IR sensor Name Space
namespace IRNS {
    const int KHZ_WAVE_PIN = PA6;
    //const int KHZ_WAVE_THRESHOLD = 300;
    const int NUM_WAVES = 10;

    const int SAMPLING_FREQUENCY = 5000;

    const int NUM_READINGS = NUM_WAVES  * SAMPLING_FREQUENCY / 1000;

}

#endif