/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
using namespace juce;

//==============================================================================
/**
*/
class DistortionVSTver1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistortionVSTver1AudioProcessorEditor (DistortionVSTver1AudioProcessor&);
    ~DistortionVSTver1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    ScopedPointer<Slider> driveKnob;
    ScopedPointer<Slider> rangeKnob;
    ScopedPointer<Slider> blendKnob;
    ScopedPointer<Slider> volumeKnob;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionVSTver1AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionVSTver1AudioProcessorEditor)
};
