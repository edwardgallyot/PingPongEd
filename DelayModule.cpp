//
// Created by edgallyot on 19/04/2022.
//

#include "DelayModule.h"

#include <cmath>


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
    flutterTable.setFrequency (20.0f, sampleRate);

    cubicModule.prepare (sampleRate, maximumExpectedSamplesPerBlock);
}

void DelayModule::process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,
                           std::vector<std::atomic<float>*>& parameters)
{
    auto bufferSize = circularBuffer.getSize ();

    for (auto sample = 0; sample < buffer.getNumSamples (); ++sample, ++m_t)
    {


        auto inLeft = buffer.getSample (0, sample);
        auto inRight = buffer.getSample (1, sample);

        auto leftDelayTime = m_smoothedParameters[DelayParameters::Left].getNextValue ();
        auto rightDelayTime = m_smoothedParameters[DelayParameters::Right].getNextValue ();

        auto currentFeedback = m_smoothedParameters[DelayParameters::Feedback].getNextValue () / 100.0f;


        auto flutterAmount = m_smoothedParameters[DelayParameters::Flutter].getNextValue () / 1000000.0f;
        auto wowAmount = m_smoothedParameters[DelayParameters::Wow].getNextValue () / 100000.0f;

        auto wow = (wowAmount * std::sin (juce::MathConstants<float>::twoPi * (2.0f / m_sampleRate) * m_t)) + 1.0f;
        auto flutter =
                flutterAmount * std::sin (juce::MathConstants<float>::twoPi * (27.5675f / m_sampleRate) * m_t) + 1.0f;

        auto leftIndex = fmod ((readHeadLeft * wow * flutter) - wowAmount - flutterAmount,
                               static_cast<float>(bufferSize - 1.0f));
        auto rightIndex = fmod ((readHeadRight * wow * flutter) - wowAmount - flutterAmount,
                                static_cast<float>(bufferSize - 1.0f ));


        auto delaySampleLeft = circularBuffer.getSample (0, leftIndex);
        auto delaySampleRight = circularBuffer.getSample (1, rightIndex);
        // DBG(wow);

        circularBuffer.writeSample (
                0, static_cast<size_t>(writeHeadLeft),
                inLeft + (currentFeedback * delaySampleRight));
        circularBuffer.writeSample (
                1, static_cast<size_t>(writeHeadRight),
                inRight + (currentFeedback * delaySampleLeft));

        readHeadLeft = std::fmod (
                bufferSize - (m_smoothedParameters[DelayParameters::Left].getNextValue () * m_ms) + writeHeadLeft,
                static_cast<float>(bufferSize));
        readHeadRight = std::fmod (
                bufferSize - (m_smoothedParameters[DelayParameters::Right].getNextValue () * m_ms) + writeHeadRight,
                static_cast<float>(bufferSize));

        writeHeadLeft += 1.0f;
        writeHeadRight += 1.0f;
        writeHeadLeft = std::fmod (writeHeadLeft, static_cast<float>(bufferSize));
        writeHeadRight = std::fmod (writeHeadRight, static_cast<float>(bufferSize));

        auto outLeft = delaySampleLeft;
        auto outRight = delaySampleRight;

        buffer.setSample (0, sample, outLeft);
        buffer.setSample (1, sample, outRight);

        if (m_t == 88200)
            m_t = 0;

    }
}

void DelayModule::setParameters (std::vector<std::atomic<float>*>& m_parameters)
{
    for (size_t i = 0; i < VTS_PARAMS_N; ++i)
    {
        m_smoothedParameters[i].setTargetValue (m_parameters[i]->load ());
    }
}
