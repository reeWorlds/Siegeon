#pragma once

#include <atomic>

#include "../../Constants/GameLoop.h"


namespace GameLoop
{
	class SharedState
	{
	public:

		std::atomic_bool m_exitGame;

		std::atomic_bool m_isPaused;
		std::atomic_bool m_isRunningSubGameLoop;

		std::atomic_bool m_isUpdatingState;
		std::atomic_bool m_isUpdatingGraphics;

		std::atomic<WorldStateTransitionStatus> m_worldStateTransitionState;


		SharedState();
		virtual ~SharedState();

	};
}
