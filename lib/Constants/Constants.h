#ifndef Constants_h
#define Constants_h

#include <Arduino.h>

//TODO: Make a namespace for each library and declare all constants for the library (stm32 pins)

//Motors Name Space
namespace MotorNS {

    static const PinName RIGHT_MOTOR_FWD = PA_6;
    static const PinName RIGHT_MOTOR_BWD = PA_10;
    static const PinName LEFT_MOTOR_FWD = PA_9;
    static const PinName LEFT_MOTOR_BWD = PA_8;

    const int MOTOR_FREQ = 1000;

    const int MAX_SPEED = 170;

}


//Reflectance Sensors Name Space
namespace PIDNS {
    // Servo Constants
    const int MAX_ANGLE = 183;
    const int MIN_ANGLE = 90;
    const int INITIAL_ANGLE = 135;
    static const PinName SERVO_PIN = PA_0;

    // PID Constants
    const float KP = 12.0;
    const float KD = 0.00;  
    const float KI = 0.001; 

    const int DIGITAL_THRESHOLD = 150;


    // Reflectance sensors PINS
    const int LEFT_SENSOR_ONE = PA5;
    const int LEFT_SENSOR_TWO = PA4;
    const int RIGHT_SENSOR_ONE = PB0;
    const int RIGHT_SENSOR_TWO = PB1;

}

//Gyroscope Name Space
namespace GyroscopeNS {
    const int MPU_ADDR=0x68;
    const int MIN_VAL=265;
    const int MAX_VAL=402;


}

//IR sensor Name Space
namespace IRNS {
    //TODO: Tune the IR to read as best as possible

    const int KHZ_WAVE_PIN = PA3;

    const int CORROLATED_WAVE_THRESHOLD = .05; //corrolation threshold

    const int NUM_WAVES = 15; //higher the cycles the more readings

    const int SAMPLING_FREQUENCY = 5000; //keep the sampling frequency to at least twice the read wave. (2000 =<)

    const int NUM_READINGS = NUM_WAVES  * SAMPLING_FREQUENCY / 1000;

}

#endif