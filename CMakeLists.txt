
cmake_minimum_required(VERSION 3.22)

project(STUBE2B VERSION 1.0.0)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 9.0.6
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(JUCE)

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

target_compile_definitions(STUBE2B
    PUBLIC
        JUCE_VST3_CAN_REPLACE_VST2=0

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
