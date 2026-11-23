
cmake_minimum_required(VERSION 3.22)

project(STUBE2B VERSION 1.0.0)

add_subdirectory(JUCE)

juce_add_plugin(STUBE2B
    COMPANY_NAME "STUBE2B"
    PLUGIN_MANUFACTURER_CODE StbB
    PLUGIN_CODE Stb2
    FORMATS VST3 Standalone
    PRODUCT_NAME "STUBE2B"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
)

juce_generate_juce_header(STUBE2B)

target_sources(STUBE2B
    PRIVATE
        PluginProcessor.cpp
        PluginProcessor.h
)

target_link_libraries(STUBE2B
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
