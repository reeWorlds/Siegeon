#pragma once

#include "SettingsHolder.h"

#include <nlohmann/json.hpp>
#include <string>


namespace GameSettings
{
	class SettingsFileManager
	{
	public:

		static SettingsHolder loadSettings(std::string path = DEFAULT_PATH_TO_SETTINGS);

		static void saveSettings(const SettingsHolder& settings);


	private:

		static bool checkJson(const nlohmann::json& json);
	};
}
