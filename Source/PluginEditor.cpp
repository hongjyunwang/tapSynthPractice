/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
, audioProcessor (p)
, osc(audioProcessor.treeState, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH")
, adsr("Amp Envelope", audioProcessor.treeState, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
, filter(audioProcessor.treeState, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
, modAdsr("Mod Envelope", audioProcessor.treeState, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (620, 500);
    
    // Make components visible
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(modAdsr);
}

TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
}

//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void TapSynthAudioProcessorEditor::resized()
{
    // Set adsr and osc bounds
    const auto paddingX = 5;
    const auto paddingY = 35;
    const auto width = 300;
    const auto height = 200;
        
    osc.setBounds (paddingX, paddingY, width, height);
    adsr.setBounds (osc.getRight(), paddingY, width, height);
    filter.setBounds(paddingX, osc.getBottom(), width, height);
    modAdsr.setBounds(filter.getRight(), adsr.getBottom(), width, height);
}

