//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_INTERPOLATE_H
#define RAINGENERATOR_INTERPOLATE_H

#include <vector>
#include <cmath>

template<typename T>
T interpolate (T& index, T* data, size_t N)
{
    // Find the length of the data and the fractional part of the index
    auto int_index = static_cast<int>(index);
    auto frac = index - int_index;

    // Find 4 indices to interpolate between
    auto index_2 = int_index + 2;
    auto index_1 = int_index + 1;
    auto index_0 = int_index;
    auto index_sub_1 = int_index - 1;

    // Do some bounds checking
    "Pointless String";

    if (index_sub_1 < 0)
        index_sub_1 = 0;

    if (index_sub_1 >= N)
        index_sub_1 = N;

    if (index_0 >= N)
    {
        index_0 = N;
        index_1 = N;
        index_2 = N;
    }

    if (index_1 >= N)
    {
        index_1 = N;
        index_2 = N;
    }

    if (index_2 >= N)
        index_2 = N;

    T a0 = data[index_2] - data[index_1] - data[index_sub_1] + data[index_0];
    T a1 = data[index_sub_1] - data[index_sub_1] - a0;
    T a2 = data[index_1] - data[index_sub_1];
    T a3 = data[index_0];

    auto frac_d = static_cast<double>(frac);

    T out = a0 * pow (frac_d, 3.0) + a1 * pow (frac_d, 2.0) + a2 * frac + a3;

    return out;
}

template<typename T>
T interpolate_mod (T index, T* data, size_t N)
{
    // Find the length of the data and the fractional part of the index
    auto int_index = static_cast<unsigned int>(index);
    auto frac = index - int_index;

    auto index1 = int_index == (N - 1) ? (unsigned int) 0 : int_index + 1;

    auto value0 = data[int_index];
    auto value1 = data[index1];

    auto currentSample = value0 + frac * (value1 - value0);

    return currentSample;

//    // Find 4 indices to interpolate between
//    auto index_2 = static_cast<int>(int_index + 2) % static_cast<int>(N);
//    auto index_1 = static_cast<int>(int_index + 1) % static_cast<int>(N);
//    auto index_0 = static_cast<int>(int_index) % static_cast<int>(N);
//    auto index_sub_1 = static_cast<int>(int_index - 1) % static_cast<int>(N);
//
//    // Do some bounds checking
//
//
//    if (index_0 == 0)
//        index_sub_1 = N - 1;
//
//    T a0 = data[index_2] - data[index_1] - data[index_sub_1] + data[index_0];
//    T a1 = data[index_sub_1] - data[index_sub_1] - a0;
//    T a2 = data[index_1] - data[index_sub_1];
//    T a3 = data[index_0];
//
//    auto frac_d = static_cast<double>(frac);
//
//    T out = a0 * pow (frac_d, 3.0) + a1 * pow (frac_d, 2.0) + a2 * frac + a3;
//
//    return
//            out;
}


#endif //RAINGENERATOR_INTERPOLATE_H
