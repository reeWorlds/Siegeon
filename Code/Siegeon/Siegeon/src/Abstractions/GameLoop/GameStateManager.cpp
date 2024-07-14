#include <chrono>
#include <thread>

#include "GameStateManager.h"
#include "../../Constants/GameLoop.h"

using namespace std::chrono;


namespace GameLoop
{
	GameStateManager::GameStateManager(std::shared_ptr<WorldState> worldState, std::shared_ptr<SharedState> sharedState)
	{
		_worldState = worldState;
		_sharedState = sharedState;
	}
	
	GameStateManager::~GameStateManager() {}

	void GameStateManager::run()
	{
		init();

		_clock.restart();
		lightTimer = 0.0;
		heavyTimer = 0.0;

		_runInnerLoop();
	}

	void GameStateManager::_runInnerLoop()
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

			sharedStatePtr->m_isUpdatingState = true;

			double elapsedTime = _clock.getElapsedTime().asMicroseconds() / 1000.0;
			_clock.restart();
			lightTimer += elapsedTime;
			heavyTimer += elapsedTime;

			deviceUpate();

			if (lightTimer > MS_PER_LIGHT_UPDATE)
			{
				lightUpdate(lightTimer);
				lightTimer = 0.0;
			}

			if (heavyTimer > MS_PER_HEAVY_UPDATE)
			{
				heavyUpdate(heavyTimer);
				heavyTimer = 0.0;
			}

			sharedStatePtr->m_isUpdatingState = false;
		}
	}
}
