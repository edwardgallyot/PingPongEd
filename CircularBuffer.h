//
// Created by edgallyot on 19/04/2022.
//

#ifndef PINGPONGED_CIRCULARBUFFER_H
#define PINGPONGED_CIRCULARBUFFER_H

#include <cstddef>
#include "Interpolate.h"

template<typename T>
class CircularBuffer
{
public:
    CircularBuffer (size_t size) : m_size (size)
    {
        m_data = new T* [2];
        m_data[0] = new T[size];
        m_data[1] = new T[size];
    };

    void writeSample (int channel, size_t position, T sample)
    {
        m_data[channel][position] = sample;
    };

    T getSample (int channel, float position)
    {
        auto sample = interpolate_mod<float> (position, m_data[channel], m_size);
        return sample;
    };

    size_t getSize ()
    {
        return m_size;
    };

    ~CircularBuffer ()
    {
        delete[] m_data[0];
        delete[] m_data[1];
        delete[] m_data;
    };
private:
    T** m_data;
    size_t m_size;
};


#endif //PINGPONGED_CIRCULARBUFFER_H
