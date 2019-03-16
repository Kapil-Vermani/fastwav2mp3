#ifndef LAME_TASKMGR_H
#define LAME_TASKMGR_H

#include <vector>
#include <mutex>
#include <queue>
#include <memory>
#include "LameSettings.h"
#include "LameTask.h"
class CLameTaskManager
{

private:
	void compute();
	std::vector<std::thread> m_vThreads;
	std::queue <std::shared_ptr<CLameTask>> qtasks;
	std::mutex qMutex;
public:
	/*
		We will be joining threads in destructor
	*/
	~CLameTaskManager();
	
	/** Member Function : This function creates std::function task corresponding to each input file that can be later used in multithreading
	*  @param1 arg_sInputFileName : Input MP3 file
	   @param2 arg_sOutputFileName : Output WAV file 	
	*/
	void addTask(const std::string& arg_sInputFileName, const std::string& arg_sOutputFileName);
	
	/** Member Function : This function start conversion of multiple mp3 files to wav files using c++11 threading and here we are
	                      starting threads equal to number of cores 
						  All threads started by this function will pick up one task from task queue 
	*/
	void startComputation();
};
#endif
