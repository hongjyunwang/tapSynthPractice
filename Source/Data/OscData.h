/*
  ==============================================================================

    OscData.h
    Created: 20 Jul 2024 6:04:30pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& block);
    void setFmParams (const float freq, const float depth);
    
private:
    // Create oscillator for FM modulation 
    juce::dsp::Oscillator<float> fmOsc {[](float x) {return sin(x);}};
    float fmMod {0.0f};
    // We create fmDepth here to scale the gain as the juce::dsp::Oscillator<float> fmOsc object does not have a set gain method for the entire oscillator
    // So we create this float value and multiply it to our sample value when we do sample by sample processing
    float fmDepth {0.0f};
    
    int lastMidiNoteNumber { 0 };
    
};
