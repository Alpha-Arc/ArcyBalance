/*
  ==============================================================================

	Knob.cpp
	Created: 3 Mar 2023 6:50:01pm
	Author:  33067

  ==============================================================================
*/

#include "Knob.h"
#include "Palette.h"



Knob::Knob()
{
	setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
	setRotaryParameters(juce::MathConstants<float>::pi * 1.25f, juce::MathConstants<float>::pi * 2.75f, true);
	setVelocityBasedMode(true);
	setVelocityModeParameters(0.5, 1, 0.09, false);
	setRange(0.0, 100.0, 0.12);
	setLookAndFeel(&customLookAndFeel);
	setWantsKeyboardFocus(true);
	setColour(juce::Slider::textBoxTextColourId, CCbase01);
	setColour(juce::Slider::textBoxOutlineColourId, CCbase3);
};
Knob::~Knob() {};

void Knob::paint(juce::Graphics& g)
{
	juce::Slider::paint(g);

	if (hasKeyboardFocus(false))
	{
		float length = getHeight() > 15 ? 5.0f : 4.0f;
		float thick = getHeight() > 15 ? 3.0f : 2.5f;

		g.setColour(findColour(juce::Slider::textBoxOutlineColourId));

		//          fromX       fromY        toX                  toY
		g.drawLine(0, 0, 0, length, thick);
		g.drawLine(0, 0, length, 0, thick);
		g.drawLine(0, getHeight(), 0, getHeight() - length, thick);
		g.drawLine(0, getHeight(), length, getHeight(), thick);
		g.drawLine(getWidth(), getHeight(), getWidth() - length, getHeight(), thick);
		g.drawLine(getWidth(), getHeight(), getWidth(), getHeight() - length, thick);
		g.drawLine(getWidth(), 0, getWidth() - length, 0, thick);
		g.drawLine(getWidth(), 0, getWidth(), length, thick);
	}
}

void Knob::mouseDown(const juce::MouseEvent& event)
{
	juce::Slider::mouseDown(event);

	setMouseCursor(juce::MouseCursor::NoCursor);
}

void Knob::mouseUp(const juce::MouseEvent& event)
{
	juce::Slider::mouseUp(event);

	juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(event.source.getLastMouseDownPosition());

	setMouseCursor(juce::MouseCursor::NormalCursor);
}