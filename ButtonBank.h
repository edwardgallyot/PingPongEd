//
// Created by edgallyot on 14/03/2022.
//

#ifndef PINGPONGED_BUTTONBANK_H
#define PINGPONGED_BUTTONBANK_H

#include "PingPongEdButton.h"
#include "PingPongEdProcessor.h"
#include <JuceHeader.h>


class ButtonBank : public juce::Component
{
public:
    ButtonBank (PingPongEdProcessor& p, juce::AudioProcessorValueTreeState& vts,
                std::vector<std::string> idName1, std::vector<std::string> idName2
    );
    void resized () override;
private:
    PingPongEdProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;
    PingPongEdButton button1;
    PingPongEdButton button2;


};


#endif //PINGPONGED_BUTTONBANK_H
