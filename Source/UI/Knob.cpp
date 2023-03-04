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
};
Knob::~Knob() {};

void Knob::paint(juce::Graphics& g)
{
	juce::Slider::paint(g);

	if (hasKeyboardFocus(false))
	{
		float L(getHeight() > 15 ? 5.0f : 4.0f), T(getHeight() > 15 ? 3.0f : 2.5f), H(getHeight()), W(getWidth());
		g.setColour(findColour(juce::Slider::textBoxOutlineColourId));

		//          fromX       fromY        toX                  toY
		g.drawLine(0, 0, 0, L, T);
		g.drawLine(0, 0, L, 0, T);
		g.drawLine(0, H, 0, H - L, T);
		g.drawLine(0, H, L, H, T);
		g.drawLine(W, H, W - L, H, T);
		g.drawLine(W, H, W, H - L, T);
		g.drawLine(W, 0, W - L, 0, T);
		g.drawLine(W, 0, W, L, T);
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