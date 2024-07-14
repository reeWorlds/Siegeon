#include <cassert>
#include <chrono>
#include <thread>

#include "GraphicsManager.h"
#include "../../Constants/GameModule.h"

using SharedStatePtr = std::shared_ptr<GameModule::SharedState>;

using namespace std::chrono;


namespace GameModule
{
	GraphicsManager::GraphicsManager(SharedStatePtr sharedState)
	{
		_sharedState = sharedState;
	}

	GraphicsManager::~GraphicsManager() {}

	void GraphicsManager::run()
	{
		assert(_sharedState != nullptr && "SharedState is nullptr");

		init();

		_clock.restart();
		_timer = 0.0;

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

			sharedStatePtr->m_isRendering = true;

			_timer += _clock.getElapsedTime().asMicroseconds() / 1000.0;
			_clock.restart();

			if (_timer > MS_PER_FRAME)
			{
				_timer -= MS_PER_FRAME;
				_timer = std::min(_timer, (double)MS_PER_FRAME);

				render();

				sharedStatePtr->m_worldSwapStatus = WorldSwapStatus::INITIATED;

				sharedStatePtr->m_isRendering = false;
			}
			else
			{
				sharedStatePtr->m_isRendering = false;

				std::this_thread::sleep_for(microseconds(SLEEP_TIME_US));
			}
		}
	}
}