/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerxAudioProcessor::SamplerxAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    tree(*this, nullptr, juce::Identifier("SamplerX"), {
        std::make_unique<juce::AudioParameterFloat>("attack","Attack",0.1f,5.0f,0.2),
        std::make_unique<juce::AudioParameterFloat>("decay","Decay",0.1f,5.0f,0.2),
        std::make_unique<juce::AudioParameterFloat>("sustain","Sustain",0.1f,1.0f,0.2),
        std::make_unique<juce::AudioParameterFloat>("release","Release",0.1f,1.0f,0.2),
        std::make_unique<juce::AudioParameterFloat>("level","Level",0.0f,0.8f,0.25),
        std::make_unique<juce::AudioParameterFloat>("finePitch","FinePitch",-12,12,0)
        })
#endif
{
    formatManager.registerBasicFormats();
    for (int i = 0; i < numVoices; i++)
        mySynth.addVoice(new juce::SamplerVoice);
}

SamplerxAudioProcessor::~SamplerxAudioProcessor()
{
    formatReader = nullptr;
}

//==============================================================================
const juce::String SamplerxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SamplerxAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SamplerxAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SamplerxAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SamplerxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SamplerxAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SamplerxAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SamplerxAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SamplerxAudioProcessor::getProgramName (int index)
{
    return {};
}

void SamplerxAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SamplerxAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    mySynth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < mySynth.getNumSounds(); ++i)
    {
        if (auto sound = dynamic_cast<juce::SamplerSound*>(mySynth.getSound(i).get()))
        {
            sound->setEnvelopeParameters(adsrParameters);
        }
        
    }
}

void SamplerxAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SamplerxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SamplerxAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    getADSRParameters();
    juce::MidiMessage m;
    int sample;
    juce::MidiBuffer::Iterator it{midiMessages};
    while (it.getNextEvent(m,sample))
    {
        if (m.isNoteOn())
            isNotePlayed = true;
        else if (m.isNoteOff())
            isNotePlayed = false;
    }

    
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    sampleCount = isNotePlayed ? sampleCount += buffer.getNumSamples() : 0;
    
}

//==============================================================================
bool SamplerxAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SamplerxAudioProcessor::createEditor()
{
    return new SamplerxAudioProcessorEditor (*this);
}

//==============================================================================
void SamplerxAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SamplerxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SamplerxAudioProcessor();
}
void SamplerxAudioProcessor::loadFile()
{
    mySynth.clearSounds();
    juce::FileChooser chooser{ "Please Load A file" };
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        formatReader = formatManager.createReaderFor(file);
       
    }
    juce::BigInteger range;
    range.setRange(0,128,true);
    mySynth.addSound(new juce::SamplerSound("Sample",*formatReader,range,60,0.1,0.1,10.0));
}

void SamplerxAudioProcessor::loadFile(const juce::String& path)
{
    mySynth.clearSounds();
    auto file = juce::File(path);
    formatReader = formatManager.createReaderFor(file);
    waveForm.setSize(1, formatReader->lengthInSamples);
    formatReader->read(&waveForm, 0, formatReader->lengthInSamples, 0, true, false);
    auto buffer = waveForm.getReadPointer(0);
    for (int sample = 0; sample < waveForm.getNumSamples(); ++sample)
    {

    }
    juce::BigInteger range;
    range.setRange(0, 128, true);
    mySynth.addSound(new juce::SamplerSound("Sample", *formatReader, range, 60, 0.1, 0.1, 10.0));
}

void SamplerxAudioProcessor::getADSRParameters()
{
    adsrParameters.attack = *tree.getRawParameterValue("attack");
    adsrParameters.decay = *tree.getRawParameterValue("decay");
    adsrParameters.sustain = *tree.getRawParameterValue("sustain");
    adsrParameters.release = *tree.getRawParameterValue("release");
    for (int i = 0; i < mySynth.getNumSounds(); ++i)
    {
        if (auto sound = dynamic_cast<juce::SamplerSound*>(mySynth.getSound(i).get()))
        {
            sound->setEnvelopeParameters(adsrParameters);
        }

    }

}