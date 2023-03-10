/*
  ==============================================================================

	Knob.cpp
	Created: 3 Mar 2023 6:50:01pm
	Author:  33067

  ==============================================================================
*/

#include "Knob.h"


Knob::Knob()
{
	setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
	setRotaryParameters(juce::MathConstants<float>::pi * 1.25f, juce::MathConstants<float>::pi * 2.75f, true);
	setVelocityBasedMode(true);
	setVelocityModeParameters(0.5, 1, 0.09, false);
	setRange(0.0, 100.0, 0.12);
	setLookAndFeel(&customLookAndFeel);
	setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
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

void Knob::ColorInit(juce::Colour textBoxTextColour, juce::Colour textBoxOutlineColour, juce::Colour rotarySliderFillColour, juce::Colour rotarySliderOutlineColour)
{
	Knob::setColour(juce::Slider::textBoxTextColourId, textBoxTextColour);
	Knob::setColour(juce::Slider::textBoxOutlineColourId, textBoxOutlineColour);
	Knob::setColour(juce::Slider::rotarySliderFillColourId, rotarySliderFillColour);
	Knob::setColour(juce::Slider::rotarySliderOutlineColourId, rotarySliderOutlineColour);
}



CustomLookAndFeel::CustomLookAndFeel() {};
CustomLookAndFeel::~CustomLookAndFeel() {};

juce::Slider::SliderLayout CustomLookAndFeel::getSliderLayout(juce::Slider& slider)
{
	auto localBounds = slider.getLocalBounds();

	juce::Slider::SliderLayout layout;

	layout.textBoxBounds = localBounds;
	layout.sliderBounds = localBounds;

	return layout;
}
//定义了旋钮的位置、大小和中央的文本框
//drawRotarySlider()函数对这个旋钮的影响是很大的，他确保了旋钮在缩放时不会变形，绘制了旋钮背后正方型的四个角，同时让旋钮的角度与数值相关联
void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
	auto bounds = juce::Rectangle<float>(x, y, width, height).reduced(2.0f);
	auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
	auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto lineW = radius * 0.04f;
	auto arcRadius = radius - lineW * 1.6f;

	juce::Path backgroundArc;
	backgroundArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, toAngle, rotaryEndAngle, true);
	g.setColour(slider.findColour(juce::Slider::rotarySliderOutlineColourId));
	g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

	juce::Path valueArc;
	valueArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, toAngle, true);
	g.setColour(slider.findColour(juce::Slider::rotarySliderFillColourId));
	g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

	g.setColour(CCbase3(1.0f));
	g.fillEllipse(bounds.reduced(radius * 0.2));
}

juce::Label* CustomLookAndFeel::createSliderTextBox(juce::Slider& slider)
{
	auto* l = new juce::Label();
	//l->setFont(50.0f);
	//l->setJustificationType(juce::Justification::centred);
	//l->setColour(juce::Label::textColourId, slider.findColour(juce::Slider::textBoxTextColourId));
	//l->setColour(juce::Label::textWhenEditingColourId, slider.findColour(juce::Slider::textBoxTextColourId));
	l->setColour(juce::Label::outlineWhenEditingColourId, slider.findColour(juce::Slider::textBoxOutlineColourId));
	//l->setInterceptsMouseClicks(false, false);
	//如果这个函数没有被设定为false，那么你将无法在文本框上拖拽，如果此时文本框在旋钮中央的话，这会是一个非常致命的问题。
	return l;
}