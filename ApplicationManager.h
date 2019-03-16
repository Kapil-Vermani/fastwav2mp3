#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H
#include <string>
#include <vector>
#include "LameSettings.h"
#include "lame.h"

class CApplicationManager
{
public:
	/** Member Function : This function convert multiple wav files to mp3 file efficiently using c++11 multithreading
	*  @param arg_sInputPCMFiles set of input pcm files
	   It will convert and create mp3 file at that location only with same filename
	   @return : It will return error code if there is issue otherwise for success it will return 0
	*/
	void encodeFiles(const std::vector<std::string>& arg_sInputPCMFiles,const Settings& arg_cSettings = Settings());
	
};
#endif
