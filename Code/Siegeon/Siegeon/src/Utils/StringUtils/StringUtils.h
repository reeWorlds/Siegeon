#pragma once

#include <string>
#include <vector>


namespace StringUtils
{
	std::vector<std::string> splitString(const std::string& str, char delimiter = ' ');
}