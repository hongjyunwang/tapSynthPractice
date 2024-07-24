/*
  ==============================================================================

    AdsrData.h
    Created: 19 Jul 2024 11:57:29pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

    
private:
    juce::ADSR::Parameters adsrParams;
};
