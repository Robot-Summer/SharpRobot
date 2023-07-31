#ifndef IR_h
#define IR_h

#include <Arduino.h>
#include <Constants.h>


class IR {
    public:

        /**
         * maxCorrelationOneK cross-correlates a sampled wave with a created 1khz reference wave and returns the correlation's max.
         * 
         * @param waveform The array containing the waveform samples.
         * 
         * @return a float value of the max of the convoluted wave.
        */
        float maxCorrelationOneK(float waveform[]);

        /**
         * gathers a sample
         * 
         * @param waveform A pointer to the array containing the other waveform samples (must be a set size)
         * 
         * @return returns the time it took to run the function in micros
        */
        unsigned long waveformSample(float* waveform);

    private:


        //TODO: add all constants and instances for ir to work

    

};


#endif