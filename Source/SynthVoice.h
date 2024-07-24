/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Jul 2024 9:38:56pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "OscData.h"
#include "AdsrData.h"
#include "FilterData.h"


// SynthVoice represents a voice that a Synthesiser can use to play a SynthesiserSound. A voice plays a single sound at a time, and a synthesiser holds an array of voices so that it can play polyphonically.
class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void updateAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateFilter(const int filterType, const float frequency, const float resonance);
    void updateModAdsr(const float attack, const float decay, const float sustain, const float release);
    
    OscData& getOscillator() { return osc; };
    
private:
    
    OscData osc;
    AdsrData adsr;
    FilterData filter;
    AdsrData modAdsr;
    
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};
    
    // Create an additional buffer to remove clicking when playing different notes
    // When we input an outputBuffer into renderNextBlock, there may already be samples in the outputBuffer.
    // When we  press a new note and render the next block in the same outputBuffer, the phase of the sound already in the outputBuffer may clash with the new sound's phase, causing clicking
    // To solve this, we create this synthBuffer and apply chnges to it, AND THEN we add this synthBuffer to the outputBuffer
    juce::AudioBuffer<float> synthBuffer;
    
};
