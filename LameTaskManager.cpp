#include "LameTaskManager.h"
#include <thread>
#include <functional>

void CLameTaskManager::startComputation()
{
	auto numOfThreads = std::thread::hardware_concurrency();
	for (unsigned int i = 0; i < numOfThreads; i++)
	{
		m_vThreads.push_back(std::thread(&CLameTaskManager::compute,this));
	}
}

void CLameTaskManager::compute()
{
	std::shared_ptr<CLameTask> ptrTask;	
	while(true)
	{
		{
			std::lock_guard<std::mutex> lgTask(qMutex);
			if (!qtasks.empty())
			{
				ptrTask = qtasks.front();
				qtasks.pop();
			}
			else
			{
				break;
			}
		}
		if (ptrTask)
		{
			(*ptrTask)();
		}
		
	}
	
}		

CLameTaskManager::~CLameTaskManager()
{
	for (auto&th : m_vThreads)
	{
		th.join();
	}
}

void CLameTaskManager::addTask(const std::string& arg_sInputFileName, const std::string& arg_sOutputFileName)
{
	qtasks.push(std::make_shared<CLameTask>(arg_sInputFileName, arg_sOutputFileName));
}