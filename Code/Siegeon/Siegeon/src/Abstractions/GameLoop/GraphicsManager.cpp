#include <chrono>
#include <thread>

#include "GraphicsManager.h"
#include "../../Constants/GameLoop.h"

using namespace std::chrono;


namespace GameLoop
{
	GraphicsManager::GraphicsManager(std::shared_ptr<WorldState> worldState, std::shared_ptr<SharedState> sharedState)
	{
		_worldState = worldState;
		_sharedState = sharedState;
	}

	GraphicsManager::~GraphicsManager() {}

	void GraphicsManager::run()
	{
		init();

		_clock.restart();
		timer = 0.0;

		_runInnerLoop();
	}

	void GraphicsManager::_runInnerLoop()
	{
		while (true)
		{
			SharedState* sharedStatePtr = _sharedState.get();

			if (sharedStatePtr->m_exitGame)
			{
				break;
			}

			if (sharedStatePtr->m_isRunningSubGameLoop)
			{
				std::this_thread::sleep_for(milliseconds(SLEEP_WHEN_INACTIVE_MS));

				continue;
			}

			WorldStateTransitionStatus transitionStatus = sharedStatePtr->m_worldStateTransitionState;
			if (transitionStatus != WorldStateTransitionStatus::TS_INACTIVE)
			{
				std::this_thread::sleep_for(microseconds(SLEEP_TIME_US));

				continue;
			}

			sharedStatePtr->m_isUpdatingGraphics = true;

			timer += _clock.getElapsedTime().asMicroseconds() / 1000.0;
			_clock.restart();

			if (timer > MS_PER_FRAME)
			{
				timer -= MS_PER_FRAME;
				timer = std::min(timer, (double)MS_PER_FRAME);

				render();

				sharedStatePtr->m_isUpdatingGraphics = false;
			}
			else
			{
				sharedStatePtr->m_isUpdatingGraphics = false;

				std::this_thread::sleep_for(microseconds(SLEEP_TIME_US));
			}
		}
	}
}