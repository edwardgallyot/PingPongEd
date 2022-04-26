//
// Created by edgallyot on 19/04/2022.
//

#ifndef PINGPONGED_DELAYMODULE_H
#define PINGPONGED_DELAYMODULE_H

#include "CircularBuffer.h"
#include <JuceHeader.h>
#include "id_name_vts.h"
#include "CosTable.h"

class DelayModule
{
public:
    void prepare (double sampleRate, int maximumExpectedSamplesPerBlock,
                  std::vector<std::atomic<float>*>& parameters);
    void setParameters (std::vector<std::atomic<float>*>& m_parameters);
    void process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages,
                  std::vector<std::atomic<float>*>& parameters);

private:
    juce::LinearSmoothedValue<float> m_smoothedParameters[VTS_PARAMS_N] = {{0.0f},
                                                                           {0.0f},
                                                                           {0.0f},
                                                                           {0.0f},
                                                                           {0.0f},
                                                                           {0.0f},
                                                                           {0.0f},
                                                                           {0.0f},
                                                                           {0.0f}};
    CircularBuffer<float> circularBuffer {44100 * 6};
    double m_sampleRate {0.0f};
    int m_samplesPerBlock {0};
    float writeHeadLeft {0.0f};
    float writeHeadRight {0.0f};
    float readHeadLeft {0.0f};
    float readHeadRight {0.0f};
    float m_ms {0.0f};
    CosTable<float> wowTable{100000};
    CosTable<float> flutterTable{100000};


};


#endif //PINGPONGED_DELAYMODULE_H
