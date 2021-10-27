#pragma once
#include <JuceHeader.h>

class AudioFileContainer
{
public:
	AudioFileContainer(int numBlocks, int numPatterns)
	{
		for (int i = 0; i < numBlocks; i++)
		{
			// INITIALIZE FILE CONTAINER DATA AS ZERO
			for (int j = 0; j < numPatterns; j++)
			{
				for (int k = 0; k < 600000; k++)
				{
					for (int l = 0; l < 2; l++)
					{
						audioData_TEST[i][j][k][l] = 0;
						audioData_TRAIN[i][j][k][l] = 0;
					}
				}
			}
		}

		// POPULATE TRAINING SET TOO
		populateFiles("Audio Files_TRAINING",true);
		populateFiles("Audio Files_TESTING",false);
	}

	~AudioFileContainer()
	{

	}

	// Blockwise Containers for Audio Data, ADD EXTRA DIMENSION FOR 
	float audioData_TEST[7][10][600000][2];
	float audioData_TRAIN[7][10][600000][2];

	int num_Files = 0;

	// Helper Variables
	int readIndex_audioFiles = 0;
	int sampleLength_audioFiles = 0;
	bool trigger_z1 = false;
	bool isPlaying = false;
	bool isComplete_lastFile = false;

	// CURRENT FILE
	int bufferNum_Present = 0;

	void populateFiles(juce::String name_subDir, bool isTrainingSet)
	{
		juce::AudioFormatManager formatManager;
		formatManager.registerBasicFormats();

		juce::AudioFormat* audioFormat = formatManager.getDefaultFormat();

		juce::String filePath = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getFullPathName();
		filePath = filePath.upToLastOccurrenceOf("\\", true, false) + name_subDir + "\\";

		auto dir_Base = juce::File(filePath);
		num_Files = dir_Base.getNumberOfChildFiles(2, "*.wav");
		auto audioFiles = dir_Base.findChildFiles(2, false, "*.wav");
		audioFiles.sort();
		juce::File currentFile;

		for (int i = 0; i < num_Files; i++)
		{
			currentFile = audioFiles[i];
			juce::String currentFile_Name = currentFile.getFileNameWithoutExtension();
			int blockNum = currentFile_Name.fromFirstOccurrenceOf("B", false, false).upToFirstOccurrenceOf(" ", false, false).getIntValue();
			
			currentFile_Name = currentFile_Name.fromFirstOccurrenceOf("P", false, false);
			int patternNum = currentFile_Name.upToFirstOccurrenceOf("-", false, false).getIntValue();

			juce::MemoryMappedAudioFormatReader* reader = audioFormat->createMemoryMappedReader(currentFile.getFullPathName());
			reader->mapEntireFile();
			auto sampleRange = reader->getMappedSection();
			sampleLength_audioFiles = sampleRange.getEnd();

			float stereoFrame[2] = { 0,0 };

			for (int j = 0; j < sampleLength_audioFiles; j++)
			{
				reader->getSample(j, stereoFrame);

				if (isTrainingSet)
				{
					audioData_TRAIN[blockNum - 1][patternNum - 1][j][0] = stereoFrame[0];
					audioData_TRAIN[blockNum - 1][patternNum - 1][j][1] = stereoFrame[1];
				}

				else
				{
					audioData_TEST[blockNum - 1][patternNum - 1][j][0] = stereoFrame[0];
					audioData_TEST[blockNum - 1][patternNum - 1][j][1] = stereoFrame[1];
				}
			}
		}
	}

	float playFile(bool trigger, int blockNum, int patternNum, int channel, int smplIdx, int bufferSize, bool isTraining)
	{
		float output = 0.0;

		// IF NOT PRESENTLY PLAYING
		if (!isPlaying)
		{
			// IF NOTHING THEN PLAY NOTHING
			if (!trigger_z1 && !trigger)
			{
				trigger_z1 = trigger;
				return output;
			}

			// IF TRIGGER THEN START PLAYING
			if (trigger && !trigger_z1)
			{
				isComplete_lastFile = false;
				isPlaying = true;
			}
		}

		else
		{
			// HANDLE SWIFT FILE CHANGE
			if (trigger && !trigger_z1)
				bufferNum_Present = 0;

			// FETCH PRESENT OUTPUT SAMPLE
			readIndex_audioFiles = bufferSize * bufferNum_Present + smplIdx;
			if (isTraining)
				output = juce::jlimit(-1.0, 1.0, (double)audioData_TRAIN[blockNum][patternNum][readIndex_audioFiles][0]);
			else
				output = juce::jlimit(-1.0, 1.0, (double)audioData_TEST[blockNum][patternNum][readIndex_audioFiles][0]);

			if (channel == 1)
			{
				if (isTraining)
					output = juce::jlimit(-1.0, 1.0, (double)audioData_TRAIN[blockNum][patternNum][readIndex_audioFiles][1]);
				else
					output = juce::jlimit(-1.0, 1.0, (double)audioData_TEST[blockNum][patternNum][readIndex_audioFiles][1]);

				// INCREMENT BUFFER NUMBER FOR PRESENT FILE    
				if (smplIdx == bufferSize - 1)
					bufferNum_Present++;

				// STOP PLAYBACK IF FILE EXHAUSTED
				if (readIndex_audioFiles >= sampleLength_audioFiles - 1)
				{
					isComplete_lastFile = true;
					bufferNum_Present = 0;
					isPlaying = false;
				}
			}
		}

		return output;
	}

	juce::Random RandGen;
	float generateNoise(bool toTrigger)
	{
		if (toTrigger)
		{
			return 0.05 * (RandGen.nextFloat() * 2 - 1);
		}
		else return 0;
	}
};
