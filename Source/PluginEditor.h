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
class SimpleDistAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                        public Slider::Listener
{
public:
    SimpleDistAudioProcessorEditor (SimpleDistAudioProcessor&);
    ~SimpleDistAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDistAudioProcessor& audioProcessor;

    Slider DriveSlider;
    Slider RangeSlider;
    Slider BlendSlider;
    Slider gainVolumeSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDistAudioProcessorEditor)
};
