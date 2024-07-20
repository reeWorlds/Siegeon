#pragma once

#include "SettingsHolder.h"


namespace GameSettings
{
	class GameSettings
	{
	public:
		
		static GameSettings& getInstance();

		DifficultyLevel getDifficultyLevel() const;
		VideoMode getVideoMode() const;
		std::string getResolution() const;
		sf::Vector2i getResolutionInt() const;
		int32_t getUiScale() const;
		std::string getFontName() const;
		double getSoundVolume() const;
		double getMusicVolume() const;


	private:

		SettingsHolder _settings;


		GameSettings();
		~GameSettings();
		
		GameSettings(const GameSettings&) = delete;
		GameSettings& operator=(const GameSettings&) = delete;
		GameSettings(GameSettings&&) = delete;
		GameSettings& operator=(GameSettings&&) = delete;

	};
}