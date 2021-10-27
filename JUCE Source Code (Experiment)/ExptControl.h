#pragma once
#include <JuceHeader.h>
#include "LogStore.h"

class exptControl
{
public:
	exptControl()
	{
		initializeDataHolders();
		generateOrder();

		int true_Block = -1;
		int true_Pattern = -1;
		get_TRUE_Block_Pattern_fromTrialIdx(&true_Block, &true_Pattern);
		current_Block = true_Block;
		// Test Log
		//logStore.storeLog(Mat_Choices, Mat_Confidence, Mat_ResponseTime, order_Blocks, order_PatternsInBlock,
		//	num_Blocks, num_Patterns, num_Reps);
	}

	~exptControl()
	{

	}

	///////////////////////////////////////////////////// CHANGE ///////////////////////////////////////////////////////////

	int training_numTries_MIN = 3;
	int num_Reps = 3;

	///////////////////////////////////////////////////// DATA STRUCTURE INITIALIZATION /////////////////////////////////////////////

	bool completion = false;

	int num_Blocks = 6;
	int num_Patterns = 6;
	
	int num_Trials_TOTAL = 0;
	int num_Trials_PERBLOCK = 0;

	int current_Block = 0;
	int current_Pattern = 0;
	int current_Rep = 0;

	int currentTrial = 0;

	int order_Blocks[10];
	int order_PatternsInBlock[10][50];

	int current_CHOICE = 1;
	int current_CONFIDENCE = 50;
	float current_RESPTIME = 0;

	int Mat_Choices[10][10][10];
	int Mat_Confidence[10][10][10];
	float Mat_ResponseTime[10][10][10];

	int completed_Reps[10][10];

	// UI Helper
	int present_Screen = 3;

	bool is_NewBlock = false;

	bool isTraining = false;
	short trainingPattern_Random = 0;
	short trainingPattern_Random_z1 = 0;
	short trainingMapping_Slider = 0;
	int training_numTries[10] = { 0,0,0,0,0,0,0,0,0,0 };
	
	void getNew_PatternIdx_Training()
	{
		//trainingPattern_Random_z1 = trainingPattern_Random;
		//while (trainingPattern_Random_z1 == trainingPattern_Random)
		//{
		//	trainingPattern_Random = randGen.nextInt(num_Patterns);
		//}

		int tryIdx_Wrapped = training_numTries[trainingMapping_Slider] % 6;

		trainingPattern_Random = latin_resp_ODD[trainingMapping_Slider][tryIdx_Wrapped + 6] - 1;
	}

	int omsiIndex = 0;
	
	// 1 = File not Played // 2 = File Playing // 3 = Classifying // 4 = Feedback
	short phase_Training = 0;

	LogStore logStore;

	void initializeDataHolders()
	{
		for (int i = 0; i < 10; i++)
		{
			order_Blocks[i] = -1;

			for (int j = 0; j < 50; j++)
				order_PatternsInBlock[i][j] = -1;

			for (int k = 0; k < 10; k++)
			{
				completed_Reps[i][k] = 0;

				for (int l = 0; l < 10; l++)
				{
					Mat_Choices[i][k][l] = 0;
					Mat_Confidence[i][k][l] = 0;
					Mat_ResponseTime[i][k][l] = 0;
				}
			}
		}

		num_Trials_PERBLOCK = num_Patterns * num_Reps;
		num_Trials_TOTAL = num_Blocks * num_Patterns * num_Reps;
	}

	//////////////////////////////////////////////// STORE TRIAL DATA /////////////////////////////////////////////////////////////////////

	void get_TRUE_Block_Pattern_fromTrialIdx(int* block, int* pattern)
	{
		int user_blockIdx = currentTrial / num_Trials_PERBLOCK;
		*block = order_Blocks[user_blockIdx];
		
		int trial_Idx_withinBlock = currentTrial % num_Trials_PERBLOCK;
		*pattern = order_PatternsInBlock[*block][trial_Idx_withinBlock];
	}

	void endTrial()
	{
		int true_Block = -1;
		int true_Pattern = -1;

		get_TRUE_Block_Pattern_fromTrialIdx(&true_Block, &true_Pattern);

		// Store Current Choice and Confidence in Main Matrices, Increment Reps
		Mat_Choices[true_Block][true_Pattern][completed_Reps[true_Block][true_Pattern]] = current_CHOICE;
		Mat_Confidence[true_Block][true_Pattern][completed_Reps[true_Block][true_Pattern]] = current_CONFIDENCE;
		Mat_ResponseTime[true_Block][true_Pattern][completed_Reps[true_Block][true_Pattern]] = current_RESPTIME;

		completed_Reps[true_Block][true_Pattern]++;

		// Increment Trial Count
		currentTrial++;
		
		get_TRUE_Block_Pattern_fromTrialIdx(&true_Block, &true_Pattern);

		if (current_Block != true_Block)
			is_NewBlock = true;
		else is_NewBlock = false;

		current_Block = true_Block;

		// Check for experiment completion
		//if (currentTrial == num_Trials_TOTAL || currentTrial == 19)
		if (currentTrial == num_Trials_TOTAL)
		{
			logStore.storeLog(Mat_Choices, Mat_Confidence, Mat_ResponseTime, order_Blocks, order_PatternsInBlock,
				num_Blocks, num_Patterns, num_Reps, omsiIndex);
			completion = true;
		}
	}

	//////////////////////////////////////////////// ORDER GENERATION //////////////////////////////////////////////////////////////////////

	short latin_resp_ODD[6][18] =
	{
		{1,2,6,3,5,4,	5,6,4,1,3,2,	1,2,6,3,5,4},
		{2,3,1,4,6,5,	6,1,5,2,4,3,	2,3,1,4,6,5},
		{3,4,2,5,1,6,	1,2,6,3,5,4,	3,4,2,5,1,6},
		{4,5,3,6,2,1,	2,3,1,4,6,5,	4,5,3,6,2,1},
		{5,6,4,1,3,2,	3,4,2,5,1,6,	5,6,4,1,3,2},
		{6,1,5,2,4,3,	4,5,3,6,2,1,	6,1,5,2,4,3}
	};

	short latin_resp_EVEN[6][18] =
	{
		{6,1,5,2,4,3,	1,2,6,3,5,4,	6,1,5,2,4,3},
		{5,6,4,1,3,2,	6,1,5,2,4,3,	5,6,4,1,3,2},
		{4,5,3,6,2,1,	5,6,4,1,3,2,	4,5,3,6,2,1},
		{3,4,2,5,1,6,	4,5,3,6,2,1,	3,4,2,5,1,6},
		{2,3,1,4,6,5,	3,4,2,5,1,6,	2,3,1,4,6,5},
		{1,2,6,3,5,4,	2,3,1,4,6,5,	1,2,6,3,5,4}
	};

	void generateOrder()
	{
		bool isEvenParticipant = false;
		short participant_ModNum = 0;
		
		juce::String filePath_LOG = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getFullPathName();
		filePath_LOG = filePath_LOG.upToLastOccurrenceOf("\\", true, false) + "Experiment Logs\\";
		auto dir_Base = juce::File(filePath_LOG);
		int num_ParticipantsDone = dir_Base.getNumberOfChildFiles(2, "*.csv");
		isEvenParticipant = (num_ParticipantsDone % 2 == 0) ? false : true;

		participant_ModNum = (num_ParticipantsDone % 6);

		for (int i = 0; i < num_Blocks; i++)
		{
			// GENERATE RANDOM BLOCK ORDER
			//order_Blocks[i] = //getNewRandomIndex(num_Blocks, i, order_Blocks);
			order_Blocks[i] = latin_resp_ODD[participant_ModNum][i + 6] - 1;


			for (int j = 0; j < num_Trials_PERBLOCK; j++)
			{
				order_PatternsInBlock[i][j] = isEvenParticipant ? latin_resp_EVEN[i][j] : latin_resp_ODD[i][j];
				order_PatternsInBlock[i][j] -= 1;
			}
		}

		// COMMENT
		// order_Blocks[0] = 1;
	}

	juce::Random randGen;
	int getNewRandomIndex(int total, int totalElapsed, int* elapsedIndices)
	{
		int randomIndex = randGen.nextInt(total);
		bool alreadyDone = false;

		for (int i = 0; i < total; i++)
		{
			if (randomIndex == elapsedIndices[i])
				alreadyDone = true;
		} //Check if already done

		while (alreadyDone)
		{
			randomIndex = randGen.nextInt(total);
			alreadyDone = false;
			for (int i = 0; i < total; i++)
			{
				if (randomIndex == elapsedIndices[i])
					alreadyDone = true;
			}
		}

		elapsedIndices[totalElapsed] = randomIndex;
		return randomIndex;
	}

	void getNewIndex_PseudoRandom(int num_Patterns, int num_Reps, int order_PatternsInBlock[][50], int Idx_Block, int trialIdx_InBlock)
	{
		int prevIdx_Trial = order_PatternsInBlock[Idx_Block][(int)fmax(0, trialIdx_InBlock - 1)];
		int numIncidences_PatternIdx[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		for (int i = 0; i < num_Trials_PERBLOCK; i++)
		{
			for (int j = 0; j < num_Patterns; j++)
			{
				if (order_PatternsInBlock[Idx_Block][i] == j)
					numIncidences_PatternIdx[j]++;
			}
		}

		int randIdx_NEW = randGen.nextInt(num_Patterns);

		bool consecutiveCheck_Condition = (randIdx_NEW == prevIdx_Trial) && (trialIdx_InBlock < (num_Trials_PERBLOCK - 1));

		while (consecutiveCheck_Condition || numIncidences_PatternIdx[randIdx_NEW] >= num_Reps)
		{
			randIdx_NEW = randGen.nextInt(num_Patterns);
			consecutiveCheck_Condition = (randIdx_NEW == prevIdx_Trial) && (trialIdx_InBlock < (num_Trials_PERBLOCK - 2));
		}

		order_PatternsInBlock[Idx_Block][trialIdx_InBlock] = randIdx_NEW;
	}

	///////////////////////////////////////////////// TIMEOUT CONDITIONS /////////////////////////////////////////////////////////////////////////

	bool isScreen_TimeLimited[20] = {
		false,
		false,
		false,
		false,
		false,
		false,
		true,
		false,
		true,
		false,
		false,
		false
	};

	float screen_TimeLimit[20] = {
		100,
		100,
		100,
		100,
		100,
		100,
		8.5,																	// CHANGE FOR SOUND SEQUENCE
		15,																	// CHANGE FOR TEST LENGTH
		1.5,																	// CHANGE FOR NOISE SEQUENCE
		100,
		100,
		100
	};

	float presentScreen_TimeLeft = 100;

	void initializeTimer()
	{
		presentScreen_TimeLeft = screen_TimeLimit[present_Screen];
		current_RESPTIME = 0;
	}

	bool decrementTimer(bool isChoiceClicked)
	{
		if (isScreen_TimeLimited[present_Screen])
		{
			presentScreen_TimeLeft -= 0.01;
			if (!isChoiceClicked) current_RESPTIME += 0.01;
		}

		if (!isChoiceClicked) current_RESPTIME += 0.01;
		return presentScreen_TimeLeft <= 0;
	}

	///////////////////////////////////////////////////// LOAD PAST STATE /////////////////////////////////////////////////

	bool loadPastState(juce::String filePath)
	{
		juce::File logFile(filePath);
		juce::FileInputStream inputStream(logFile);

		if (!inputStream.openedOk())
			return false;  // failed to open

		juce::String line_Header = "";
		int linesRead_UnderHeader = 0;

		while (!inputStream.isExhausted())
		{
			auto line = inputStream.readNextLine();
			auto line_Rem = line;
			int colIdx = 0;

			// OMSI
			juce::String line_FirstElement = line.upToFirstOccurrenceOf(",", false, true);
			line_Rem = line_Rem.fromFirstOccurrenceOf(",", false, true);
			if (line_FirstElement == "OMSI Index");
			omsiIndex = line_Rem.upToFirstOccurrenceOf(",", false, true).getIntValue();

			
			if (line.fromFirstOccurrenceOf(",", false, true) == "")
			{
				line_Header = line.upToFirstOccurrenceOf(",", false, true);
				linesRead_UnderHeader = 0;
			}

			else
			{
				if (line_Header == "Block Order")
				{
					while (line != "")
					{
						order_Blocks[colIdx] = line.upToFirstOccurrenceOf(",", false, true).getIntValue();
						line = line.fromFirstOccurrenceOf(",", false, true);
						colIdx++;
					}
				}

				if (line_Header == "Pattern Order in Blocks")
				{
					while (line != "")
					{
						order_PatternsInBlock[linesRead_UnderHeader][colIdx] = line.upToFirstOccurrenceOf(",", false, true).getIntValue();
						line = line.fromFirstOccurrenceOf(",", false, true);
						colIdx++;
					}
					linesRead_UnderHeader++;
				}

				for (int i = 0; i < num_Blocks; i++)
				{
					if (line_Header == "Choice - Block " + juce::String(i))
					{
						while (line != "")
						{							
							Mat_Choices[i][linesRead_UnderHeader][colIdx] = line.upToFirstOccurrenceOf(",", false, true).getIntValue();
							if (Mat_Choices[i][linesRead_UnderHeader][colIdx] != 0)
							{
								completed_Reps[i][linesRead_UnderHeader]++;
								currentTrial++;
							}
							line = line.fromFirstOccurrenceOf(",", false, true);
							colIdx++;
						}
						linesRead_UnderHeader++;
					}

					if (line_Header == "Confidence - Block " + juce::String(i))
					{
						while (line != "")
						{
							Mat_Confidence[i][linesRead_UnderHeader][colIdx] = line.upToFirstOccurrenceOf(",", false, true).getIntValue();
							line = line.fromFirstOccurrenceOf(",", false, true);
							colIdx++;
						}
						linesRead_UnderHeader++;
					}

					if (line_Header == "Response Time - Block " + juce::String(i))
					{
						while (line != "")
						{
							Mat_ResponseTime[i][linesRead_UnderHeader][colIdx] = line.upToFirstOccurrenceOf(",", false, true).getFloatValue();
							line = line.fromFirstOccurrenceOf(",", false, true);
							colIdx++;
						}
						linesRead_UnderHeader++;
					}
				}
			}
		}

		current_Block = order_Blocks[(currentTrial) / num_Trials_PERBLOCK];

		return true;
	}

	////////////////////////////////////////////////// REINFORCEMENT LEARNING LINKS /////////////////////////////////////////

	juce::String videoURLs[6][6] = // B // P
	{
		{
			"https://www.youtube.com/watch?v=Qi6_2L1EyJg",
			"https://www.youtube.com/watch?v=gZkYBgzlw9I",
			"https://www.youtube.com/watch?v=HNtwSYsbWJ8",
			"https://www.youtube.com/watch?v=bxFtCkfvSLk",
			"https://www.youtube.com/watch?v=uxNPw3kL74A",
			"https://www.youtube.com/watch?v=gz6zEdce9ME"
		},

		{
			"https://www.youtube.com/watch?v=8ncRq9c9AKA",
			"https://www.youtube.com/watch?v=Iaq7CKbjtB8",
			"https://www.youtube.com/watch?v=Ljw9sU07uXI",
			"https://www.youtube.com/watch?v=J1XIAeKKzRg",
			"https://www.youtube.com/watch?v=wlBNTyKAq18",
			"https://www.youtube.com/watch?v=LV4vZpQOC-4"
		},

		{
			"https://www.youtube.com/watch?v=9ywD3tv86Io",
			"https://www.youtube.com/watch?v=TV1GcHTK_BM",
			"https://www.youtube.com/watch?v=LTHgeCl-rgU",
			"https://www.youtube.com/watch?v=5YJQ_iumpRo",
			"https://www.youtube.com/watch?v=pe-PXOli7AQ",
			"https://www.youtube.com/watch?v=BtF_H-JEwkU"
		},

		{
			"https://www.youtube.com/watch?v=kZcVRzxhAng",
			"https://www.youtube.com/watch?v=0_6SwE3Xjcw",
			"https://www.youtube.com/watch?v=hayF10fABn8",
			"https://www.youtube.com/watch?v=wj1YSWk45gg",
			"https://www.youtube.com/watch?v=r54tLHkiTfs",
			"https://www.youtube.com/watch?v=cBSIDfsly_k"
		},

		{
			"https://www.youtube.com/watch?v=2mWmA62I0KI",
			"https://www.youtube.com/watch?v=0ExqGdXuvjw",
			"https://www.youtube.com/watch?v=m2z04rWWaQs",
			"https://www.youtube.com/watch?v=GliT91bbg5Q",
			"https://www.youtube.com/watch?v=jEWn7Y5bfm0",
			"https://www.youtube.com/watch?v=Q9cvEj2fbFw"
		},

		{
			"https://www.youtube.com/watch?v=9Ubad-Cd6aw",
			"https://www.youtube.com/watch?v=ZgMFipYpAtY",
			"https://www.youtube.com/watch?v=8x7XNai7REQ",
			"https://www.youtube.com/watch?v=t0i-HZFWXHE",
			"https://www.youtube.com/watch?v=BiBwl7mXW1k",
			"https://www.youtube.com/watch?v=WP-a_e6rsP0"
		}
	};

	juce::String getVideoLinkFull(int block, int pattern)
	{
		return videoURLs[block][pattern];
	}

	////////////////////////////////////////////////// BLOCK DISPLAY ///////////////////////////////////////////////////////

	int numMappings_1_1 = 4;

	juce::String mappingNames_1234[10] =
	{
		"Speed - Blowing Pressure",
		"Progression - Pitch",
		"Rising Stops - Bell",
		"Jerkiness - Glitches"
	};

	bool isMappingPresent_Blockwise[10][4] =
	{
		{true, false, false, false},
		{true, false, false, true},
		{true, true, false, false},
		{true, false, true, true},
		{true, true, true, false},
		{true, true, true, true}
	};
};