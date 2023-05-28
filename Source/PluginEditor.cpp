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
    setSize (500, 200);


    DriveSlider.setSliderStyle(Slider::Rotary);
    //DriveSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    DriveSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    DriveSlider.setRange(0.0, 1.0);
    DriveSlider.setValue(0.5);
    DriveSlider.addListener(this);
    addAndMakeVisible(DriveSlider);

    
    RangeSlider.setSliderStyle(Slider::Rotary);
    RangeSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    RangeSlider.setRange(0.0, 300.0);
    RangeSlider.setValue(20.0);
    RangeSlider.addListener(this);
    addAndMakeVisible(RangeSlider);


    BlendSlider.setSliderStyle(Slider::Rotary);
    BlendSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    BlendSlider.setRange(0.0, 1.0);
    BlendSlider.setValue(0.0);
    BlendSlider.addListener(this);
    addAndMakeVisible(BlendSlider);


    gainVolumeSlider.setSliderStyle(Slider::Rotary);
    gainVolumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    gainVolumeSlider.setRange(0.0, 2.0);
    gainVolumeSlider.setValue(1.0);
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


    g.drawText("Drive", ((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) + 5, 100, 100, Justification::centred, false);
    g.drawText("Range", ((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) + 5, 100, 100, Justification::centred, false);
    g.drawText("Blend", ((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) + 5, 100, 100, Justification::centred, false);
    g.drawText("Volume", ((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) + 5, 100, 100, Justification::centred, false);


}

void SimpleDistAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //gainVolumeSlider.setBounds(getLocalBounds());

    DriveSlider.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    RangeSlider.setBounds(((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    BlendSlider.setBounds(((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);
    gainVolumeSlider.setBounds(((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) - (100 / 2), 100, 100);

}


void SimpleDistAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &gainVolumeSlider) {
        //audioProcessor.rawVolume = pow(10, gainVolumeSlider.getValue() / 20);
        audioProcessor.rawVolume = gainVolumeSlider.getValue();
    }
    if (slider == &DriveSlider) {
        audioProcessor.rawDrive = DriveSlider.getValue();
    }
    if (slider == &RangeSlider) {
        audioProcessor.rawRange = RangeSlider.getValue();
    }
    if (slider == &BlendSlider) {
        audioProcessor.rawBlend = BlendSlider.getValue();
    }
}
