/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Knob.h"

class ArcyBalanceAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
	ArcyBalanceAudioProcessorEditor(ArcyBalanceAudioProcessor&);
	~ArcyBalanceAudioProcessorEditor() override;
	void paint(juce::Graphics&) override;
	void resized() override;

private:
	Knob gainKnob, panKnob;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainKnobAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panKnobAttachment;

	ArcyBalanceAudioProcessor& audioProcessor;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArcyBalanceAudioProcessorEditor)
};