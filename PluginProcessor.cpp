
#include "PluginProcessor.h"

STUBE2BAudioProcessor::STUBE2BAudioProcessor()
    : AudioProcessor(
        BusesProperties()
            .withInput("Input", juce::AudioChannelSet::stereo(), true)
            .withOutput("Output", juce::AudioChannelSet::stereo(), true)
      ),
      parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

STUBE2BAudioProcessor::~STUBE2BAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout
STUBE2BAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "THRESHOLD", "Threshold",
        juce::NormalisableRange<float>(-60.0f, 0.0f), -18.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "RATIO", "Ratio",
        juce::NormalisableRange<float>(1.0f, 20.0f), 4.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "ATTACK", "Attack",
        juce::NormalisableRange<float>(1.0f, 200.0f), 10.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "RELEASE", "Release",
        juce::NormalisableRange<float>(10.0f, 1000.0f), 100.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "OUTPUT", "Output",
        juce::NormalisableRange<float>(-24.0f, 24.0f), 0.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "MIX", "Mix",
        juce::NormalisableRange<float>(0.0f, 100.0f), 100.0f));

    return layout;
}

void STUBE2BAudioProcessor::prepareToPlay(double, int)
{
}

void STUBE2BAudioProcessor::releaseResources()
{
}

void STUBE2BAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const float threshold = parameters.getRawParameterValue("THRESHOLD")->load();
    const float ratio = parameters.getRawParameterValue("RATIO")->load();
    const float output = parameters.getRawParameterValue("OUTPUT")->load();
    const float mix = parameters.getRawParameterValue("MIX")->load() / 100.0f;

    const float thresholdGain = juce::Decibels::decibelsToGain(threshold);
    const float outputGain = juce::Decibels::decibelsToGain(output);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* data = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            const float dry = data[sample];
            const float level = std::abs(dry);

            float wet = dry;

            if (level > thresholdGain)
            {
                const float compressedLevel =
                    thresholdGain + (level - thresholdGain) / ratio;

                wet = std::copysign(compressedLevel, dry);
            }

            wet *= outputGain;
            data[sample] = dry * (1.0f - mix) + wet * mix;
        }
    }
}

juce::AudioProcessorEditor* STUBE2BAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

bool STUBE2BAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String STUBE2BAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool STUBE2BAudioProcessor::acceptsMidi() const
{
    return false;
}

bool STUBE2BAudioProcessor::producesMidi() const
{
    return false;
}

bool STUBE2BAudioProcessor::isMidiEffect() const
{
    return false;
}

double STUBE2BAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int STUBE2BAudioProcessor::getNumPrograms()
{
    return 1;
}

int STUBE2BAudioProcessor::getCurrentProgram()
{
    return 0;
}

void STUBE2BAudioProcessor::setCurrentProgram(int)
{
}

const juce::String STUBE2BAudioProcessor::getProgramName(int)
{
    return {};
}

void STUBE2BAudioProcessor::changeProgramName(int, const juce::String&)
{
}

void STUBE2BAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void STUBE2BAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));

    if (xml != nullptr)
    {
        if (xml->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new STUBE2BAudioProcessor();
}
