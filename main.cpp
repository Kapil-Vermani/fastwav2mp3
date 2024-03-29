// main.cpp : Defines the entry point for the console application.
//

#include "FSManager.h"
#include "ApplicationManager.h"
#include "ValidationException.h"
#include <iostream>
#include <stdio.h>
#include <sstream>

void showErrorMsgAndExit(const std::string& arg_sMessage,int arg_nStatus)
{
	std::cerr << arg_sMessage << std::endl;
	exit(arg_nStatus);
}

int main(int argc,char* argv[])
{
	/**
	Parsing command line arguments
	*/
	if (argc != 2)
	{
		showErrorMsgAndExit("Incorrect number of arguments,application expects single command line argument i.e. directory name", 1);
	}
	
	/**
	 Our complete application should be in try/catch so that we can have single exit point 
	 that makes it convenient for others to follow the code flow
	*/
	try
	{
		CApplicationManager l_cAppManager;
		std::string directoryName = argv[1];
		const auto& l_vsFileNames = CFSManager::getFileNames(directoryName,".wav");
		l_cAppManager.encodeFiles(l_vsFileNames);
	}
	catch (const CValidationException& e)
	{
		std::stringstream errStream;
		errStream << "Internal Validation Exception Occured ..." << e.what();
		showErrorMsgAndExit(errStream.str(), 1);
	}
	catch (const std::exception& e)
	{
		std::stringstream errStream;
		errStream << "Standard Exception occured ..." << e.what();
		showErrorMsgAndExit(errStream.str(), 1);
	}
	catch (...)
	{
		showErrorMsgAndExit("Unknown Exception occured ...", 1);
	}
	return 0;
}

