#include "GameSettings.h"
#include "SettingsFileManager.h"


namespace GameSettings
{
	GameSettings& GameSettings::getInstance()
	{
		static GameSettings instance;

		return instance;
	}

	DifficultyLevel GameSettings::getDifficultyLevel() const
	{
		return _settings.difficultyLevel;
	}

	VideoMode GameSettings::getVideoMode() const
	{
		return _settings.videoMode;
	}

	std::string GameSettings::getResolution() const
	{
		return _settings.resolution;
	}
	
	sf::Vector2i GameSettings::getResolutionInt() const
	{
		return _settings.getResolutionInt();
	}
	
	std::string GameSettings::getFontName() const
	{
		return _settings.fontName;
	}
	
	double GameSettings::getSoundVolume() const
	{
		return _settings.soundVolume;
	}
	
	double GameSettings::getMusicVolume() const
	{
		return _settings.musicVolume;
	}

	GameSettings::GameSettings()
	{
		_settings = SettingsFileManager::loadSettings();
	}

	GameSettings::~GameSettings()
	{
		SettingsFileManager::saveSettings(_settings);
	}
}