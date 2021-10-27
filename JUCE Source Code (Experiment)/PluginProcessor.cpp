/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
STS_ListeningTestAudioProcessor::STS_ListeningTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    audFileCont = new AudioFileContainer(exptCont.num_Blocks, exptCont.num_Patterns);
    startTimer(10);
}

STS_ListeningTestAudioProcessor::~STS_ListeningTestAudioProcessor()
{
}

void STS_ListeningTestAudioProcessor::hiResTimerCallback()
{
    if (exptCont.decrementTimer(isChoiceClicked))
        handleScreenChange();

    if (exptCont.isTraining && audFileCont->isComplete_lastFile && exptCont.phase_Training == 2)
    {
        exptCont.phase_Training = 3;
        screenChange_isPendingUIChange_TRAINING = true;
    }
}

void STS_ListeningTestAudioProcessor::handleScreenChange()
{
    toTrigger_Audio = false;
    toTrigger_Noise = false;
    audFileCont->isComplete_lastFile = false;

    if (exptCont.completion) exptCont.present_Screen = 9;

    switch (exptCont.present_Screen)
    {
    case 1:
        exptCont.present_Screen = 2;
        break;
    case 2:
        exptCont.present_Screen = 3;
        break;
    case 3:
        if (toLoad_PastState)
        {
            if (exptCont.currentTrial == exptCont.num_Trials_TOTAL)
                exptCont.present_Screen = 9;
            else
                exptCont.present_Screen = 5;
        }
        else
        exptCont.present_Screen = 4;
        break;
    case 4:
        exptCont.isTraining = true;
        exptCont.phase_Training = 1;
        screenChange_isPendingUIChange_TRAINING = true;
        exptCont.present_Screen = 11;
        break;
    case 5:
        exptCont.present_Screen = 6;
        toTrigger_Audio = true;
        break;
    case 6:
        exptCont.current_CHOICE = -1;
        isChoiceClicked = false;
        exptCont.present_Screen = 7;
        break;
    case 7:
        exptCont.endTrial();
        toTrigger_Noise = true;
        exptCont.present_Screen = 8;
        break;
    case 8:
        exptCont.present_Screen = exptCont.completion ? 9 : 5;
        break;
    case 9:
        break;
    case 10:
        exptCont.present_Screen = 11;
        break;
    case 11:                                                        // TRAINING
        exptCont.isTraining = false;
        exptCont.present_Screen = 5;
        break;
    }
    screenChange_isPendingUIChange = true;
    exptCont.initializeTimer();
}

//==============================================================================
const juce::String STS_ListeningTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool STS_ListeningTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool STS_ListeningTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool STS_ListeningTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double STS_ListeningTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int STS_ListeningTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int STS_ListeningTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void STS_ListeningTestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String STS_ListeningTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void STS_ListeningTestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void STS_ListeningTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void STS_ListeningTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool STS_ListeningTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void STS_ListeningTestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    float outputAudio = 0.0;
    float outputNoise = 0.0;
    bool triggerAudio = toTrigger_Audio || toTrigger_TestFile;
    bool triggerNoise = toTrigger_Noise;

    int blockNum = 0;
    int patternNum = 0;

    if (exptCont.isTraining)
    {
        blockNum = exptCont.trainingMapping_Slider;
        patternNum = exptCont.trainingPattern_Random;
    }

    else
    {
        exptCont.get_TRUE_Block_Pattern_fromTrialIdx(&blockNum, &patternNum);
    }

    //for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //    buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) 
        {
            outputAudio = audFileCont->playFile(triggerAudio, blockNum, patternNum, channel, i, buffer.getNumSamples(), exptCont.isTraining);

            outputNoise = audFileCont->generateNoise(toTrigger_Noise);

            *buffer.getWritePointer(channel, i) = juce::jlimit(-1.0,1.0,(double)(outputAudio + outputNoise));
        }

        audFileCont->trigger_z1 = triggerAudio;
    }
}

//==============================================================================
bool STS_ListeningTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* STS_ListeningTestAudioProcessor::createEditor()
{
    return new STS_ListeningTestAudioProcessorEditor (*this);
}

//==============================================================================
void STS_ListeningTestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void STS_ListeningTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new STS_ListeningTestAudioProcessor();
}
