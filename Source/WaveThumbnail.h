/*
  ==============================================================================

    WaveThumbnail.h
    Created: 13 Apr 2021 3:24:08pm
    Author:  Sourav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class WaveThumbnail  : public juce::Component,
    public juce::FileDragAndDropTarget
{
public:
    WaveThumbnail(SamplerxAudioProcessor& p);
    ~WaveThumbnail() override;
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    void paint (juce::Graphics&) override;
    void resized() override;
    bool toPaint = false;
    juce::String filename{""};
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
        std::vector<float> audioPoints;
    juce::ImageComponent samplerXImageComponent;
    SamplerxAudioProcessor& audioProcessor;
};
