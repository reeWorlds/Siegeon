#include "StringUtils.h"

#include <sstream>


namespace StringUtils
{
	std::vector<std::string> splitString(const std::string& str, char delimiter)
	{
		std::vector<std::string> result;
		std::string token;
		std::istringstream tokenStream(str);

		while (std::getline(tokenStream, token, delimiter))
		{
			result.push_back(token);
		}

		return result;
	}
}
