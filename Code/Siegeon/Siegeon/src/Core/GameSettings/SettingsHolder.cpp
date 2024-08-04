#include "SettingsHolder.h"
#include "../../Resources/FontManager/FontManager.h"
#include "../../Utils/StringUtils/StringUtils.h"

#include <SFML/Graphics.hpp>

using namespace StringUtils;


namespace GameSettings
{
	SettingsHolder::SettingsHolder()
	{
		difficultyLevel = DEFAULT_DIFFICULTY_LEVEL;

		videoMode = DEFAULT_VIDEO_MODE;
		resolution = DEFAULT_RESOLUTION;

		std::vector<std::string> availableFonts = FontManager::FontManager::getInstance().getListOfFonts();
		fontName = availableFonts[0];
		for (auto& _fontName : availableFonts)
		{
			if (_fontName == DEFAULT_FONT_NAME)
			{
				fontName = _fontName;
				break;
			}
		}

		soundVolume = DEFAULT_SOUND_VOLUME;
		musicVolume = DEFAULT_MUSIC_VOLUME;
	}

	SettingsHolder::~SettingsHolder()
	{

	}

	sf::Vector2i SettingsHolder::getResolutionInt() const
	{
		std::vector<std::string> size = splitString(resolution, 'x');
		int32_t width = std::stoi(size[0]);
		int32_t height = std::stoi(size[1]);

		return sf::Vector2i(width, height);
	}

	bool SettingsHolder::checkValidity() const
	{
		int32_t checkSum = 0;

		for (auto _difficulty : { DifficultyLevel::EASY, DifficultyLevel::MEDIUM, DifficultyLevel::HARD })
		{
			if (difficultyLevel == _difficulty) { checkSum++; break; }
		}

		for (auto _videoModeType : { VideoMode::WINDOWED, VideoMode::FULLSCREEN })
		{
			if (videoMode == _videoModeType) { checkSum++; break; }
		}

		if (videoMode == VideoMode::WINDOWED)
		{
			for (auto _resolution : POSSIBLE_WINDOWED_RESOLUTIONS)
			{
				if (resolution == _resolution) { checkSum++; break; }
			}
		}
		else if (videoMode == VideoMode::FULLSCREEN)
		{
			sf::Vector2i resolutionInt = getResolutionInt();
			int32_t width = resolutionInt.x;
			int32_t height = resolutionInt.y;

			for (auto& _videoMode : sf::VideoMode::getFullscreenModes())
			{
				if (_videoMode.width == width && _videoMode.height == height) { checkSum++; break; }
			}
		}

		for (auto& _fontName : FontManager::FontManager::getInstance().getListOfFonts())
		{
			if (fontName == _fontName) { checkSum++; break; }
		}

		if (soundVolume >= MIN_VOLUME && soundVolume <= MAX_VOLUME) { checkSum++; }
		if (musicVolume >= MIN_VOLUME && musicVolume <= MAX_VOLUME) { checkSum++; }

		if (checkSum == 6) { return true; }

		return false;
	}
}