#pragma once

#include <JuceHeader.h>
#include "BaseProcessor.h"
#include "id_name_vts.h"
#include "DelayModule.h"

//==============================================================================
class PingPongEdProcessor : public BaseProcessor
{
public:
    //==============================================================================
    PingPongEdProcessor ();
    ~PingPongEdProcessor () override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources () override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor () override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


private:

    std::vector<juce::String> m_ids {PPE_ID_LEFT,PPE_ID_RIGHT,  PPE_ID_FEEDBACK, PPE_ID_DRIVE,
                                     PPE_ID_HICUT, PPE_ID_LOCUT, PPE_ID_WOW,
                                     PPE_ID_FLUTTER, PPE_ID_MIX};

    std::vector<juce::String> m_names {PPE_NAME_LEFT, PPE_NAME_RIGHT, PPE_NAME_FEEDBACK, PPE_NAME_DRIVE,
                                       PPE_NAME_HICUT, PPE_NAME_LOCUT, PPE_NAME_WOW,
                                       PPE_NAME_FLUTTER, PPE_NAME_MIX};

    std::vector<float> m_minimums { PPE_MIN_LEFT, PPE_MIN_RIGHT, PPE_MIN_FEEDBACK, PPE_MIN_DRIVE,
                                   PPE_MIN_HICUT, PPE_MIN_LOCUT, PPE_MIN_WOW,
                                   PPE_MIN_FLUTTER, PPE_MIN_MIX};

    std::vector<float> m_maxes {PPE_MAX_LEFT, PPE_MAX_RIGHT,  PPE_MAX_FEEDBACK, PPE_MAX_DRIVE,
                                PPE_MAX_HICUT, PPE_MAX_LOCUT, PPE_MAX_WOW,
                                PPE_MAX_FLUTTER, PPE_MAX_MIX};

    std::vector<float> m_defaults {PPE_DEFAULT_LEFT, PPE_DEFAULT_RIGHT, PPE_DEFAULT_FEEDBACK, PPE_DEFAULT_DRIVE,
                                   PPE_DEFAULT_HICUT, PPE_DEFAULT_LOCUT, PPE_DEFAULT_WOW,
                                   PPE_DEFAULT_FLUTTER, PPE_DEFAULT_MIX};

    std::vector<std::atomic<float>*> m_parameters {9, nullptr};
    juce::AudioProcessorValueTreeState parameters;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout ();

    DelayModule delayModule;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PingPongEdProcessor)
};
