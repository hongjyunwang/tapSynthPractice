/*
  ==============================================================================

    FilterData.h
    Created: 21 Jul 2024 10:07:03pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// This is our wrapper around the juce::dsp::StateVariableTPTFilter<float> class
class FilterData
{
public:
    // Whenever we have some sort of dsp processing, we always need a prepareToPlay functionality
    // To pass the sample rate and buffer size to the algorithm
    void prepareToPlay(double sampleRate, double samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int filterType, const float frequency, const float resonance, const float modulator = 1.0f);
    void reset();
    
private:
    
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared {false};

};
