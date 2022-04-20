//
// Created by edgallyot on 07/03/2022.
//

#ifndef DISTORTED_GAINMODULE_H
#define DISTORTED_GAINMODULE_H

#include "juce_audio_utils/juce_audio_utils.h"
#include "juce_gui_extra/juce_gui_extra.h"
#include "DistortEd_Algorithms.h"

class GainModule
{
public:
    GainModule() = default;
    void prepare (double sampleRate, int maximumExpectedSamplesPerBlock);
    void process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages, float gain);
private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> smoothedValue;
    float (& dsp) (float, float) = DistortEdAlgorithms::scaleInDb<float>;
};


#endif //DISTORTED_GAINMODULE_H
