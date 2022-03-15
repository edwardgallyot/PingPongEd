//
// Created by edgallyot on 21/02/2022.
//

#ifndef DISTORTED_BASEPROCESSOR_H
#define DISTORTED_BASEPROCESSOR_H

#include <JuceHeader.h>

class BaseProcessor : virtual public juce::AudioProcessor
{
    const juce::String getName () const override;

    bool acceptsMidi () const override;
    bool producesMidi () const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds () const override;

    int getNumPrograms () override;
    int getCurrentProgram () override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    bool hasEditor () const override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

};


#endif //DISTORTED_BASEPROCESSOR_H
