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
	), apvts(*this, nullptr, "Parameters", creatParameters())
#endif
{
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
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
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

	auto g0 = apvts.getRawParameterValue("Pan");
	auto g1 = apvts.getRawParameterValue("Gain");

	if (g0->load() == previousGain)
		buffer.applyGain(previousGain);
	else
		buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, g0->load()), previousGain = g0->load();

	/*
	if (g1->load() == previousPan)
		juce::setpan(previousPan)
	else
		buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, g0->load()), previousGain = g0->load();
	*/


	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());



	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);
	}
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

juce::AudioProcessorValueTreeState::ParameterLayout ArcyBalanceAudioProcessor::creatParameters()
{
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
	params.push_back(std::make_unique<juce::AudioParameterFloat>("Gain", "Gain", 0.0f, 1.0f, 1.0f));
	params.push_back(std::make_unique<juce::AudioParameterFloat>("Pan", "Pan", 0.0f, 1.0f, 0.5f));
	return { params.begin(),params.end() };
}