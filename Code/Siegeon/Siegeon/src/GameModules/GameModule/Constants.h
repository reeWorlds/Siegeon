// Notations:
// MS = Milliseconds
// US = Microseconds

#pragma once

#include <stdint.h>


namespace GameModule
{
	inline constexpr const int32_t FPS = 50;
	inline constexpr const int32_t MS_PER_FRAME = 1000 / FPS; // 20ms

	inline constexpr const int32_t MS_PER_LIGHT_UPDATE = 1;
	inline constexpr const int32_t MS_PER_HEAVY_UPDATE = 10;

	inline constexpr const int32_t SLEEP_TIME_US = 100;
	inline constexpr const int32_t SLEEP_WHEN_INACTIVE_MS = 20;

	enum class WorldSwapStatus
	{
		INACTIVE,
		INITIATED,
		SWAPING_STATES,
	};
}