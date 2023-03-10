/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ArcyBalanceAudioProcessorEditor::ArcyBalanceAudioProcessorEditor(ArcyBalanceAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.

	gainKnob.ColorInit(CCbase01(0.8f), CCbase3(1.0f), CCviolet(1.0f), CCbase01(1.0f));
	panKnob.ColorInit(CCbase01(0.8f), CCbase3(1.0f), CCviolet(1.0f), CCcyan(1.0f));

	addAndMakeVisible(gainKnob);
	addAndMakeVisible(panKnob);

	setSize(400, 200);
	setWantsKeyboardFocus(true);

	gainKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Gain", gainKnob);
	panKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Pan", panKnob);
}

ArcyBalanceAudioProcessorEditor::~ArcyBalanceAudioProcessorEditor() {}

void ArcyBalanceAudioProcessorEditor::paint(juce::Graphics& g) { g.fillAll(CCbase03(1.0f)); }

void ArcyBalanceAudioProcessorEditor::resized()
{
	gainKnob.setBounds((getWidth() / 4) - 90, getHeight() / 2 - 90, 180, 180);
	panKnob.setBounds((getWidth() / 4 * 3) - 90, getHeight() / 2 - 90, 180, 180);
}
