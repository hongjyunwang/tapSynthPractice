/*
  ==============================================================================

    AdsrData.cpp
    Created: 19 Jul 2024 11:57:29pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters(adsrParams);
}
