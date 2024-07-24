/*
  ==============================================================================

    OscComponent.cpp
    Created: 20 Jul 2024 6:49:59pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& treeState, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId)
{
    juce::StringArray choices {"Sine", "Saw", "Square"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);
    
    // Make attachment
    // Just a reminder that the attachment allows the treeState to capture user input on the combobox, which allows the pluginProcessor to set the wave type through the OscData class
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(treeState, waveSelectorId, oscWaveSelector);
    
    setSliderWithLabel(fmFreqSlider, fmFreqLabel, treeState, fmFreqId, fmFreqAttachment);
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, treeState, fmDepthId, fmDepthAttachment);
    
    addAndMakeVisible(waveSelectorLabel);
    
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll(juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("Oscillator", labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void OscComponent::resized()
{
    const int startY = 55;
    const int sliderWidth = 100;
    const int sliderHeight = 90;
    const int labelYOffset = 20;
    const int labelHeight = 20;
    
    oscWaveSelector.setBounds(10, startY + 5, 90, 30);
    waveSelectorLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);
    
    fmFreqSlider.setBounds(oscWaveSelector.getRight(), startY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);
    
    fmDepthSlider.setBounds(fmFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
}

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& treeState, juce::String paramID, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment)
{
    // Create slider and attach to apvts
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, paramID, slider);
    
    // Create fmFreqLabel
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(15.0f);
    addAndMakeVisible(label);
}
