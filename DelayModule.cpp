//
// Created by edgallyot on 19/04/2022.
//

#include "DelayModule.h"


void DelayModule::prepare (double sampleRate, int maximumExpectedSamplesPerBlock,
                           std::vector<std::atomic<float>*>& parameters)
{
    m_samplesPerBlock = maximumExpectedSamplesPerBlock;
    m_sampleRate = sampleRate;

    auto bufferSize = circularBuffer.getSize ();

    readHeadLeft = bufferSize - parameters[DelayParameters::Left]->load ();
    readHeadRight = bufferSize - parameters[DelayParameters::Right]->load ();

    for (auto i = 0; i < VTS_PARAMS_N; ++i)
    {
        m_smoothedParameters[i].reset (sampleRate, 0.5f);
    }

    m_ms = sampleRate / 1000.0f;

    wowTable.setFrequency (2.0f, sampleRate);
    flutterTable.setFrequency (100.0f, sampleRate);
}
void DelayModule::process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,
                           std::vector<std::atomic<float>*>& parameters)
{
    auto bufferSize = circularBuffer.getSize ();

    for (auto sample = 0; sample < buffer.getNumSamples (); ++sample)
    {


        auto inLeft = buffer.getSample (0, sample);
        auto inRight = buffer.getSample (0, sample);

        auto leftDelayTime = m_smoothedParameters[DelayParameters::Left].getNextValue ();
        auto rightDelayTime = m_smoothedParameters[DelayParameters::Right].getNextValue ();

        auto currentMix = m_smoothedParameters[DelayParameters::Mix].getNextValue () / 100.0f;
        auto currentFeedback = m_smoothedParameters[DelayParameters::Feedback].getNextValue () / 100.0f;


        auto delaySampleLeft = circularBuffer.getSample (0, readHeadLeft);
        auto delaySampleRight = circularBuffer.getSample (1, readHeadRight);


        circularBuffer.writeSample (0, static_cast<size_t>(writeHeadLeft),
                                    inLeft + (currentFeedback * delaySampleRight));
        circularBuffer.writeSample (1, static_cast<size_t>(writeHeadRight),
                                    inRight + (currentFeedback * delaySampleLeft));

        readHeadLeft = fmod (
                bufferSize - m_smoothedParameters[DelayParameters::Left].getNextValue () * m_ms + writeHeadLeft,
                bufferSize - 1);
        readHeadRight = fmod (
                bufferSize - m_smoothedParameters[DelayParameters::Right].getNextValue () * m_ms + writeHeadRight,
                bufferSize - 1);

        writeHeadLeft += 1.0f;
        writeHeadRight += 1.0f;
        writeHeadLeft = fmod (writeHeadLeft, bufferSize - 1);
        writeHeadRight = fmod (writeHeadRight, bufferSize - 1);

        auto outLeft = currentMix * delaySampleLeft + (1 - currentMix) * inLeft;
        auto outRight = currentMix * delaySampleRight + (1 - currentMix) * inRight;

        buffer.setSample (0, sample, outLeft);
        buffer.setSample (1, sample, outRight);

    }
}
void DelayModule::setParameters (std::vector<std::atomic<float>*>& m_parameters)
{
    for (size_t i = 0; i < VTS_PARAMS_N; ++i)
    {
        m_smoothedParameters[i].setTargetValue (m_parameters[i]->load ());
    }
}
