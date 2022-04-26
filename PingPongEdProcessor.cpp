#include "PingPongEdProcessor.h"
#include "PingPongEdEditor.h"
#include "id_name_vts.h"


//==============================================================================
PingPongEdProcessor::PingPongEdProcessor ()
        : AudioProcessor (
        BusesProperties ()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                .withInput ("Input", juce::AudioChannelSet::stereo (), true)
#endif
                .withOutput ("Output", juce::AudioChannelSet::stereo (), true)
#endif
),

          parameters (
                  *this, nullptr, juce::Identifier (PPE_ID_TREE),
                  createParameterLayout ()
          )
{
    size_t i = 0;
    for (const auto &id : m_ids)
    {
        m_parameters[i] = parameters.getRawParameterValue (id);
        i++;
    }
}

PingPongEdProcessor::~PingPongEdProcessor ()
{
}

//==============================================================================


//==============================================================================
void PingPongEdProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
    delayModule.prepare (sampleRate, samplesPerBlock, m_parameters);
    cubicModule.prepare(sampleRate, samplesPerBlock);
}

void PingPongEdProcessor::releaseResources ()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool PingPongEdProcessor::isBusesLayoutSupported (const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet () != juce::AudioChannelSet::mono ()
        && layouts.getMainOutputChannelSet () != juce::AudioChannelSet::stereo ())
        return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet () != layouts.getMainInputChannelSet ())
        return false;
#endif

    return true;
#endif
}

void PingPongEdProcessor::processBlock (juce::AudioBuffer<float> &buffer,
                                        juce::MidiBuffer &midiMessages)
{
    size_t i = 0;
    for (const auto &id : m_ids)
    {
        m_parameters[i] = parameters.getRawParameterValue (id);
        i++;
    }
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels ();
    auto totalNumOutputChannels = getTotalNumOutputChannels ();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples ());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    delayModule.setParameters (m_parameters);
    delayModule.process (buffer, midiMessages, m_parameters);
    cubicModule.process(buffer, midiMessages, m_parameters[DelayParameters::Drive]->load());
    // TODO : Split Buffer in Two so tone modules can be implemented and mix is in main processor
}


juce::AudioProcessorEditor *PingPongEdProcessor::createEditor ()
{
    return new PingPongEdEditor (*this, parameters);
}

//==============================================================================
void PingPongEdProcessor::getStateInformation (juce::MemoryBlock &destData)
{
    auto state = parameters.copyState ();
    std::unique_ptr<juce::XmlElement> xml (state.createXml ());
    copyXmlToBinary (*xml, destData);
}

void PingPongEdProcessor::setStateInformation (const void *data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get () != nullptr)
        if (xmlState->hasTagName (parameters.state.getType ()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout PingPongEdProcessor::createParameterLayout ()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    DBG(m_ids.size ());

    for (size_t i = 0; i < m_ids.size (); ++i)
    {
        params.add (
                std::make_unique<juce::AudioParameterFloat> (
                        m_ids[i],
                        m_names[i],
                        m_minimums[i],
                        m_maxes[i],
                        m_defaults[i]));
    }
    return params;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter ()
{
    return new PingPongEdProcessor ();
}
