/*
  ==============================================================================

	Knob.h
	Created: 3 Mar 2023 6:50:09pm
	Author:  33067

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Palette.h"

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel();

	juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;

	void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, juce::Slider&) override;

	juce::Label* createSliderTextBox(juce::Slider& slider) override;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel);
};


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