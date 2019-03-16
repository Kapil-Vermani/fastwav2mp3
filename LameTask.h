#ifndef LAME_TASK_H
#define LAME_TASK_H

#include "lame.h"
#include "LameSettings.h"
#include <string>
class CLameTask
{
private:
	//Helper function to set album art
	/**
	@param gfp : lame global function pointer
	@param arg_pcFileName :  image filename
	@return
	*/
	void setAlbumArt(lame_t gfp, char const* arg_pcFileName);

	//This function will print error message to console for now
	/**
	@param msg: input error message
	*/
	void errorHandler(const std::string& msg);

private:
	std::string m_sInputFileName;
	std::string m_sOutputFileName;
	Settings m_cSettings;

public:
	CLameTask(const std::string& arg_sInputFileName, const std::string& arg_sOutputFileName, const Settings& arg_cSettings=Settings()) :m_sInputFileName(arg_sInputFileName),
		m_sOutputFileName(arg_sOutputFileName), m_cSettings(arg_cSettings)
	{

	}
	~CLameTask()
	{

	}
	
	/**
	//Encode Single WAV File to MP3 File using lame library
	@ return : It will return error code if there is issue otherwise for success it will return 0
	*/
	void operator()();
	
};
#endif