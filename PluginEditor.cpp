
#include "PluginEditor.h"

STUBE2BAudioProcessorEditor::STUBE2BAudioProcessorEditor(
    STUBE2BAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setupKnob(thresholdKnob, "THRESHOLD");
    setupKnob(ratioKnob, "RATIO");
    setupKnob(attackKnob, "ATTACK");
    setupKnob(releaseKnob, "RELEASE");
    setupKnob(outputKnob, "OUTPUT");
    setupKnob(mixKnob, "MIX");

    thresholdAttachment = std::make_unique<SliderAttachment>(
        audioProcessor.parameters, "THRESHOLD", thresholdKnob);

    ratioAttachment = std::make_unique<SliderAttachment>(
        audioProcessor.parameters, "RATIO", ratioKnob);

    attackAttachment = std::make_unique<SliderAttachment>(
        audioProcessor.parameters, "ATTACK", attackKnob);

    releaseAttachment = std::make_unique<SliderAttachment>(
        audioProcessor.parameters, "RELEASE", releaseKnob);

    outputAttachment = std::make_unique<SliderAttachment>(
        audioProcessor.parameters, "OUTPUT", outputKnob);

    mixAttachment = std::make_unique<SliderAttachment>(
        audioProcessor.parameters, "MIX", mixKnob);

    setSize(1200, 400);
}

void STUBE2BAudioProcessorEditor::setupKnob(
    juce::Slider& knob, const juce::String& name)
{
    addAndMakeVisible(knob);

    knob.setName(name);
    knob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    knob.setColour(juce::Slider::rotarySliderFillColourId,
                   juce::Colours::darkred);
    knob.setColour(juce::Slider::thumbColourId,
                   juce::Colours::black);
}

void STUBE2BAudioProcessorEditor::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    juce::ColourGradient metal(
        juce::Colour(220, 220, 210), 0.0f, 0.0f,
        juce::Colour(145, 148, 145), 0.0f,
        false);

    metal.addColour(0.5, juce::Colour(190, 190, 180));
    g.setGradientFill(metal);
    g.fillAll();

    g.setColour(juce::Colour(70, 65, 60));
    g.drawRect(bounds, 4.0f);

    g.setColour(juce::Colour(105, 0, 15));
    g.setFont(juce::Font(42.0f, juce::Font::bold));
    g.drawText("STUBE 2B",
               25, 65, 280, 55,
               juce::Justification::left);

    g.setColour(juce::Colours::black);
    g.setFont(juce::Font(19.0f, juce::Font::bold));
    g.drawText("COMPRESSOR  CL 1B",
               28, 120, 280, 30,
               juce::Justification::left);

    g.setFont(juce::Font(16.0f));
    g.drawText("LYDKRAFT  DENMARK",
               28, 155, 280, 25,
               juce::Justification::left);

    g.setFont(juce::Font(15.0f, juce::Font::bold));

    g.drawText("OUTPUT VOLUME", 300, 205, 130, 25,
               juce::Justification::centred);
    g.drawText("RATIO", 470, 205, 130, 25,
               juce::Justification::centred);
    g.drawText("THRESHOLD", 640, 205, 130, 25,
               juce::Justification::centred);
    g.drawText("ATTACK", 300, 360, 130, 25,
               juce::Justification::centred);
    g.drawText("RELEASE", 470, 360, 130, 25,
               juce::Justification::centred);
    g.drawText("PARALLEL COMPRESSION", 640, 360, 200, 25,
               juce::Justification::centred);

    // Vintage-style VU meter housing
    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(870.0f, 35.0f, 290.0f, 155.0f, 8.0f);

    g.setColour(juce::Colour(255, 183, 75));
    g.fillRoundedRectangle(880.0f, 45.0f, 270.0f, 135.0f, 5.0f);

    g.setColour(juce::Colours::black);
    g.setFont(juce::Font(25.0f, juce::Font::italic));
    g.drawText("LYDKRAFT", 900, 105, 230, 35,
               juce::Justification::centred);

    g.setFont(juce::Font(16.0f, juce::Font::bold));
    g.drawText("VU", 1100, 150, 35, 20,
               juce::Justification::centred);
}

void STUBE2BAudioProcessorEditor::resized()
{
    outputKnob.setBounds(300, 65, 130, 130);
    ratioKnob.setBounds(470, 65, 130, 130);
    thresholdKnob.setBounds(640, 65, 130, 130);

    attackKnob.setBounds(300, 220, 130, 130);
    releaseKnob.setBounds(470, 220, 130, 130);
    mixKnob.setBounds(680, 230, 110, 110);
}
