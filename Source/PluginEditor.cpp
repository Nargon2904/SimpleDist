/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace juce;

//==============================================================================
SimpleDistAudioProcessorEditor::SimpleDistAudioProcessorEditor (SimpleDistAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);


    //DriveSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    //DriveSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    //DriveSlider.setRange(-48.0, 0.0);
    //DriveSlider.setValue(-1.0);
    //DriveSlider.addListener(this);
    //addAndMakeVisible(gainVolumeSlider);
    //
    //RangeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    //DriveSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    //DriveSlider.setRange(-48.0, 0.0);
    //DriveSlider.setValue(0.0);
    //DriveSlider.addListener(this);
    //addAndMakeVisible(gainVolumeSlider);
    //
    //BlendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    //gainVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    //gainVolumeSlider.setRange(-48.0, 0.0);
    //gainVolumeSlider.setValue(-1.0);
    //gainVolumeSlider.addListener(this);
    //addAndMakeVisible(gainVolumeSlider);

    gainVolumeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 70, 25);
    gainVolumeSlider.setRange(-48.0, 0.0);
    gainVolumeSlider.setValue(-1.0);
    gainVolumeSlider.addListener(this);
    addAndMakeVisible(gainVolumeSlider);
}

SimpleDistAudioProcessorEditor::~SimpleDistAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDistAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);


}

void SimpleDistAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //gainVolumeSlider.setBounds(getLocalBounds());
    gainVolumeSlider.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - 100, 100, 200);

}


void SimpleDistAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &gainVolumeSlider) {
        audioProcessor.rawVolume = pow(10, gainVolumeSlider.getValue() / 20);
    }
}