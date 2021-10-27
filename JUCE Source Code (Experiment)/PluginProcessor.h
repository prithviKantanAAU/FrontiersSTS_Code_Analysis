#pragma once

#include <JuceHeader.h>
#include "ExptControl.h"
#include "AudioFileContainer.h"

//==============================================================================
/**
*/
class STS_ListeningTestAudioProcessor  : public juce::AudioProcessor, public juce::HighResolutionTimer
{
public:
    //==============================================================================
    STS_ListeningTestAudioProcessor();
    ~STS_ListeningTestAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    exptControl exptCont;
    AudioFileContainer* audFileCont;

    void handleScreenChange();
    bool screenChange_isPendingUIChange = false;
    bool screenChange_isPendingUIChange_TRAINING = false;
    bool toTrigger_Audio = false;
    bool toTrigger_Noise = false;
    bool toTrigger_TestFile = false;
    bool isChoiceClicked = false;
    bool toLoad_PastState = false;

    void endExperiment()
    {
        exptCont.logStore.storeLog(exptCont.Mat_Choices, exptCont.Mat_Confidence, exptCont.Mat_ResponseTime, 
            exptCont.order_Blocks, exptCont.order_PatternsInBlock, exptCont.num_Blocks, exptCont.num_Patterns, exptCont.num_Reps, 
            exptCont.omsiIndex);
        exptCont.completion = true;
        handleScreenChange();
    }

private:

    void hiResTimerCallback();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (STS_ListeningTestAudioProcessor)
};
