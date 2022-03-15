//
// Created by edgallyot on 18/02/2022.
//

#ifndef DISTORTED_DISTORTEDSLIDER_H
#define DISTORTED_DISTORTEDSLIDER_H

#include "JuceHeader.h"
#include <atomic>
#include <string>
#include "PingPongEdProcessor.h"
#include "PingPongEdAlias.h"


class PingPongEdSlider : public juce::Component,
                        juce::Slider::Listener
{
public:
    PingPongEdSlider (juce::AudioProcessorValueTreeState& treeState, std::string ID, std::string Name);
    void resized () override;
protected:
    juce::AudioProcessorValueTreeState& parameters;
    std::string ID;
    std::string Name;
    juce::Slider m_slider;
    juce::Label m_labelValue;
    juce::Label m_labelName;
    std::unique_ptr<SliderAttachment> attachment;
private:
    void sliderValueChanged (juce::Slider* slider) override;
};


#endif //DISTORTED_DISTORTEDSLIDER_H
