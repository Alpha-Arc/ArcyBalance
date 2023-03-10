/*
  ==============================================================================

	CustomLookAndFeel.cpp
	Created: 3 Mar 2023 10:17:33pm
	Author:  33067

  ==============================================================================
*/

#include "CustomLookAndFeel.h"
#include "Palette.h"

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