#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class STS_ListeningTestAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    STS_ListeningTestAudioProcessorEditor (STS_ListeningTestAudioProcessor&);
    ~STS_ListeningTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    STS_ListeningTestAudioProcessor& audioProcessor;
    
    int interface_Width = 1300;
    int interface_Height = 700;
    int uiRefreshFreq = 40;

    int screen_Present = 3;
    int screen_Total = 11;

    void timerCallback();

    // UI ELEMENTS

    // COMMON
    juce::Label header;
    int fontSize_header = 36;
    juce::Label body;
    int fontSize_body = 24;
    juce::Justification centred = juce::Justification::centred;

    juce::TextButton proceed;

    juce::String headerText[15] =
    {
        "",
        "WELCOME!",
        "MUSICAL SOPHISTICATION SCALE",
        "MUSICAL SOPHISTICATION SCALE",
        "EXPERIMENT INFO",
        "TRIAL NUMBER: ",
        "SOUND SEQUENCE",
        "",
        "NOISE SEQUENCE",
        "EXPERIMENT COMPLETE",
        "FAMILIARIZATION PHASE",
        "TRAINING PHASE",
        ""
    };

    juce::String bodyText[15] = {
        "",

        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd ",

        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd ",
        
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd "
        "abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd abcd ",
        
        "Welcome to this listening test experiment. \n\n"
        "Here, the goal is to identify sit-stand movement types by listening to musical audio clips. \n"
        "These audio clips were generated by converting the movement properties into sound in different ways. Now, you must:\n\n"
        "1) Familiarize yourself with the movement types.\n"
        "2) Understand how these are communicated through sound.\n"
        "3) Learn to work with the training interface.\n"
        "4) Understand the structure and length of the experiment.\n\n"
        ""
        "Please feel free to ask questions at any time.",
        "Listen carefully to the sound sequence that follows.",
        "",
        "",
        "",
        "",
        "Please watch the following video:",
        "Here, you can train yourself in classifying the audio clips for as long as you like. \n\n"
        "Use the slider to change the amount of information the sound contains. \n\n"
        "Then, click the button to play a random audio clip, and see whether you are able to correctly guess the movement pattern. ",
        "",
        "",
        ""
    };

    // SCREEN-SPECIFIC
    juce::TextButton endExpt;
    juce::TextButton endExpt_Y;
    juce::TextButton endExpt_N;
    short quitState = 0;

    // 1

    // 2

    // 3
    juce::HyperlinkButton omsiLink;
    juce::TextEditor omsiScore;
    juce::Label omsiScore_Lab;
    juce::TextButton load_PastLog;
    // 4

    // 5
    juce::TextButton startTrial;
    juce::TextButton understandBlock;
    juce::Label blockInfo;
    juce::Label newInfoCombo;
    // 6

    // 7
    juce::Label choiceQ;
    juce::String choiceQ_Text = "Which pattern does the sound represent? (FIRST THAT COMES TO MIND)";
    juce::Label confidenceQ;
    juce::String confidenceQ_Text = "How confident are you in your choice? 0 : Not at all, 100: Fully";
    juce::Slider confidenceScale;
    juce::ToggleButton choiceToggle[10];    
    juce::Label choiceToggleLAB[10];    
    juce::String choiceToggleLAB_Text[10] =
    {
        "Slow Rise",
        "Slow / Fast",
        "Failed Attempts",
        "Freezing",
        "Jerky Rise",
        "Unstable Ankles",
        "Pattern 7",
        "",
        "",
        "",
    };
    juce::Label timeLeft;
    juce::String timeLeft_Text = "";
    int fontSize_Q = 30;
    bool trial_choiceMade = false;
    bool trial_confEntered = false;

    // 8

    // 9

    // 10
    juce::TextButton        training_playFile;
    juce::Slider            training_mapCombo;
    juce::Label             training_mapCombo_Info;
    juce::TextButton        training_checkAns;
    juce::Label             training_feedback;
    juce::HyperlinkButton   training_AnsVideo;
    void training_handlePhaseChange();
    
    juce::String            training_mapCombos[10] =
    {
        "Info Provided: Speed",
        "Info Provided: Speed, Jerkiness",
        "Info Provided: Speed, Progression",
        "Info Provided: Speed, Stopping, Jerkiness",
        "Info Provided: Speed, Progression, Stopping",
        "Info Provided: Speed, Progression, Stopping, Jerkiness",
    };

    // 11

    void addUIElements()
    {
        addAndMakeVisible(endExpt);
        addAndMakeVisible(newInfoCombo);
        addAndMakeVisible(omsiLink);
        addAndMakeVisible(omsiScore);
        addAndMakeVisible(omsiScore_Lab);
        addAndMakeVisible(load_PastLog);
        addAndMakeVisible(endExpt_Y);
        addAndMakeVisible(endExpt_N);
        addAndMakeVisible(header);
        addAndMakeVisible(body);
        addAndMakeVisible(proceed);
        addAndMakeVisible(understandBlock);
        addAndMakeVisible(startTrial);
        addAndMakeVisible(blockInfo);
        addAndMakeVisible(choiceQ);
        addAndMakeVisible(confidenceQ);
        addAndMakeVisible(confidenceScale);
        for (int i = 0; i < 10; i++)
        {
            addAndMakeVisible(choiceToggle[i]);
            addAndMakeVisible(choiceToggleLAB[i]);
        }
        addAndMakeVisible(timeLeft);
        addAndMakeVisible(training_playFile);
        addAndMakeVisible(training_mapCombo);
        addAndMakeVisible(training_mapCombo_Info);
        addAndMakeVisible(training_checkAns);
        addAndMakeVisible(training_feedback);
        addAndMakeVisible(training_AnsVideo);     
    }

    void initializeUI()
    {
        header.setJustificationType(centred);
        body.setJustificationType(centred);
        choiceQ.setJustificationType(centred);
        newInfoCombo.setJustificationType(centred);
        confidenceQ.setJustificationType(centred);
        timeLeft.setJustificationType(centred);
        training_feedback.setJustificationType(centred);
        training_mapCombo_Info.setJustificationType(centred);
        blockInfo.setJustificationType(centred);
        blockInfo.setColour(blockInfo.backgroundColourId,juce::Colours::lightblue);
        blockInfo.setColour(blockInfo.textColourId,juce::Colours::black);

        header.setFont(juce::Font(fontSize_header, juce::Font::bold));
        training_feedback.setFont(juce::Font(fontSize_body*2, juce::Font::bold));
        body.setFont(juce::Font(fontSize_body, juce::Font::plain));
        blockInfo.setFont(juce::Font(fontSize_body*0.7, juce::Font::bold));
        choiceQ.setFont(juce::Font(fontSize_Q, juce::Font::plain));
        newInfoCombo.setFont(juce::Font(fontSize_Q, juce::Font::bold));
        confidenceQ.setFont(juce::Font(fontSize_Q, juce::Font::plain));
        training_mapCombo_Info.setFont(juce::Font(fontSize_Q, juce::Font::bold));
        timeLeft.setFont(juce::Font(fontSize_Q, juce::Font::plain));
        
        load_PastLog.setButtonText("Load Previous");
        load_PastLog.setColour(load_PastLog.buttonColourId, juce::Colours::navy);
        load_PastLog.onClick = [this]
        {
            juce::String filePath = "";
            juce::String extension = "*.csv";
            juce::FileChooser logChooser("Please select a valid log",
                juce::File::getSpecialLocation(juce::File::currentApplicationFile), extension);
            if (logChooser.browseForFileToOpen())
            {
                juce::File logFile(logChooser.getResult());
                filePath = logFile.getFullPathName();
                audioProcessor.exptCont.loadPastState(filePath);
                audioProcessor.toLoad_PastState = true;
                audioProcessor.handleScreenChange();
            }
        };

        endExpt.setColour(endExpt.buttonColourId, juce::Colours::navy);
        endExpt.setButtonText("Terminate Experiment");
        endExpt.onClick = [this]
        {
            if (quitState == 0)
            {
                quitState = 1;
                endExpt.setVisible(false);
                endExpt_Y.setVisible(true);
                endExpt_N.setVisible(true);
            }
        };

        endExpt_Y.setColour(endExpt_Y.buttonColourId, juce::Colours::red);
        endExpt_Y.setButtonText("Yes, Quit");
        endExpt_Y.setVisible(false);
        endExpt_Y.onClick = [this]
        {
            quitState = 2;
            audioProcessor.endExperiment();
            endExpt_Y.setVisible(false);
            endExpt_N.setVisible(false);
            endExpt.setVisible(false);
        };

        endExpt_N.setColour(endExpt_Y.buttonColourId, juce::Colours::green);
        endExpt_N.setButtonText("No, Go Back");
        endExpt_N.setVisible(false);
        endExpt_N.onClick = [this]
        {
            quitState = 0;
            endExpt.setVisible(true);
            endExpt_Y.setVisible(false);
            endExpt_N.setVisible(false);
        };

        proceed.setColour(proceed.buttonColourId, juce::Colours::red);
        proceed.setButtonText("Proceed");
        proceed.onClick = [this]
        {
            if (quitState == 1)
            {
                quitState = 0;
                endExpt.setVisible(true);
                endExpt_Y.setVisible(false);
                endExpt_N.setVisible(false);
            }

            audioProcessor.handleScreenChange();
        };
        startTrial.setButtonText("Start Trial");
        startTrial.onClick = [this]
        {
            audioProcessor.handleScreenChange();
        };

        understandBlock.setButtonText("I Understand");
        understandBlock.setColour(understandBlock.buttonColourId, juce::Colours::blue);
        understandBlock.onClick = [this]
        {
            startTrial.setVisible(true);
            understandBlock.setVisible(false);
        };

        choiceQ.setText(choiceQ_Text, juce::dontSendNotification);
        choiceQ.setColour(choiceQ.backgroundColourId, juce::Colours::black);
        confidenceQ.setText(confidenceQ_Text, juce::dontSendNotification);
        confidenceQ.setColour(confidenceQ.backgroundColourId, juce::Colours::black);

        for (int i = 0; i < 10; i++)
        {
            choiceToggle[i].setToggleState((i == 0) ? true : false,juce::dontSendNotification);
            choiceToggleLAB[i].attachToComponent(&choiceToggle[i], true);
            choiceToggleLAB[i].setJustificationType(centred);
            choiceToggleLAB[i].setFont(juce::Font(22, juce::Font::bold));
            choiceToggleLAB[i].setColour(choiceToggleLAB[i].backgroundColourId, juce::Colours::blue);
            choiceToggleLAB[i].setText(choiceToggleLAB_Text[i], juce::dontSendNotification);

            choiceToggle[i].onStateChange = [this, i]
            {
                if (choiceToggle[i].getToggleState())
                {
                    trial_choiceMade = true;
                    if (!audioProcessor.isChoiceClicked) audioProcessor.isChoiceClicked = true;
                    audioProcessor.exptCont.current_CHOICE = i + 1;
                    choiceToggleLAB[i].setColour(choiceToggleLAB[i].backgroundColourId, juce::Colours::green);
                    choiceToggle[i].setAlpha(0);

                    for (int j = 0; j < 6; j++)
                    {
                        if (j != i)
                        {
                            choiceToggle[j].setToggleState(false, juce::sendNotificationSync);
                            choiceToggle[j].setVisible(false);
                        }
                    }

                    if (screen_Present == 7 && trial_confEntered) proceed.setVisible(true);
                }

                else if (!choiceToggle[i].getToggleState())
                {
                   choiceToggleLAB[i].setColour(choiceToggleLAB[i].backgroundColourId, juce::Colours::blue);
                }
            };
        }

        confidenceScale.setRange(0, 100);
        confidenceScale.setValue(50);
        confidenceScale.setNumDecimalPlacesToDisplay(0);
        confidenceScale.setColour(confidenceScale.trackColourId, juce::Colours::yellow);
        confidenceScale.setColour(confidenceScale.backgroundColourId, juce::Colours::blue);
        confidenceScale.setColour(confidenceScale.thumbColourId, juce::Colours::white);
        confidenceScale.onValueChange = [this]
        {
            if(trial_choiceMade) trial_confEntered = true;
            audioProcessor.exptCont.current_CONFIDENCE = confidenceScale.getValue();

            if (screen_Present == 7 && trial_choiceMade) proceed.setVisible(true);
        };
        training_feedback.setColour(training_feedback.textColourId, juce::Colours::yellow);
        
        training_playFile.setColour(training_playFile.buttonColourId, juce::Colours::blue);
        training_playFile.setButtonText("Play Random Pattern");
        training_playFile.onClick = [this]
        {
            audioProcessor.exptCont.phase_Training = 2;
            audioProcessor.screenChange_isPendingUIChange_TRAINING = true;
            audioProcessor.exptCont.getNew_PatternIdx_Training();
            audioProcessor.toTrigger_TestFile = true;
            audioProcessor.audFileCont->isComplete_lastFile = false;
        };

        training_mapCombo.setRange(0, audioProcessor.exptCont.num_Blocks - 1, 1);
        training_mapCombo.setValue(audioProcessor.exptCont.num_Blocks - 1);
        training_mapCombo.setColour(training_mapCombo.trackColourId, juce::Colours::yellow);
        training_mapCombo.setColour(training_mapCombo.backgroundColourId, juce::Colours::blue);
        training_mapCombo.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        training_mapCombo.onValueChange = [this]
        {
            training_updateInfoLabel();
            audioProcessor.exptCont.trainingMapping_Slider = training_mapCombo.getValue();
        };

        training_checkAns.setColour(training_checkAns.buttonColourId, juce::Colours::green);
        training_checkAns.onClick = [this]
        {
            if (audioProcessor.exptCont.phase_Training == 3)
                audioProcessor.exptCont.phase_Training = 4;

            else if (audioProcessor.exptCont.phase_Training == 4)
                audioProcessor.exptCont.phase_Training = 1;

            audioProcessor.screenChange_isPendingUIChange_TRAINING = true;
        };

        training_AnsVideo.setButtonText("Watch Clip With Sound");
        training_AnsVideo.setColour(training_AnsVideo.textColourId, juce::Colours::yellow);

        omsiLink.setButtonText("Click here");
        juce::String omsiURL = "https://shiny.gold-msi.org/longgold_demo/?test=GMS&language=en&p_id=430a74975011940469dd3f48d76e875eb77e2954057964e516c17ef11a79ab1b";
        //juce::String omsiURL = "http://marcs-survey.uws.edu.au/OMSI/";
        omsiLink.setURL(omsiURL);

        omsiScore.setJustification(centred);
        omsiScore.setFont(juce::Font(fontSize_body, juce::Font::bold));
        omsiScore.onTextChange = [this]
        {
            audioProcessor.exptCont.omsiIndex = omsiScore.getText().getIntValue();
        };
        omsiScore_Lab.setText("Enter your score here:",juce::dontSendNotification);
        omsiScore_Lab.attachToComponent(&omsiScore, true);
        
        newInfoCombo.setText("New Info Combination - See Top Right!",juce::dontSendNotification);
        newInfoCombo.setColour(newInfoCombo.backgroundColourId, juce::Colours::black);
    }

    void nextScreen()
    {
        screen_Present = audioProcessor.exptCont.present_Screen;

        modifyText_HeaderBody();
        hideAllUI();
        showScreenUI();
    }

    void hideAllUI()
    {
        newInfoCombo.setVisible(false);
        omsiLink.setVisible(false);
        omsiScore.setVisible(false);
        header.setVisible(false);
        body.setVisible(false);
        proceed.setVisible(false);
        startTrial.setVisible(false);
        blockInfo.setVisible(false);
        understandBlock.setVisible(false);
        choiceQ.setVisible(false);
        confidenceQ.setVisible(false);
        confidenceScale.setVisible(false);
        for (int i = 0; i < 10; i++)
        {
            choiceToggle[i].setVisible(false);
        }
        timeLeft.setVisible(false);
        training_playFile.setVisible(false);
        training_mapCombo.setVisible(false);
        training_mapCombo_Info.setVisible(false);
        training_checkAns.setVisible(false);
        training_feedback.setVisible(false);
        training_AnsVideo.setVisible(false);
        load_PastLog.setVisible(false);
    }

    void showScreenUI()
    {
        juce::Random randChoice;
        proceed.setButtonText("Proceed");

        switch (screen_Present)
        {
        case 1:                                     // WELCOME
            header.setVisible(true);
            body.setVisible(true);
            proceed.setVisible(true);
            break;
        case 2:                                     // NONE
            header.setVisible(true);
            body.setVisible(true);
            proceed.setVisible(true);
            break;
        case 3:                                     // MSOPH
            load_PastLog.setVisible(true);
            header.setVisible(true);
            omsiLink.setVisible(true);
            omsiScore.setVisible(true);
            //body.setVisible(true);
            proceed.setVisible(true);
            break;
        case 4:                                     // EXPERIMENT INFO
            header.setVisible(true);
            body.setVisible(true);
            proceed.setVisible(true);
            break;
        case 5:                                     // TRIAL START
            update_BlockInfo();
            blockInfo.setVisible(true);
            header.setVisible(true);
            body.setVisible(true);
            startTrial.setVisible(true);

            if (audioProcessor.exptCont.is_NewBlock || audioProcessor.exptCont.currentTrial == 0)
            {
                newInfoCombo.setVisible(true);
                startTrial.setVisible(false);
                understandBlock.setVisible(true);
            }

            break; 
        case 6:                                     // SOUND SEQUENCE
            header.setVisible(true);
            //timeLeft.setVisible(true);
            break;
        case 7:                                     // QUESTION FILLING
            trial_confEntered = false;
            trial_choiceMade = false;
            choiceQ.setVisible(true);
            confidenceQ.setVisible(true);
            for (int i = 0; i < 6; i++)
            {
                choiceToggle[i].setVisible(true);
                choiceToggle[i].setAlpha(100);
                choiceToggle[i].setToggleState(false, juce::sendNotificationSync);
            }
            trial_choiceMade = false;
            confidenceScale.setValue(0);
            confidenceScale.setVisible(true);
            trial_confEntered = false;
            
            //timeLeft.setVisible(true);
            //proceed.setVisible(true);
            break;
        case 8:                                     // NOISE SEQUENCE
            header.setVisible(true);
            //timeLeft.setVisible(true);
            break;
        case 9:                                     // EXPERIMENT COMPLETE
            header.setVisible(true);
            body.setVisible(true);
            break;
        case 10:
            header.setVisible(true);
            body.setVisible(true);
            proceed.setVisible(true);
            break;
        case 11:                                    // REINFORCEMENT LEARNING PHASE
            header.setVisible(true);
            body.setVisible(true);
            proceed.setButtonText("START EXPERIMENT");
            proceed.setVisible(true);
            break;
        }
    }

    void modifyText_HeaderBody()
    {
        header.setText(headerText[screen_Present], juce::dontSendNotification);
        body.setText(bodyText[screen_Present], juce::dontSendNotification);
    }

    void updateTimeLeft()
    {
        timeLeft.setText("Time Left (sec): " + juce::String
        (audioProcessor.exptCont.presentScreen_TimeLeft, 1),juce::dontSendNotification);
    }

    void updateTrialNumber()
    {
        if (screen_Present == 5)
            //header.setText("Trial Number: " + juce::String(audioProcessor.exptCont.currentTrial + 1), juce::dontSendNotification);
            header.setText("Trial", juce::dontSendNotification);
    }

    void training_updateInfoLabel()
    {
        training_mapCombo_Info.setText(training_mapCombos[(int)training_mapCombo.getValue()] + " (Tries Done: "
            + juce::String(audioProcessor.exptCont.training_numTries[(int)training_mapCombo.getValue()]) + ")"
            , juce::dontSendNotification);
        bool comboDone = audioProcessor.exptCont.training_numTries[(int)training_mapCombo.getValue()] >= audioProcessor.exptCont.training_numTries_MIN;
        training_mapCombo_Info.setColour(training_mapCombo_Info.textColourId, comboDone ? juce::Colours::lightgreen : juce::Colours::red);
    }

    bool is_MinTraining_Done()
    {
        bool done = true;
        for (int i = 0; i < audioProcessor.exptCont.num_Blocks; i++)
        {
            if (audioProcessor.exptCont.training_numTries[i] < audioProcessor.exptCont.training_numTries_MIN)
                done = false;
        }
        return done;
    }

    void update_BlockInfo()
    {
        juce::String text = "Block " + juce::String(audioProcessor.exptCont.current_Block + 1) + "\n\n";
        juce::String yesNo = "";

        for (int i = 0; i < audioProcessor.exptCont.numMappings_1_1; i++)
        {
            yesNo = audioProcessor.exptCont.isMappingPresent_Blockwise
                [audioProcessor.exptCont.current_Block][i] ?
                "YES" : "NO";
            text += audioProcessor.exptCont.mappingNames_1234[i] + " - " + yesNo + "\n\n";
        }

        blockInfo.setText(text, juce::dontSendNotification);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(STS_ListeningTestAudioProcessorEditor)
};
