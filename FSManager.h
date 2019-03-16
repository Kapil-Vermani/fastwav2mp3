#ifndef FSMANAGER_H
#define FSMANAGER_H
#include <string>
#include <vector>
class CFSManager
{
private:
	CFSManager() = delete;
	~CFSManager() = delete;
public:
	static bool isDirectory(const std::string& arg_spath);
	static std::vector<std::string> getFileNames(const std::string& arg_sDirectory,const std::string& arg_sFileExtn);
};
#endif
