#pragma once

#include <stdint.h>
#include <SFML/System.hpp>


namespace GameSettings
{
	inline constexpr const char* DEFAULT_PATH_TO_SETTINGS = "resources/settings.json";

	enum class DifficultyLevel : int32_t
	{
		EASY,
		MEDIUM,
		HARD,
	};

	enum class VideoMode : int32_t
	{
		WINDOWED,
		FULLSCREEN,
	};
	
	inline constexpr DifficultyLevel DEFAULT_DIFFICULTY_LEVEL = DifficultyLevel::EASY;

	inline constexpr VideoMode DEFAULT_VIDEO_MODE = VideoMode::WINDOWED;
	inline constexpr const char* DEFAULT_RESOLUTION = "1280x720";
	inline const sf::Vector2i DEFAULT_RESOLUTION_INT = sf::Vector2i(1280, 720);

	inline constexpr const char* DEFAULT_FONT_NAME = "Orbitron-Medium";

	inline constexpr double MIN_VOLUME = 0.0;
	inline constexpr double MAX_VOLUME = 100.0;
	inline constexpr double DEFAULT_SOUND_VOLUME = 50.0;
	inline constexpr double DEFAULT_MUSIC_VOLUME = 50.0;

	inline constexpr const char* POSSIBLE_WINDOWED_RESOLUTIONS[] =
	{
		"800x600", "1280x720", "1366x768", "1600x900", "1920x1080"
	};
}