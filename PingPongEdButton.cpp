//
// Created by edgallyot on 06/03/2022.
//

#include "PingPongEdButton.h"

PingPongEdButton::PingPongEdButton (juce::AudioProcessorValueTreeState& treeState, std::string ID, std::string Name) :
        parameters (treeState),
        ID (ID),
        Name (Name)
{
    m_button.setClickingTogglesState (true);
    addAndMakeVisible (m_button);
    m_labelName.setText (this->Name, juce::dontSendNotification);
    addAndMakeVisible (m_labelName);
    attachment = std::make_unique<ButtonAttachment> (treeState, this->ID, m_button);
}

void PingPongEdButton::buttonClicked (juce::Button* button)
{

}

void PingPongEdButton::resized ()
{
    auto buttonArea = getLocalBounds ();
    auto labelArea = getLocalBounds ();
    labelArea.removeFromTop (getHeight () / 3);
    buttonArea.removeFromBottom (getHeight () / 3);
    labelArea.removeFromLeft (5);
    labelArea.removeFromTop (40);
    m_button.setBounds (buttonArea);
    m_labelName.setBounds (labelArea);
}

