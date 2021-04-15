/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SamplerxAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SamplerxAudioProcessor();
    ~SamplerxAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void loadFile();
    void loadFile(const juce::String& path);
    int getNumSamplerSounds() { return mySynth.getNumSounds(); };
    void getADSRParameters();
    juce::ADSR::Parameters& getADSR() { return adsrParameters; };
    juce::AudioBuffer<float>& getWaveForm() { return waveForm; };
    juce::AudioProcessorValueTreeState tree;
    std::atomic<bool>& getIsNotePlayed() { return isNotePlayed; };
    std::atomic<int>& getSampleCount() { return sampleCount; };
    float getLevel() { return *tree.getRawParameterValue("level"); };
    private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamplerxAudioProcessor)
        juce::Synthesiser mySynth;
    const int numVoices = 3;
    juce::AudioFormatManager formatManager;
    juce::AudioFormatReader* formatReader{ nullptr };
    juce::AudioBuffer<float> waveForm;
    juce::ADSR::Parameters adsrParameters;
    std::atomic<bool> isNotePlayed = false;//Heavier Data Type--> Use it for a var which is being written in a different thread and being read in another
    std::atomic<int> sampleCount;
};
