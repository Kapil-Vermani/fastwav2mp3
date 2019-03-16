#include "Utility.h"


bool CUtility::endsWith(const std::string& arg_sInput, const std::string& arg_sEndsWith)
{
	bool isEndWith = false;
	if (arg_sInput.size() >= arg_sEndsWith.size())
	{
		const auto& l_sEndsWith = arg_sInput.substr(arg_sInput.size() - arg_sEndsWith.size());
		if (l_sEndsWith == arg_sEndsWith)
		{
			isEndWith = true;
		}
	}
	return isEndWith;
}