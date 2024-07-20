#pragma once

#include "Constants.h"

#include <stdint.h>
#include <string>
#include <SFML/System.hpp>


namespace GameSettings
{
	class SettingsHolder
	{
	public:

		DifficultyLevel difficultyLevel;

		VideoMode videoMode;
		std::string resolution;

		int32_t uiScale;
		std::string fontName;

		double soundVolume;
		double musicVolume;


		SettingsHolder();
		~SettingsHolder();

		sf::Vector2i getResolutionInt() const;

		bool checkValidity() const;

	};
}