#include <cassert>
#include <chrono>
#include <thread>

#include "WorldManager.h"
#include "Constants.h"

using SharedStatePtr = std::shared_ptr<GameModule::SharedState>;

using namespace std::chrono;


namespace GameModule
{
	WorldManager::WorldManager(SharedStatePtr sharedState)
	{
		_sharedState = sharedState;
	}
	
	WorldManager::~WorldManager() {}

	void WorldManager::run()
	{
		assert(_sharedState != nullptr && "SharedState is nullptr");

		init();

		_clock.restart();
		_lightTimer = 0.0;
		_heavyTimer = 0.0;

		_runInnerLoop();
	}

	void WorldManager::_runInnerLoop()
	{
		while (true)
		{
			SharedState* sharedStatePtr = _sharedState.get();

			if (sharedStatePtr->m_exitGame)
			{
				break;
			}

			if (sharedStatePtr->m_isRunningSubGameModule)
			{
				std::this_thread::sleep_for(milliseconds(SLEEP_WHEN_INACTIVE_MS));

				continue;
			}

			WorldSwapStatus swapStatus = sharedStatePtr->m_worldSwapStatus;
			if (swapStatus != WorldSwapStatus::INACTIVE)
			{
				std::this_thread::sleep_for(microseconds(SLEEP_TIME_US));

				continue;
			}

			sharedStatePtr->m_isUpdatingWorld = true;

			double elapsedTime = _clock.getElapsedTime().asMicroseconds() / 1000.0;
			_clock.restart();
			_lightTimer += elapsedTime;
			_heavyTimer += elapsedTime;

			devicesUpate();

			if (_lightTimer > MS_PER_LIGHT_UPDATE)
			{
				_lightTimer = std::min(_lightTimer, 2.0 * MS_PER_HEAVY_UPDATE);
				lightUpdate(_lightTimer);
				_lightTimer = 0.0;
			}

			if (_heavyTimer > MS_PER_HEAVY_UPDATE)
			{
				_heavyTimer = std::min(_heavyTimer, 2.0 * MS_PER_HEAVY_UPDATE);
				heavyUpdate(_heavyTimer);
				_heavyTimer = 0.0;
			}

			sharedStatePtr->m_isUpdatingWorld = false;
		}
	}
}
