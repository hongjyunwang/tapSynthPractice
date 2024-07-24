/*
  ==============================================================================

    FilterComponent.cpp
    Created: 22 Jul 2024 8:05:36pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& treeState, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId)
{
    
    juce::StringArray choices {"Low-Pass", "Band-Pass", "High-Pass"};
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);
    
    // Make attachment
    // Just a reminder that the attachment allows the treeState to capture user input on the combobox, which allows the pluginProcessor to set the wave type through the OscData class
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(treeState, filterTypeSelectorId, filterTypeSelector);
    
    setSliderWithLabel(filterFreqSlider, filterFreqLabel, treeState, filterFreqId, filterFreqAttachment);
    setSliderWithLabel(filterResSlider, filterResLabel, treeState, filterResId, filterResAttachment);
    
    addAndMakeVisible(filterSelectorLabel);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll(juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("Filter", labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{
    const int startY = 55;
    const int sliderWidth = 100;
    const int sliderHeight = 90;
    const int labelYOffset = 20;
    const int labelHeight = 20;
    
    filterTypeSelector.setBounds(10, startY + 5, 90, 30);
    filterSelectorLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);
    
    filterFreqSlider.setBounds(filterTypeSelector.getRight(), startY, sliderWidth, sliderHeight);
    filterFreqLabel.setBounds(filterFreqSlider.getX(), filterFreqSlider.getY() - labelYOffset, filterFreqSlider.getWidth(), labelHeight);
    
    filterResSlider.setBounds(filterFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    filterResLabel.setBounds(filterResSlider.getX(), filterResSlider.getY() - labelYOffset, filterResSlider.getWidth(), labelHeight);

} 

void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& treeState, juce::String paramID, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment)
{
    // Create slider and attach to treeState
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, paramID, slider);
    
    // Create labels
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(15.0f);
    addAndMakeVisible(label);
}
