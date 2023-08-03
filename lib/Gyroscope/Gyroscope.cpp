#include <Arduino.h>
#include <Gyroscope.h>
#include <Constants.h>
#include <Helper.h>
#include <Wire.h>

Gyro::Gyro()
{    
    Wire.begin();
    Wire.beginTransmission(GyroscopeNS::MPU_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
}

float Gyro::getXAngle(){
    int yAng = map(AcY,GyroscopeNS::MIN_VAL, GyroscopeNS::MAX_VAL,-90,90);
    int zAng = map(AcZ,GyroscopeNS::MIN_VAL, GyroscopeNS::MAX_VAL,-90,90);
    float x = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);

    return x;
}

float Gyro::getYAngle(){
    int xAng = map(AcX,GyroscopeNS::MIN_VAL, GyroscopeNS::MAX_VAL,-90,90);
    int zAng = map(AcZ,GyroscopeNS::MIN_VAL, GyroscopeNS::MAX_VAL,-90,90);
    float y = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);

    return y;
}


float Gyro::getZAngle(){
    int yAng = map(AcY,GyroscopeNS::MIN_VAL, GyroscopeNS::MAX_VAL,-90,90);
    int xAng = map(AcX,GyroscopeNS::MIN_VAL, GyroscopeNS::MAX_VAL,-90,90);
    float z = RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

    return z;
}


void Gyro::readWire(){
    AcX=Wire.read()<<8|Wire.read();
    AcY=Wire.read()<<8|Wire.read();
    AcZ=Wire.read()<<8|Wire.read();
}


void Gyro::beginTransmission(){
    Wire.beginTransmission(GyroscopeNS::MPU_ADDR);  //initiates a communication transmission to the gyroscope sensor. It informs the sensor that the Arduino wants to read or write data to/from it.
    Wire.write(0x3B); //writes a single byte (0x3B) to the gyroscope sensor.
    Wire.endTransmission(false); //ends the transmission to the gyroscope sensor, but the false parameter indicates that the Arduino does not send a stop signal on the I2C bus.
    Wire.requestFrom(GyroscopeNS::MPU_ADDR,14,true); //requests 14 bytes of data from the gyroscope sensor with the address specified. Because of "true", Arduino stops the signal after transition.
}


