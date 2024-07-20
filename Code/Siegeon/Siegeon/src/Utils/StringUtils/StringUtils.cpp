#include "StringUtils.h"

#include <sstream>


namespace StringUtils
{
	std::string ftos(float x, int precision)
	{
		std::ostringstream out;

		out.precision(precision);
		out << std::fixed << x;

		return out.str();
	}

	std::string dtos(double x, int precision)
	{
		std::ostringstream out;

		out.precision(precision);
		out << std::fixed << x;
		
		return out.str();
	}

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
