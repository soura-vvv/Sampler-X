/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 13 Apr 2021 3:24:08pm
    Author:  Sourav

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"

//==============================================================================
WaveThumbnail::WaveThumbnail(SamplerxAudioProcessor& p):audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveThumbnail::~WaveThumbnail()
{
}

void WaveThumbnail::paint (juce::Graphics& g)
{   
    g.fillAll(juce::Colours::black.withAlpha(0.55f));
    juce::Path p;
    g.setColour(juce::Colours::white);
    g.setFont(25.0f);
    auto titleBounds = getLocalBounds().reduced(5);
    auto waveForm = audioProcessor.getWaveForm();
   g.drawFittedText("SAMPLER-X", titleBounds, juce::Justification::centredTop, 1);
    auto samplerXImage =juce::ImageCache::getFromMemory(BinaryData::samplerx_png, BinaryData::samplerx_pngSize);
    if(!samplerXImage.isNull())
        samplerXImageComponent.setImage(samplerXImage,juce::RectanglePlacement::stretchToFit);
    addAndMakeVisible(samplerXImageComponent);
    if (waveForm.getNumSamples()>0)
    {

        g.setColour(juce::Colours::blue);

        audioPoints.clear();
        auto waveForm = audioProcessor.getWaveForm();
        auto ratio = waveForm.getNumSamples() / getWidth();
        auto buffer = waveForm.getReadPointer(0);
        for (int sample = 0; sample < waveForm.getNumSamples(); sample += ratio)
        {
            audioPoints.push_back(buffer[sample]);
        }

        p.startNewSubPath(0, getHeight() / 2);
        for (int sample = 0; sample < audioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(audioPoints[sample], -1, 1, getHeight(), 0);
            p.lineTo(sample, point);
        }

        g.strokePath(p, juce::PathStrokeType(2));
        toPaint = false;
        g.setColour(juce::Colours::white);
        auto textBounds = getLocalBounds().reduced(10);
        g.setFont(15.0f);
        g.drawFittedText(filename, textBounds, juce::Justification::bottomRight, 1);
        auto playHeadPosition = juce::jmap<int>(audioProcessor.getSampleCount(),0,audioProcessor.getWaveForm().getNumSamples(),0,getWidth());
        g.setColour(juce::Colours::white);
        g.drawLine(playHeadPosition,0,playHeadPosition,getHeight(),2);

        g.setColour(juce::Colours::black.withAlpha(0.4f));
    }
    else
    {
        g.setFont(15.0f);
        g.drawFittedText("DRAG FILE TO LOAD A SAMPLE", titleBounds, juce::Justification::centred, 1);
    }
        
}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //samplerXImageComponent.setBounds(0.0f, 0.0f,40,30);
}
