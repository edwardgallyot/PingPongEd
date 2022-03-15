#include "PingPongEdProcessor.h"
#include "PingPongEdEditor.h"
#include "id_name_vts.h"

//==============================================================================
PingPongEdEditor::PingPongEdEditor (PingPongEdProcessor& p, juce::AudioProcessorValueTreeState& vts) :
        AudioProcessorEditor (&p),
        processorRef (p),
        sliderBank1 (p, vts, {PPE_ID_LEFT, PPE_NAME_LEFT}, {PPE_ID_RIGHT, PPE_NAME_RIGHT}),
        sliderBank2 (p, vts, {PPE_ID_FEEDBACK, PPE_NAME_FEEDBACK}, {PPE_ID_DRIVE, PPE_NAME_DRIVE}),
        sliderBank3 (p, vts, {PPE_ID_HICUT, PPE_NAME_HICUT}, {PPE_ID_LOCUT, PPE_NAME_LOCUT}),
        sliderBank4 (p, vts, {PPE_ID_FLUTTER, PPE_NAME_FLUTTER}, {PPE_ID_WOW, PPE_NAME_WOW}),
        mixSlider (vts, PPE_ID_MIX, PPE_NAME_MIX),
        buttonBank (p, vts, {PPE_ID_LINK, PPE_NAME_LINK}, {PPE_ID_SYNC, PPE_NAME_SYNC})
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 400);
    addAndMakeVisible (sliderBank1);
    addAndMakeVisible (sliderBank2);
    addAndMakeVisible (sliderBank3);
    addAndMakeVisible (sliderBank4);
    addAndMakeVisible (buttonBank);
    addAndMakeVisible (mixSlider);
}

PingPongEdEditor::~PingPongEdEditor ()
{
}

//==============================================================================
void PingPongEdEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel ().findColour (juce::ResizableWindow::backgroundColourId));


}

void PingPongEdEditor::resized ()
{

    std::vector<juce::Rectangle<int>> areas {6, getLocalBounds ()};

    for (int i = 0; i < areas.size (); ++i)
    {
        areas[i].removeFromRight ((getWidth () / 6) * (5 - i));
        areas[i].removeFromLeft ((getWidth () / 6) * (i));
    }

    sliderBank1.setBounds (areas[0]);
    buttonBank.setBounds (areas[1]);
    sliderBank2.setBounds (areas[2]);
    sliderBank3.setBounds (areas[3]);
    sliderBank4.setBounds (areas[4]);
    mixSlider.setBounds (areas[5]);

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
