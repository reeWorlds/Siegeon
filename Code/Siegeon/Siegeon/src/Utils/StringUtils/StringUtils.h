#pragma once

#include <string>
#include <vector>


namespace Utils
{
	namespace StringUtils
	{
		std::string ftos(float x, int precision = 4);
		std::string dtos(double x, int precision = 8);

		std::vector<std::string> splitString(const std::string& str, char delimiter = ' ');
	}
}