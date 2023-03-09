/*
  ==============================================================================

	Knob.h
	Created: 3 Mar 2023 6:50:09pm
	Author:  33067

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

class Knob : public juce::Slider
{
public:
	Knob();
	~Knob();

	void paint(juce::Graphics& g) override;
	void mouseDown(const juce::MouseEvent& event) override;
	void mouseUp(const juce::MouseEvent& event) override;
	void ColorInit(juce::Colour textBoxTextColour, juce::Colour textBoxOutlineColour, juce::Colour rotarySliderFillColour, juce::Colour rotarySliderOutlineColour);

private:
	CustomLookAndFeel customLookAndFeel;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};