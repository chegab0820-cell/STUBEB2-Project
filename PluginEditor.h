
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class STUBE2BAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit STUBE2BAudioProcessorEditor(STUBE2BAudioProcessor&);
    ~STUBE2BAudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    STUBE2BAudioProcessor& audioProcessor;

    juce::Slider thresholdKnob;
    juce::Slider ratioKnob;
    juce::Slider attackKnob;
    juce::Slider releaseKnob;
    juce::Slider outputKnob;
    juce::Slider mixKnob;

    juce::Label titleLabel;
    juce::Label subtitleLabel;

    using SliderAttachment =
        juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> thresholdAttachment;
    std::unique_ptr<SliderAttachment> ratioAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    std::unique_ptr<SliderAttachment> outputAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;

    void setupKnob(juce::Slider&, const juce::String&);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
        STUBE2BAudioProcessorEditor
    )
};
