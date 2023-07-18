#include <Arduino.h>

#include <Constants.h>
#include <Helper.h>

#include <IR.h>

float IR::maxCorrelationOneK(float* waveform){
    float onek[IRNS::NUM_READINGS];
    float correlation = 0.0;


    //generates a normalized reference wave
    for (int i = 0; i < IRNS::NUM_READINGS; i++) {
        onek[i] = 0.5 * sin(2 * PI * ((double) IRNS::NUM_WAVES / IRNS::NUM_READINGS) * i) + 0.5;
    }

    // Calculate the cross-correlation
    for (int k = 0; k < IRNS::NUM_READINGS; k++) {
        float sum = 0.0;
        for (int i = 0; i < IRNS::NUM_READINGS; i++) {
            // sum += (reference[i] - referenceMean) * (measured[i + k] - referenceMean);
            sum += (waveform[i]) * (onek[i + k]); //without normalization
        }
        correlation = fmax(correlation, sum);
    }

    // Normalize the correlation coefficient
    // correlation /= (IRNS::NUM_READINGS * referenceStdDev * referenceStdDev);

    return correlation;
}


unsigned long IR::waveformSample(float* waveform, int sampleIndex) {
    unsigned long start = micros();
    waveform[sampleIndex] = analogRead(IRNS::KHZ_WAVE_PIN);
    return micros() - start;
}


    // Calculate the mean of the reference and measured waveforms

    // Pre-calculate the mean of the reference waveform
    // float referenceMean = 0.0;
    // for (int i = 0; i < IRNS::NUM_READINGS; i++) {
    //     referenceMean += reference[i];
    // }
    // referenceMean /= IRNS::NUM_READINGS;

    // Calculate the standard deviation of the reference waveform
    // float referenceStdDev = 0.0;
    // for (int i = 0; i < IRNS::NUM_READINGS; i++) {
    //     float diff = reference[i] - referenceMean;
    //     referenceStdDev += diff * diff;
    // }
    // referenceStdDev = sqrt(referenceStdDev / IRNS::NUM_READINGS);