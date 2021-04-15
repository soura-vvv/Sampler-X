/*
  ==============================================================================

    ADSRComponent.h
    Created: 13 Apr 2021 4:06:06pm
    Author:  Sourav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class ADSRComponent  : public juce::Component
{
public:
    ADSRComponent(SamplerxAudioProcessor& p);
    ~ADSRComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::Slider levelSlider;
    juce::Slider finePitchSlider;
    juce::TextButton loadButton{ "Load" };
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;
    juce::Label levelLabel;
    juce::Label finePitchLabel;
    SamplerxAudioProcessor& audioProcessor;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> treeState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)

};
