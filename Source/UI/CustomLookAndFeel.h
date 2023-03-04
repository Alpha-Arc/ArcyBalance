/*
  ==============================================================================

	CustomLookAndFeel.h
	Created: 3 Mar 2023 10:17:33pm
	Author:  33067

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

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
