/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Jul 2024 9:38:56pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound){
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition){
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn(); 
    modAdsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff){
    adsr.noteOff();
    modAdsr.noteOff();
    if(! allowTailOff || ! adsr.isActive()) return clearCurrentNote();
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue){
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue){

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels){
    // the ProcessSpec structure is passed into a DSP algorithm's prepare() method, and contains information about various aspects of the context in which it can expect to be called.
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    // Then we pass this ProcessSpec object into the oscillator and gain
    // This prepareToPlay on osc is wrapped with our own OscData class
    osc.prepareToPlay(spec);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    modAdsr.setSampleRate (sampleRate);
    gain.prepare(spec);
    
    // Apply new gain linearly rather than logarithmically
    gain.setGainLinear(0.3f);
    
    adsr.setSampleRate(sampleRate);
    
    isPrepared = true;
}

// This update function will be called by the processBlock to update information about the ADSR
void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples){
    
    // if isPrepared is false we want to stop execution
    jassert(isPrepared);
    
    // If the voice is currently silent, it should just return without doing anything.
    if(! isVoiceActive()) return;
    
    // Instead of inputting new sounds into the outputBuffer, we put them in this synthBuffer first
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    // Notice how we apply the filter modAdsr here, when the synthbuffer is empty
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    synthBuffer.clear();
    
    // We put the processing of processBlock into renderNextBlock (processBlock is going to call renderNextBlock)
    // the AudioBlock is essentially an alias for an audio buffer to put into dsp
    // It is a Minimal and lightweight data-structure which contains a list of pointers to channels containing some kind of sample data.
    // The object here is initialized with uniform initialization
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    // the ProcessContextReplacing object Contains context information that is passed into an algorithm's process method
    osc.getNextAudioBlock(audioBlock);
    
    // Apply adsr
    // Note that we apply adsr to outputBuffer while the process methods process on the audioBlock. This is ok because note that audioBlock is just an alias of outputBuffer
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    // Process with the filter
    filter.process(synthBuffer);
    
    // Process with the gain
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    
    
    
    // Now we add the synthBuffer into the outputBuffer channel by channel
    for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel){
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        // If the sound that the voice is playing finishes during the course of this rendered block, it must call clearCurrentNote(), to tell the synthesiser that it has finished.
        if(!adsr.isActive()) clearCurrentNote();
    }
}

void SynthVoice::updateFilter(const int filterType, const float frequency, const float resonance)
{
    float modulator = modAdsr.getNextSample();
    filter.updateParameters(filterType, frequency, resonance, modulator);
}

void SynthVoice::updateModAdsr(const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateADSR(attack, decay, sustain, release);
}
