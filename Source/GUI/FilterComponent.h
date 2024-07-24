/*
  ==============================================================================

    FilterComponent.h
    Created: 22 Jul 2024 8:05:36pm
    Author:  Hong Jyun Wang

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& treeState, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::ComboBox filterTypeSelector {"Filter Type"};
    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResAttachment;
    
    juce::Label filterSelectorLabel {"Filter Type", "Filter Type"};
    juce::Label filterFreqLabel {"Filter Freq", "Filter Freq"};
    juce::Label filterResLabel {"Filter Res", "Filter Res"};
    
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& treeState, juce::String paramID, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
