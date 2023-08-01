#include <Arduino.h>
#include <Wire.h>

#include <Constants.h>
#include <IR.h>
#include <Helper.h>
#include <Master.h>
#include <PID.h>

HardwareSerial Serial3(PB11, PB10);

#include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define OLED_RESET  -1 // This display does not have a reset pin accessible
// Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IR ir;
// float waveform[IRNS::NUM_READINGS];

 
Master state;

// PID help;

void setup() {
    Serial3.begin(9600);
    // pinMode(IRNS::KHZ_WAVE_PIN, INPUT);


    // display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
    // // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
    // display_handler.display();
    // delay(1000);

    // display_handler.clearDisplay();
    // display_handler.setTextSize(1);
    // display_handler.setTextColor(SSD1306_WHITE);
    // display_handler.setCursor(0,0);
    // display_handler.println("hello world");
    // display_handler.display();

    state.setState(MasterState::DRV_TAPE);

}



void loop() {
    // display_handler.clearDisplay();
    // display_handler.setCursor(0, 0);

    // display_handler.println(count);
    
    // float maxCorrelation;

    // maxCorrelation = ir.maxCorrelationOneK(waveform);
    
    // display_handler.print("correlation: ");
    // display_handler.println(maxCorrelation);

    // if (maxCorrelation >= 0.018) {
    //     display_handler.println("I SEE THE WAY!");

    // } else {
    //     display_handler.println("I DON'T SEE THE WAY");
    // }

    // display_handler.display();

    // digitalWrite(PC13, !digitalRead(PC13));
    //delay(500);

    state.poll();

    // help.usePID();

    // myservo.writeAngle(100);


}