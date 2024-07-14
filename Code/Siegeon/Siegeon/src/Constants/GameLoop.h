// Notations:
// MS = Milliseconds
// US = Microseconds
// TS = Transition State

#pragma once

#include <stdint.h>


namespace GameLoop
{
	inline constexpr int32_t FPS = 50;
	inline constexpr int32_t MS_PER_FRAME = 1000 / FPS; // 20ms

	inline constexpr int32_t MS_PER_LIGHT_UPDATE = 1;
	inline constexpr int32_t MS_PER_HEAVY_UPDATE = 5;

	inline constexpr int32_t SLEEP_TIME_US = 100;
	inline constexpr int32_t SLEEP_WHEN_INACTIVE_MS = 20;

	enum class WorldStateTransitionStatus
	{
		TS_INACTIVE,
		TS_INITIATED,
		TS_SWITCHING_STATES,
	};
}