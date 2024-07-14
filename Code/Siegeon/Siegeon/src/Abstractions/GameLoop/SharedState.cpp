#include "SharedState.h"

namespace GameLoop
{
	SharedState::SharedState()
	{
		m_exitGame = false;

		m_isPaused = false;
		m_isRunningSubGameLoop = false;

		m_isUpdatingState = false;
		m_isUpdatingGraphics = false;

		m_worldStateTransitionState = WorldStateTransitionStatus::TS_INACTIVE;
	}

	SharedState::~SharedState() {};
}