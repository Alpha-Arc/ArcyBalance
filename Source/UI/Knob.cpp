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
//��������ť��λ�á���С��������ı���
//drawRotarySlider()�����������ť��Ӱ���Ǻܴ�ģ���ȷ������ť������ʱ������Σ���������ť���������͵��ĸ��ǣ�ͬʱ����ť�ĽǶ�����ֵ�����
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
	//����������û�б��趨Ϊfalse����ô�㽫�޷����ı�������ק�������ʱ�ı�������ť����Ļ��������һ���ǳ����������⡣
	return l;
}