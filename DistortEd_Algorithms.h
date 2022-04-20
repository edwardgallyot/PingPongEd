//
// Created by edgallyot on 01/03/2022.
//

#pragma once

#if 0

BEGIN_JUCE_MODULE_DECLARATION

      ID:               DistortEd_Algorithmslib
      vendor:           Ed Gallyot
      version:          0.0.1
      name:             DistortEd_Algorithmslib
      description:      Shared processing functions
      license:          GPL/Commercial
      dependencies:     juce_audio_utils

     END_JUCE_MODULE_DECLARATION

#endif

#ifndef WAVE_IO_DISTORTED_ALGORITHMS_H
#define WAVE_IO_DISTORTED_ALGORITHMS_H

#include <iostream>
#include <cmath>

#define TWO_OVER_PI (2 / M_PI)
#define HALF_PI (M_PI * 0.5f)

// Most of these algorithms are implemented
// from Eric Tarrs book Hack Audio
// The Matlab Algorithms have been converted to C++ functions
// Because of the element wise processing
// they are simple to call in the process block on each sample
// Any parameter changes can be smoothed within the
// Process block by applying ramps

namespace DistortEdAlgorithms {
    template<typename T>
    T sign (T in)
    {
        return (static_cast<T>(0) < in) - (in < static_cast<T>(0));
    }

    template<typename T>
    T diodeClip(T in){
        T out;
        auto thermalVoltage = 0.0253f;
        auto emissionCoefficient = 1.68f;
        auto saturationCurrent = 0.105f;

        out = saturationCurrent * (exp(0.1f * in / (emissionCoefficient * thermalVoltage)) -1);
        return out;
    }

    template<typename T>
    T dcOffsetClip (T in, float dcOffset)
    {
        T out {0.0f};
        auto x = in + dcOffset;
        auto absoluteIn = abs (x);

        if (absoluteIn > 1)
            x = sign(x);

        out = x - ((1.0f / 5.0f) * pow(static_cast<double>(x), 5.0f));

        return static_cast<T>(out - dcOffset);
    }

    template<typename T>
    T processPieceWiseClip (T in)
    {
        T out;
        auto absoluteIn = abs (in);
        auto third = static_cast<T>(1.0f / 3.0f);
        if (absoluteIn <= third)
            out = 2 * in;
        else if (absoluteIn > (2 * third))
            out = sign (in);
        else
            out = sign (in) * (3.0f - (2.0f - (3 * pow (absoluteIn, 2.0f)))) / 3.0f;
        return out;
    }

    template<typename T>
    T processSineClip (T in)
    {
        T out;
        out = sin (HALF_PI * in);
        return out;
    }

    template<typename T>
    T processBitClip (T in, float bits)
    {
        // bits should be between 1 and 16
        T out;
        auto ampValues = pow (static_cast<double>(2.0f), static_cast<double>(bits));
        T tmpIn = (0.5f * in) + 0.5f;
        T scaleInput = static_cast<T>(ampValues) * tmpIn;
        T roundInput = round (scaleInput);
        T prepOut = roundInput / ampValues;
        out = (2.0f * prepOut) - 1.0f;
        return out;
    }

    template<typename T>
    T processArcTanClip (T in, float coeff)
    {
        // coeff should be between 1 and 10
        T out = TWO_OVER_PI * atan (static_cast<double>(in * coeff));
        return out;
    }

    template<typename T>
    T processExponentialClip (T in, float coeff)
    {
        // coeff should be between 1 and 10
        T out = sign (in) * (1 - std::exp (-1.0f * std::abs (coeff * in)));
        return out;
    }

    template<typename T>
    T processInfiniteClip (T in)
    {
        T out;
        if (in >= 0)
            return static_cast<T>(1.0f);
        else
            return static_cast<T>(-1.0f);
    }

    template<typename T>
    T processFullWaveRect (T in)
    {
        T out;
        if (in >= 0)
            out = in;
        else
            out = -1.0f * in;
        return out;
    }

    template<typename T>
    T processHalfWaveRect (T in)
    {
        T out;
        if (in >= 0)
            out = in;
        else
            out = 0.0f;
        return out;
    }

    template<typename T>
    T scaleInDb (T in, float dbChange)
    {
        auto scale = pow (10.0f, static_cast<double>(dbChange / 20.0f));
        return static_cast<T>(scale * in);
    }

    template<typename T>
    T processHardClip (T in, float threshold)
    {
        // threshold should be between 0 and 1
        T out;
        auto lo_threshold = static_cast<T>(0 - threshold);
        if (in > threshold)
        {
            out = threshold;
        } else if (in <= lo_threshold)
        {
            out = lo_threshold;
        } else
        {
            out = in;
        }
        return out;
    }

    template<typename T>
    T processCubicClip (T in, float alpha)
    {
        // alpha should be between 0 and 1
        auto coefficient = alpha * static_cast<double>(1.0f / 3.0f);
        T out = static_cast<T>(in - (coefficient * pow (static_cast<double>(in), 3.0f)));
        return out;
    }
}

#endif //WAVE_IO_DISTORTED_ALGORITHMS_H
