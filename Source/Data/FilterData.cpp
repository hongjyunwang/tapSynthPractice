/*
  ==============================================================================

    FilterData.cpp
    Created: 21 Jul 2024 10:07:03pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#include "FilterData.h"
void FilterData::prepareToPlay(double sampleRate, double samplesPerBlock, int numChannels){
    filter.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    filter.prepare(spec);
    
    isPrepared = true;
}


void FilterData::process(juce::AudioBuffer<float>& buffer){
    
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> block (buffer);
    
    filter.process(juce::dsp::ProcessContextReplacing<float>{block});
}


void FilterData::updateParameters(const int filterType, const float frequency, const float resonance, const float modulator){
    switch (filterType) {
        case 0:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case 1:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
        case 2:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
    }
    float modFreq = std::fmax(frequency * modulator, 20.0f);
    modFreq = std::fmax(modFreq, 20.0f);
    modFreq = std::fmin(modFreq, 20000.0f);
    
    filter.setCutoffFrequency(modFreq);
    filter.setResonance(resonance);
}

void FilterData::reset(){
    filter.reset();
}
