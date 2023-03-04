/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ArcyBalanceAudioProcessor::ArcyBalanceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	), apvts(*this, nullptr, "Parameters", creatParameterLayout())
#endif
{
	mGain.setGainLinear(0.0f);
	mGain.setRampDurationSeconds(0.05);
	mPanner.setRule(juce::dsp::PannerRule::squareRoot3dB);
	mPanner.setPan(0.0f);
}

ArcyBalanceAudioProcessor::~ArcyBalanceAudioProcessor()
{
}

//==============================================================================
const juce::String ArcyBalanceAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool ArcyBalanceAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool ArcyBalanceAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool ArcyBalanceAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double ArcyBalanceAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int ArcyBalanceAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int ArcyBalanceAudioProcessor::getCurrentProgram()
{
	return 0;
}

void ArcyBalanceAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String ArcyBalanceAudioProcessor::getProgramName(int index)
{
	return {};
}

void ArcyBalanceAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void ArcyBalanceAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = 2;
	mGain.prepare(spec);
	mPanner.prepare(spec);
}

void ArcyBalanceAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ArcyBalanceAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void ArcyBalanceAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i(totalNumInputChannels); i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());
	
	mGain.setGainLinear(*apvts.getRawParameterValue("Gain"));
	mPanner.setPan(*apvts.getRawParameterValue("Pan"));
	juce::dsp::AudioBlock<float> block(buffer);
	juce::dsp::ProcessContextReplacing<float> context(block);
	mPanner.process(context);
	mGain.process(context);
}

//==============================================================================
bool ArcyBalanceAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ArcyBalanceAudioProcessor::createEditor()
{
	return new ArcyBalanceAudioProcessorEditor(*this);
}

//==============================================================================
void ArcyBalanceAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void ArcyBalanceAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new ArcyBalanceAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout ArcyBalanceAudioProcessor::creatParameterLayout()
{
	juce::AudioProcessorValueTreeState::ParameterLayout layout;
	layout.add(std::make_unique<juce::AudioParameterFloat>("Gain", "Gain", 0.0f, 1.0f, 1.0f));
	layout.add(std::make_unique<juce::AudioParameterFloat>("Pan", "Pan", -1.0f, 1.0f, 0.0f));
	return layout;
}