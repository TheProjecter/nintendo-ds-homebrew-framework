#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>

namespace Helper
{
	static std::string GetFileExtension(const std::string& filename)
	{
		// find the last dot and then then create a string from whats left
		if(filename.find_last_of(".") != std::string::npos)
		{
			return filename.substr(filename.find_last_of(".") + 1);
		}

		// return nothing if not found
		return "";
	}
}

#endif