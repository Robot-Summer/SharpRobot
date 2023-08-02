#include <Arduino.h>
#include <Gyroscope.h>
#include <Constants.h>
#include <Helper.h>
#include <Wire.h>

Gyro::Gyro(): 
    AcX(0),
    AcY(0),
    AcZ(0),
    Tmp(0),
    GyX(0),
    GyY(0),
    GyZ(0)
{
    Wire.begin();
    Wire.beginTransmission(GyroscopeNS::MPU_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Wire.beginTransmission(GyroscopeNS::MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(GyroscopeNS::MPU_ADDR,14,true);
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


