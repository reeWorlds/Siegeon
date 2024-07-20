#pragma once

#include <stdint.h>


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
	
	inline constexpr const DifficultyLevel DEFAULT_DIFFICULTY_LEVEL = DifficultyLevel::EASY;

	inline constexpr const VideoMode DEFAULT_VIDEO_MODE = VideoMode::WINDOWED;
	inline constexpr const char* DEFAULT_RESOLUTION = "1280x720";

	inline constexpr const int32_t DEFAULT_UI_SCALE = 100;
	inline constexpr const char* DEFAULT_FONT_NAME = "Orbitron-Medium";

	inline constexpr const double MIN_VOLUME = 0.0;
	inline constexpr const double MAX_VOLUME = 100.0;
	inline constexpr const double DEFAULT_SOUND_VOLUME = 50.0;
	inline constexpr const double DEFAULT_MUSIC_VOLUME = 50.0;

	inline constexpr const char* POSSIBLE_WINDOWED_RESOLUTIONS[] =
	{
		"800x600", "1280x720", "1366x768", "1600x900", "1920x1080"
	};

	inline constexpr const int32_t POSSIBLE_UI_SCALES[] = { 50, 75, 100, 125, 150 };
}