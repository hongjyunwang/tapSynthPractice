/*
  ==============================================================================

    OscData.cpp
    Created: 20 Jul 2024 6:04:30pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec){
    fmOsc.prepare(spec);
    prepare(spec);
}

void OscData::setWaveType(const int choice){
    switch (choice) {
        case 0:
            // Sine Wave
            initialise([](float x) {return sin(x);});
            break;
            
        case 1:
            // Saw Wave
            initialise([](float x) {return x / juce::MathConstants<float>::pi;});
            break;
            
        case 2:
            // Square Wave
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber){
    // Notice how we are adding fmMod, which is a sample value, to the main wave frequency
    setFrequency(juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber) + fmMod);
    lastMidiNoteNumber = midiNoteNumber;
}

void OscData::getNextAudioBlock (juce::dsp::AudioBlock<float>& block){
    
    // Perform sample by sample processing (rather than the entire buffer) for the fm wave
    // We can do this with the processSample method 
    for(int channel = 0; channel < block.getNumChannels(); ++channel){
        for(int s = 0; s < block.getNumSamples(); ++s){
            fmMod = fmOsc.processSample(block.getSample(channel, s)) * fmDepth;
        }
    }
    
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setFmParams (const float freq, const float depth){
    // Set the fm waveform frequency and depth here
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    
    // Set the main waveform frequency here (as influenced by the fm waveform)
    // The phase increment cannot be negative, so we esure that here
    auto currentFreq = abs(juce::MidiMessage::getMidiNoteInHertz (lastMidiNoteNumber) + fmMod);
    setFrequency(currentFreq);
}
