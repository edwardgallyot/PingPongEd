//
// Created by edgallyot on 14/03/2022.
//

#include "SliderBank.h"
#include "id_name_vts.h"

SliderBank::SliderBank (PingPongEdProcessor& p, juce::AudioProcessorValueTreeState& vts,
                        std::vector<std::string> idName1, std::vector<std::string> idName2) :
        processor (p),
        parameters (vts),
        slider1 (parameters,
                 idName1[0],
                 idName1[1]),
        slider2 (parameters,
                 idName2[0],
                 idName2[1])
{
    addAndMakeVisible (slider1);
    addAndMakeVisible (slider2);
}
void SliderBank::resized ()
{
    auto area1 = getLocalBounds ();
    auto area2 = getLocalBounds ();

    area1.removeFromBottom (getHeight () / 2);
    area2.removeFromTop (getHeight () / 2);

    slider1.setBounds (area1);
    slider2.setBounds (area2);
}
