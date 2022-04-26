//
// Created by edgallyot on 07/03/2022.
//

#include "CubicModule.h"

void CubicModule::prepare (double sampleRate, int maximumExpectedSamplesPerBlock)
{
    smoothedValue.reset (sampleRate, 0.0005);
}
void CubicModule::process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages, float& drive)
{
    smoothedValue.setTargetValue (drive);
    for (auto sample = 0; sample < buffer.getNumSamples (); ++sample)
    {
        auto value = smoothedValue.getNextValue();
        for (auto channel = 0; channel < buffer.getNumChannels (); ++channel)
        {
            auto in = buffer.getSample (channel, sample);
            auto value1 = value;
            auto value2 = value;
            auto value3 = value;
            auto value4 = value;
            auto gainCompensation = value;

            value1 *= 4.0f;
            value1 += 0.1f;

            value2 *= 3.0f;
            value2 += 0.1f;

            value3 *= 2.0f;
            value3 += 0.1f;

            value4 += 0.5f;

            float out = dsp (in, value1);

            for (int i = 0; i < 10; ++i)
                out = dsp (out, value1);

            for (int i = 0; i < 10; ++i)
                out = dsp (out, value2);

            for (int i = 0; i < 10; ++i)
                out = dsp (out, value3);

            for (int i = 0; i < 10; ++i)
                out = dsp (out, value4);

            buffer.setSample (channel, sample, DistortEdAlgorithms::scaleInDb (out * (1.0f + gainCompensation), 4.0f));
        }
    }
}
