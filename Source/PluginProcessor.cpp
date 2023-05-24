/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace juce;

//==============================================================================
DistortionVSTver1AudioProcessor::DistortionVSTver1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

    state = new AudioProcessorValueTreeState(*this, nullptr);
    //
    //state->createAndAddParameter("drive", "Drive", "Drive", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.0, nullptr, nullptr );
    //state->createAndAddParameter("range", "Range", "Range", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.0, nullptr, nullptr );
    //state->createAndAddParameter("blend", "Blend", "Blend", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.0, nullptr, nullptr );
    //state->createAndAddParameter("volume", "Volume", "Volume", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.0, nullptr, nullptr );
    //
    //state->state = ValueTree("drive");
    //state->state = ValueTree("range");
    //state->state = ValueTree("blend");
    //state->state = ValueTree("volume");

}

DistortionVSTver1AudioProcessor::~DistortionVSTver1AudioProcessor()
{
}

//==============================================================================
const String DistortionVSTver1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionVSTver1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionVSTver1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionVSTver1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionVSTver1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionVSTver1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionVSTver1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionVSTver1AudioProcessor::setCurrentProgram (int index)
{
}

const String DistortionVSTver1AudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionVSTver1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DistortionVSTver1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistortionVSTver1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionVSTver1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DistortionVSTver1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

AudioProcessorValueTreeState& DistortionVSTver1AudioProcessor::getState() {
    return *state;
}


//==============================================================================
bool DistortionVSTver1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DistortionVSTver1AudioProcessor::createEditor()
{
    return new DistortionVSTver1AudioProcessorEditor (*this);
}

//==============================================================================
void DistortionVSTver1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);

}

void DistortionVSTver1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    
    if (tree.isValid()) {
        state->state = tree;
    }

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionVSTver1AudioProcessor();
}
