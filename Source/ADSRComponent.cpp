/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 13 Apr 2021 4:06:06pm
    Author:  Sourav

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(SamplerxAudioProcessor& p):audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(loadButton);
    loadButton.onClick = [&]() {audioProcessor.loadFile(); };
    //Level Slider
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider.setRange(0.0f, 0.8f, 0.025);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    levelSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::blue.darker());
    addAndMakeVisible(levelSlider);

    levelLabel.setFont(15.0f);
    levelLabel.setText("LEVEL", juce::NotificationType::dontSendNotification);
    levelLabel.setJustificationType(juce::Justification::centredTop);
    levelLabel.attachToComponent(&levelSlider, false);
    treeState = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "level", levelSlider);

    //FinePitch Slider

    finePitchSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    finePitchSlider.setRange(-12,12, 1);
    finePitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    finePitchSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::blue.darker());
    addAndMakeVisible(finePitchSlider);

    finePitchLabel.setFont(15.0f);
    finePitchLabel.setText("FINE PITCH", juce::NotificationType::dontSendNotification);
    finePitchLabel.setJustificationType(juce::Justification::centredTop);
    finePitchLabel.attachToComponent(&finePitchSlider, false);
    treeState = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "finePitch", finePitchSlider);


    //attackSlider

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setRange(0.1f, 5.0f, 0.01);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    attackSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::blue.darker());
    addAndMakeVisible(attackSlider);

    attackLabel.setFont(15.0f);
    attackLabel.setText("ATTACK", juce::NotificationType::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centredTop);
    attackLabel.attachToComponent(&attackSlider, false);
    treeState = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "attack", attackSlider);
    //decaySlider
    addAndMakeVisible(decaySlider);
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    decaySlider.setRange(0.1f, 5.0f, 0.01);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    decaySlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::blue.darker());
    decayLabel.setFont(15.0f);
    decayLabel.setText("DECAY", juce::NotificationType::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centredTop);
    decayLabel.attachToComponent(&decaySlider, false);
    treeState = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "decay", decaySlider);
    //Susutain Slider
    addAndMakeVisible(sustainSlider);
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sustainSlider.setRange(0.1f, 1.0, 0.01);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    sustainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::blue.darker());
    treeState = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "sustain", sustainSlider);
    sustainLabel.setFont(15.0f);
    sustainLabel.setText("SUSTAIN", juce::NotificationType::dontSendNotification);
    sustainLabel.setJustificationType(juce::Justification::centredTop);
    sustainLabel.attachToComponent(&sustainSlider, false);
    //Release Slider
    addAndMakeVisible(releaseSlider);
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSlider.setRange(0.1f, 5.0f, 0.01);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    releaseSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::blue.darker());
    treeState = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "release", releaseSlider);
    releaseLabel.setFont(15.0f);
    releaseLabel.setText("RELEASE", juce::NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centredTop);
    releaseLabel.attachToComponent(&releaseSlider, false);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black.withAlpha(0.5f));

    
}

void ADSRComponent::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    attackSlider.setBounds(area.removeFromLeft(100).removeFromBottom(90));
    decaySlider.setBounds(area.removeFromLeft(100).removeFromBottom(90));
    sustainSlider.setBounds(area.removeFromLeft(100).removeFromBottom(90));
    releaseSlider.setBounds(area.removeFromLeft(100).removeFromBottom(90));
    levelSlider.setBounds(area.removeFromLeft(100).removeFromBottom(90));
    finePitchSlider.setBounds(area.removeFromLeft(100).removeFromBottom(90));
}
