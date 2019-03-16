#include <iostream>
#include "ApplicationManager.h"
#include "LameTaskManager.h"
#include "AppConstants.h"

void CApplicationManager::encodeFiles(const std::vector<std::string>& arg_sInputPCMFiles, const Settings& arg_cSettings)
{
	CLameTaskManager l_cTaskManager;
	for (const auto& l_sInputFileName:arg_sInputPCMFiles)
	{
		auto l_sOutputFileName = l_sInputFileName;
		auto extensionPos = l_sOutputFileName.find(WAV_EXTENSION);
		if (extensionPos != std::string::npos)
		{
			l_sOutputFileName = l_sInputFileName.substr(0, extensionPos);
			l_sOutputFileName += MP3_EXTENSION;
			l_cTaskManager.addTask(l_sInputFileName, l_sOutputFileName);
		}
	}
	l_cTaskManager.startComputation();	
}

