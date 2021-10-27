#pragma once
#include <ctime>
#include "../JuceLibraryCode/JuceHeader.h"
#include "windows.h"

class LogStore
{
public:
	LogStore()
	{

	}

	~LogStore()
	{

	}

	juce::Time currentDateTime;
	FILE* fileObj;
	juce::File forRootDirectory;
	juce::String filePath_LOG = "";
	juce::String format = "%s,\n";

	void storeLog(
		int Mat_Choices[10][10][10], 
		int Mat_Confidence[10][10][10], 
		float Mat_Time[10][10][10],
		int Order_Blocks[10],
		int Order_PatternsInBlocks[10][50],
		int num_Blocks,
		int num_Patterns,
		int num_Reps,
		int omsiIndex)
	{
		// Create File
		filePath_LOG = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getFullPathName();
		filePath_LOG = filePath_LOG.upToLastOccurrenceOf("\\", true, false) + "Experiment Logs\\PARTICIPANT_" + 
						getCurrentTime() + ".csv";
		fileObj = fopen(filePath_LOG.toStdString().c_str(), "w");

		juce::String lineData = "";

		// Store OMSI
		fprintf(fileObj, format.toStdString().c_str(), ("OMSI Index," + juce::String(omsiIndex)));
		lineData = "";

		// Store Block Order
		fprintf(fileObj, format.toStdString().c_str(), "Block Order");
		for (int i = 0; i < num_Blocks; i++)
			lineData += juce::String(Order_Blocks[i]) + ",";

		fprintf(fileObj, format.toStdString().c_str(), lineData);

		// Store Pattern Order in Blocks
		fprintf(fileObj, format.toStdString().c_str(), "Pattern Order in Blocks");

		for (int i = 0; i < num_Blocks; i++)
		{
			lineData = "";
			for (int j = 0; j < num_Patterns * num_Reps; j++)
			{
				lineData += juce::String(Order_PatternsInBlocks[i][j]) + ",";
			}
			fprintf(fileObj, format.toStdString().c_str(), lineData);
		}

		// <FOR EACH BLOCK, PATTERN, REP>
		// Store Choices
		for (int i = 0; i < num_Blocks; i++)
		{
			fprintf(fileObj, format.toStdString().c_str(), "Choice - Block " + juce::String(i));
			for (int j = 0; j < num_Patterns; j++)
			{
				lineData = "";
				for (int k = 0; k < num_Reps; k++)
				{
					lineData += juce::String(Mat_Choices[i][j][k]) + ",";
				}
				fprintf(fileObj, format.toStdString().c_str(), lineData);
			}
		}

		// Store Confidence
		for (int i = 0; i < num_Blocks; i++)
		{
			fprintf(fileObj, format.toStdString().c_str(), "Confidence - Block " + juce::String(i));
			for (int j = 0; j < num_Patterns; j++)
			{
				lineData = "";
				for (int k = 0; k < num_Reps; k++)
				{
					lineData += juce::String(Mat_Confidence[i][j][k]) + ",";
				}
				fprintf(fileObj, format.toStdString().c_str(), lineData);
			}
		}

		// Store Confidence
		for (int i = 0; i < num_Blocks; i++)
		{
			fprintf(fileObj, format.toStdString().c_str(), "Response Time - Block " + juce::String(i));
			for (int j = 0; j < num_Patterns; j++)
			{
				lineData = "";
				for (int k = 0; k < num_Reps; k++)
				{
					lineData += juce::String(Mat_Time[i][j][k]) + ",";
				}
				fprintf(fileObj, format.toStdString().c_str(), lineData);
			}
		}

		// Close File
		fclose(fileObj);
	}

	// Returns Current Time
	juce::String getCurrentTime()
	{
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H-%M-%S", timeinfo);
		std::string str(buffer);

		return juce::String(str);
	}
};

