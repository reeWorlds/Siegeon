#include "SharedState.h"

namespace GameModule
{
	SharedState::SharedState()
	{
		m_exitGame = false;

		m_isPaused = false;
		m_isRunningSubGameModule = false;

		m_isUpdatingWorld = false;
		m_isRendering = false;

		m_worldSwapStatus = WorldSwapStatus::INACTIVE;
	}

	SharedState::~SharedState() {};
}