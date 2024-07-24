/*
  ==============================================================================

    SynthSound.h
    Created: 15 Jul 2024 9:39:23pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
// Describes one of the sounds that a Synthesiser can play. A synthesiser can contain one or more sounds, and a sound can choose which midi notes and channels can trigger it.
class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override {return true;}
    bool appliesToChannel (int midiChannel) override {return true;}
    
};
