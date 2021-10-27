#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
STS_ListeningTestAudioProcessorEditor::STS_ListeningTestAudioProcessorEditor (STS_ListeningTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (interface_Width, interface_Height);
    addUIElements();
    initializeUI();
    nextScreen();
    startTimerHz(uiRefreshFreq);
    
}

STS_ListeningTestAudioProcessorEditor::~STS_ListeningTestAudioProcessorEditor()
{
}

void STS_ListeningTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void STS_ListeningTestAudioProcessorEditor::timerCallback()
{
    updateTimeLeft();
    updateTrialNumber();
    if (audioProcessor.screenChange_isPendingUIChange)
    {
        nextScreen();
        audioProcessor.screenChange_isPendingUIChange = false;
    }

    if (audioProcessor.screenChange_isPendingUIChange_TRAINING && audioProcessor.exptCont.isTraining)
    {
        training_handlePhaseChange();
    }
}

void STS_ListeningTestAudioProcessorEditor::training_handlePhaseChange()
{
    training_feedback.setVisible(true);
    proceed.setVisible(false);

    switch (audioProcessor.exptCont.phase_Training)
    {
    case 1:
        training_updateInfoLabel();
        body.setVisible(false);
        training_checkAns.setVisible(false);
        training_AnsVideo.setVisible(false);
        training_playFile.setVisible(true);
        training_mapCombo.setVisible(true);
        training_mapCombo_Info.setVisible(true);
        audioProcessor.toTrigger_TestFile = false;
        training_feedback.setText("Ready to play sound.", juce::dontSendNotification);
        break;
    case 2:
       
        training_playFile.setVisible(false);
        training_mapCombo.setVisible(false);
        training_mapCombo_Info.setVisible(false);
        training_AnsVideo.setVisible(false);
        training_feedback.setText("Playing sound...", juce::dontSendNotification);
        break;
    case 3:
        training_checkAns.setButtonText("Check \n Answer");
        training_AnsVideo.setVisible(false);
        choiceQ.setVisible(true);
        confidenceQ.setVisible(true);
        for (int i = 0; i < 6; i++)
        {
            choiceToggle[i].setAlpha(100);
            choiceToggle[i].setVisible(true);
            choiceToggle[i].setToggleState(false, juce::sendNotificationSync);
        }
        confidenceScale.setValue(0);
        confidenceScale.setVisible(true);
        training_checkAns.setVisible(true);
        audioProcessor.toTrigger_TestFile = false;
        training_feedback.setText("Pattern identification in progress.", juce::dontSendNotification);
        break;
    case 4:
        training_AnsVideo.setVisible(true);
        training_AnsVideo.setURL(audioProcessor.exptCont.getVideoLinkFull(
            audioProcessor.exptCont.trainingMapping_Slider, audioProcessor.exptCont.trainingPattern_Random));
        training_checkAns.setButtonText("Try Again");
        choiceQ.setVisible(false);
        confidenceQ.setVisible(false);
        for (int i = 0; i < 6; i++)
        {
            choiceToggle[i].setVisible(false);
        }
        confidenceScale.setVisible(false);

        training_feedback.setText("Your Choice: " + choiceToggleLAB_Text[audioProcessor.exptCont.current_CHOICE - 1] + "      " +
            "Correct Answer: " + choiceToggleLAB_Text[audioProcessor.exptCont.trainingPattern_Random]
            , juce::dontSendNotification);
        training_feedback.setColour(training_feedback.textColourId,
            choiceToggleLAB_Text[audioProcessor.exptCont.current_CHOICE - 1] == choiceToggleLAB_Text[audioProcessor.exptCont.trainingPattern_Random] ?
            juce::Colours::lightgreen : juce::Colours::orangered
            );

        audioProcessor.exptCont.training_numTries[(int)training_mapCombo.getValue()] += 1;
        break;
    }

    if (is_MinTraining_Done())
        proceed.setVisible(true);

    audioProcessor.screenChange_isPendingUIChange_TRAINING = false;
}

void STS_ListeningTestAudioProcessorEditor::resized()
{
    proceed.setBounds(interface_Width / 2 - 100, interface_Height - 60, 200, 40);

    header.setBounds(0, 0, interface_Width, interface_Height / 10);

    // 1
    body.setBounds(0, interface_Height / 10, interface_Width, interface_Height / 2.4);

    // 2

    // 3
    omsiLink.setBounds(0, interface_Height / 10, interface_Width, interface_Height / 2.4);
    omsiScore.setBounds(interface_Width/4, interface_Height / 2, interface_Width/2, interface_Height / 8);
    load_PastLog.setBounds(20, interface_Height - 25, 300, 20);

    // 4

    // 5
    blockInfo.setBounds(interface_Width * 0.75, 0, interface_Width * 0.25, interface_Height * 0.33);
    startTrial.setBounds(interface_Width / 2 - 100, interface_Height - 100, 200, 40);
    newInfoCombo.setBounds(0, 3 * interface_Height / 8, interface_Width, interface_Height / 8);
    understandBlock.setBounds(interface_Width * 0.75, 3 * interface_Height / 8, interface_Width * 0.25, interface_Height / 8);

    // 6

    // 7
    choiceQ.setBounds(0, 3* interface_Height / 8, interface_Width, interface_Height / 8);
    for (int i = 0; i < audioProcessor.exptCont.num_Patterns; i++)
        choiceToggle[i].setBounds(150 + (interface_Width - 50) * i / 6, 4*interface_Height / 8, 40, interface_Height / 8);
    confidenceQ.setBounds(0, 5 * interface_Height / 8, interface_Width, interface_Height / 8);
    confidenceScale.setBounds(200, 6 * interface_Height / 8, interface_Width - 400, interface_Height / 8);
    timeLeft.setBounds(0, 2 * interface_Height / 8, interface_Width, interface_Height / 8);

    // 8

    // 9

    // 10

    // 11
    training_mapCombo.setBounds(interface_Width / 4, 3 * interface_Height / 8, interface_Width / 2, interface_Height / 8);
    training_mapCombo_Info.setBounds(0, 5 * interface_Height / 8 - 100, interface_Width, interface_Height / 8);
    training_playFile.setBounds(200, 6 * interface_Height / 8 - 50, interface_Width - 400, interface_Height / 8);
    training_AnsVideo.setBounds(200, 6 * interface_Height / 8 - 50, interface_Width - 400, interface_Height / 16);
    training_checkAns.setBounds(interface_Width - 180, 6 * interface_Height / 8, 100, interface_Height / 8);
    training_feedback.setBounds(0, interface_Height / 10, interface_Width, interface_Height / 3);

    endExpt.setBounds(interface_Width - 320, interface_Height - 25, 300, 20);
    endExpt_Y.setBounds(interface_Width - 320, interface_Height - 25, 150, 20);
    endExpt_N.setBounds(interface_Width - 160, interface_Height - 25, 150, 20);
}
