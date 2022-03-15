#pragma once

#include "PingPongEdProcessor.h"
#include "SliderBank.h"
#include "ButtonBank.h"
#include "PingPongEdSlider.h"

//==============================================================================
class PingPongEdEditor  : public juce::AudioProcessorEditor
{
public:
    explicit PingPongEdEditor (PingPongEdProcessor& p, juce::AudioProcessorValueTreeState& vts);
    ~PingPongEdEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PingPongEdProcessor& processorRef;

    SliderBank sliderBank1;
    SliderBank sliderBank2;
    SliderBank sliderBank3;
    SliderBank sliderBank4;

    PingPongEdSlider mixSlider;

    ButtonBank buttonBank;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PingPongEdEditor)
};
