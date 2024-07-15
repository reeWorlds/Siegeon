#pragma once

#include <atomic>

#include "Constants.h"


namespace GameModule
{
	class SharedState
	{
	public:

		std::atomic_bool m_exitGame;

		std::atomic_bool m_isPaused;
		std::atomic_bool m_isRunningSubGameModule;

		std::atomic_bool m_isUpdatingWorld;
		std::atomic_bool m_isRendering;

		std::atomic<WorldSwapStatus> m_worldSwapStatus;


		SharedState();
		virtual ~SharedState();

	};
}
