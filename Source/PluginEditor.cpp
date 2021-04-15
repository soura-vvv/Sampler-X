/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerxAudioProcessorEditor::SamplerxAudioProcessorEditor (SamplerxAudioProcessor& p)
    : AudioProcessorEditor (&p),myWaveThumbnail(p),myADSR(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 400);

    //Labels
    addAndMakeVisible(myWaveThumbnail);
    addAndMakeVisible(myADSR);
    startTimerHz(30);
}

SamplerxAudioProcessorEditor::~SamplerxAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void SamplerxAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll(juce::Colours::lightseagreen.brighter());
   g.setColour(juce::Colours::white);
   
    
    
    /*if (audioProcessor.getNumSamplerSounds() > 0)
    {
        g.fillAll(juce::Colours::red);
    }*/
   
}

void SamplerxAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   // loadButton.setBounds(getWidth()/2-50,getHeight()/2-50,100,100);
    //attackSlider.setBoundsRelative(0.5,0.5,0.1,0.4);
    auto area = getLocalBounds().reduced(10);
    myWaveThumbnail.setBounds(area.removeFromTop(250));
    area.removeFromTop(10);
    myADSR.setBounds(area);
    
}
bool WaveThumbnail::isInterestedInFileDrag(const juce::StringArray& files)
{
    
    return true;
}
void WaveThumbnail::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(files))
        {
            //load This File
            auto myFile = std::make_unique<juce::File>(file);
            filename=myFile->getFileNameWithoutExtension();
            toPaint = true;
            audioProcessor.loadFile(file);
        }
    }
    //repaint();
}
void SamplerxAudioProcessorEditor::timerCallback()
{
    repaint();
}