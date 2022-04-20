//
// Created by edgallyot on 08/03/2022.
//

#ifndef DISTORTED_LOWPASSMODULE_H
#define DISTORTED_LOWPASSMODULE_H

#include <JuceHeader.h>

using namespace juce::dsp;

class LowPassModule
{
public:
    LowPassModule () = default;
    void prepare (double sampleRate, unsigned int samplesPerBlock, unsigned int numChannels);
    void process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages, float cutoff);
private:
    double sampleRate{0.0f};
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> smoothedValue;
    ProcessorDuplicator<StateVariableFilter::Filter<float>, StateVariableFilter::Parameters<float>> stateVariableFilter;
};

#endif //DISTORTED_LOWPASSMODULE_H