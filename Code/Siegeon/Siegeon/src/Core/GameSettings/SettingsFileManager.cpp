#include "SettingsFileManager.h"

#include <fstream>


namespace GameSettings
{
	SettingsHolder SettingsFileManager::loadSettings(std::string path)
	{
		std::ifstream file(path);
		if (!file.is_open()) { return SettingsHolder(); }

		nlohmann::json json;
		file >> json;

		if (!checkJson(json)) { return SettingsHolder(); }

		SettingsHolder settings;

		settings.difficultyLevel = static_cast<DifficultyLevel>(json["difficultyLevel"]);
		settings.videoMode = static_cast<VideoMode>(json["videoMode"]);
		settings.resolution = json["resolution"];
		settings.fontName = json["fontName"];
		settings.soundVolume = json["soundVolume"];
		settings.musicVolume = json["musicVolume"];

		if (!settings.checkValidity()) { return SettingsHolder(); }

		return settings;
	}

	void SettingsFileManager::saveSettings(const SettingsHolder& settings)
	{
		std::ofstream file(DEFAULT_PATH_TO_SETTINGS);

		if (!file.is_open())
		{
			throw std::runtime_error("Could not open file to save settings.");
		}

		nlohmann::json json;

		json["difficultyLevel"] = static_cast<int32_t>(settings.difficultyLevel);
		json["videoMode"] = static_cast<int32_t>(settings.videoMode);
		json["resolution"] = settings.resolution;
		json["fontName"] = settings.fontName;
		json["soundVolume"] = settings.soundVolume;
		json["musicVolume"] = settings.musicVolume;

		file << json.dump(4);
	}

	bool SettingsFileManager::checkJson(const nlohmann::json& json)
	{
		if (!json.contains("difficultyLevel") || !json["difficultyLevel"].is_number_integer()) { return false; }
		if (!json.contains("videoMode") || !json["videoMode"].is_number_integer()) { return false; }
		if (!json.contains("resolution") || !json["resolution"].is_string()) { return false; }
		if (!json.contains("fontName") || !json["fontName"].is_string()) { return false; }
		if (!json.contains("soundVolume") || !json["soundVolume"].is_number_float()) { return false; }
		if (!json.contains("musicVolume") || !json["musicVolume"].is_number_float()) { return false; }

		return true;
	}
}