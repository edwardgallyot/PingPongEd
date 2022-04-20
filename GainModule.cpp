//
// Created by edgallyot on 07/03/2022.
//

#include "GainModule.h"

void GainModule::prepare (double sampleRate, int maximumExpectedSamplesPerBlock)
{
    smoothedValue.reset (sampleRate, 0.0005);
}
void GainModule::process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages, float gain)
{
    smoothedValue.setTargetValue (gain);
    for (auto sample = 0; sample < buffer.getNumSamples (); ++sample)
    {
        auto value = smoothedValue.getNextValue();
        for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            auto in = buffer.getSample(channel, sample);
            auto decibels = juce::Decibels::gainToDecibels (value);
            auto out = dsp(in, decibels);
            buffer.setSample (channel, sample, out);
        }
    }
}