#include <Arduino.h>

#include <Constants.h>
#include <IR.h>
#include <Helper.h>

#include <Adafruit_SSD1306.h>

void setup() {
    Serial.begin(9600);  
    pinMode(IRNS::KHZ_WAVE_PIN, INPUT);
}

void loop() {
    IR ir;
    float waveform[IRNS::NUM_READINGS];
    float maxCorrelation = 0;

    //samples a wave and normalilzes it
    for (int i = 0; i < IRNS::NUM_READINGS; i++){
        waveform[i] = analogRead(IRNS::KHZ_WAVE_PIN) / (float) 1024;
        delayMicroseconds(1000000 / IRNS::SAMPLING_FREQUENCY);
    }

    unsigned long currentMillis = micros();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        waveform[sampleIndex] = analogRead(IRNS::KHZ_WAVE_PIN) / (float)1024;
        sampleIndex++;

        if (sampleIndex >= IRNS::NUM_READINGS) {
            // Transition to the PROCESSING state when sampling is done.
            currentState = State::PROCESSING;
        }
    }

    maxCorrelation = ir.maxCorrelationOneK(waveform);

    Serial.println("correlation: ");
    Serial.println(maxCorrelation);

    delay(5000);

    
    Serial.println("start");
    for (int i = 0; i < IRNS::NUM_READINGS; i++){
        Serial.println(waveform[i]);
    }


}
