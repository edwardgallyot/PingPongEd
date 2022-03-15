//
// Created by edgallyot on 14/03/2022.
//

#include "ButtonBank.h"

ButtonBank::ButtonBank (PingPongEdProcessor& p, juce::AudioProcessorValueTreeState& vts,
                        std::vector<std::string> idName1, std::vector<std::string> idName2) :
        processor (p),
        parameters (vts),
        button1 (parameters,
                 idName1[0],
                 idName1[1]),
        button2 (parameters,
                 idName2[0],
                 idName2[1])
{
    addAndMakeVisible (button1);
    addAndMakeVisible (button2);
}
void ButtonBank::resized ()
{
    auto area1 = getLocalBounds ();
    auto area2 = getLocalBounds ();

    area1.removeFromBottom (getHeight () / 2);
    area2.removeFromTop (getHeight () / 2);

    button1.setBounds (area1);
    button2.setBounds (area2);

}
