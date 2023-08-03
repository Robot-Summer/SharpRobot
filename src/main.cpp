#include <Arduino.h>
#include <Wire.h>

#include <Constants.h>
#include <IR.h>
#include <Helper.h>
#include <Master.h>
#include <PID.h>

HardwareSerial Serial3(PB11, PB10);

#include <Adafruit_SSD1306.h>
 
Master state;

void setup() {
    Serial3.begin(9600);
    state.setState(MasterState::DRV_TAPE);
}



void loop() {
    state.poll();
}