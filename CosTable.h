//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_COSTABLE_H
#define RAINGENERATOR_COSTABLE_H

#include <JuceHeader.h>

#include <cmath>
#include "Interpolate.h"

template<typename T>
class CosTable
{
public:
    explicit CosTable (size_t size)
            : max_index (size - 1), m_size (size)
    {
        data = new T[size];
        auto delta = juce::MathConstants<float>::twoPi / static_cast<float>(size);
        auto currentAngle = 0.0f;
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = cos (currentAngle);
            currentAngle += delta;
        }
    }

    void setFrequency (float frequency, float sampleRate)
    {
        auto tableSizeOverSampleRate = static_cast<float>(m_size) / sampleRate;
        tableDelta = frequency * tableSizeOverSampleRate;
    }

    float getNextSample ()
    {
        auto sample = interpolate_mod<float> (currentIndex, data, m_size);
        currentIndex += tableDelta;
        currentIndex = std::fmod (currentIndex, static_cast<float>(m_size));
        return sample;
    }

    size_t getMaxIndex () const
    {
        return max_index;
    }

    ~CosTable ()
    {
        delete data;
    }
private:
    T* data;
    size_t m_size;
    size_t max_index;
    float tableDelta;
    float currentIndex {0.0f};
};


#endif //RAINGENERATOR_COSTABLE_H
