//
// Created by edgallyot on 14/03/2022.
//

#ifndef PINGPONGED_SLIDERBANK_H
#define PINGPONGED_SLIDERBANK_H

#include <JuceHeader.h>
#include <atomic>
#include "PingPongEdProcessor.h"
#include "PingPongEdSlider.h"

class SliderBank : public juce::Component
{
public:
    SliderBank (PingPongEdProcessor& p, juce::AudioProcessorValueTreeState& vts,
                std::vector<std::string> idName1, std::vector<std::string> idName2);
    void resized() override;
private:
    PingPongEdProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;
    PingPongEdSlider slider1;
    PingPongEdSlider slider2;
};


#endif //PINGPONGED_SLIDERBANK_H
