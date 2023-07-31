#include <Arduino.h>

#include <Constants.h>
#include <Helper.h>

#include <IR.h>

//TODO: Erase all unneccesary comments and comment for clarity


float IR::maxCorrelationOneK(float waveform[]) {
    //average of the sampled wave
    float waveformAverage = 0;
    for (int i = 0; i < IRNS::NUM_READINGS; i++) {
        waveformAverage += waveform[i];
    }
    waveformAverage /= IRNS::NUM_READINGS;

    float onek[IRNS::NUM_READINGS];

    //generates a normalized reference wave
    for (int i = 0; i < IRNS::NUM_READINGS; i++) {
        onek[i] = .5 * sin(2 * PI * ((float) IRNS::NUM_WAVES / IRNS::NUM_READINGS) * i);
        waveform[i] -= waveformAverage; //centers the waveform around 0
    }

    float correlation = 0.0;
    for (int shift = 0; shift < IRNS::NUM_READINGS; shift++) {
        float sum = 0.0;
        for (int i = 0; i + shift < IRNS::NUM_READINGS; i++) {
            sum += ( waveform[i]) * ( onek[shift] ); 
        }
        correlation = fmax ( correlation, sum );
    }

    return correlation;
}

unsigned long IR::waveformSample(float* waveform) {
    unsigned long start = micros();
    
    //samples a wave and normalilzes it
    for (int i = 0; i < IRNS::NUM_READINGS; i++){
        waveform[i] = analogRead(IRNS::KHZ_WAVE_PIN) / (float) 1024;
        delayMicroseconds(1000000 / IRNS::SAMPLING_FREQUENCY);
    }

    return micros() - start;
}