#include <sys/stat.h>
#include <dirent.h>

#include "ValidationException.h"
#include "FSManager.h"
#include "Utility.h"

bool CFSManager::isDirectory(const std::string& arg_spath)
{
	bool isDir = false;
	struct stat s;
	if (stat(arg_spath.c_str(), &s) == 0)
	{
		if (s.st_mode && S_IFDIR)
		{
			isDir = true;
		}
	}
	return isDir;
}

std::vector<std::string> CFSManager::getFileNames(const std::string& arg_sDirectory,const std::string& arg_sFileExtn)
{
	if (!isDirectory(arg_sDirectory))
	{
		throw CValidationException("Incorrect argument, passed argument should be valid existing directory name");
	}
	
	struct dirent *entry;
	DIR *dir = opendir(arg_sDirectory.c_str());
	if (dir == NULL) 
	{
		throw CValidationException("Unable to list directory,please check your permissions");
	}

	std::vector<std::string> l_vsFileNames;
	while ((entry = readdir(dir)) != NULL) 
	{
		if (CUtility::endsWith(entry->d_name,arg_sFileExtn))
		{
			l_vsFileNames.push_back(arg_sDirectory  + "\\" +  entry->d_name);
		}
		
	}

	closedir(dir);
	return l_vsFileNames;
}
