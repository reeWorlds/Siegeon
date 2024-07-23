#include <cassert>
#include <thread>
#include <chrono>

#include "GameModule.h"
#include "Constants.h"

using GameModulePtr = std::shared_ptr<GameModule::GameModule>;
using WorldPtr = std::shared_ptr<GameModule::World>;
using SharedStatePtr = std::shared_ptr<GameModule::SharedState>;
using WorldManagerPtr = std::shared_ptr<GameModule::WorldManager>;
using GraphicsManagerPtr = std::shared_ptr<GameModule::GraphicsManager>;

using namespace std::chrono;


namespace GameModule
{
	GameModule::GameModule() : _worldIndex(0) { }

	GameModule::~GameModule() { }

	void GameModule::_setWorld(int32_t index, WorldPtr world)
	{
		assert(index >= 0 && index < 2 && "Index out of bounds");
		_worlds[index] = world;
	}

	void GameModule::_setSharedState(SharedStatePtr sharedState)
	{
		_sharedState = sharedState;
	}

	void GameModule::_setWorldManager(WorldManagerPtr worldManager)
	{
		_worldManager = worldManager;
	}

	void GameModule::_setGraphicsManager(GraphicsManagerPtr graphicsManager)
	{
		_graphicsManager = graphicsManager;
	}

	int32_t GameModule::_getWorldIndex()
	{
		return _worldIndex;
	}

	void GameModule::run()
	{
		_initOnRun();

		_runLoop();
	}

	void GameModule::runSubGame(GameModulePtr subGame)
	{
		auto runSubGameLoop = [this, subGame]()
			{
				_sharedState->m_isRunningSubGameModule = true;

				assert(subGame != nullptr && "SubGame is nullptr");
				subGame->run();

				_sharedState->m_isRunningSubGameModule = false;
			};

		std::thread subGameThread(runSubGameLoop);
		subGameThread.detach();
	}

	void GameModule::_initOnRun()
	{
		initOnRun();

		assert(_worlds[0] != nullptr && "Worlds[0] is nullptr");
		assert(_worlds[1] != nullptr && "Worlds[1] is nullptr");
		assert(_sharedState != nullptr && "SharedState is nullptr");

		assert(_worldManager != nullptr && "WorldManager is nullptr");
		_worldManager->setWorld(_worlds[_worldIndex]);
		std::thread worldManagerThread(&WorldManager::run, _worldManager);
		worldManagerThread.detach();

		assert(_graphicsManager != nullptr && "GraphicsManager is nullptr");
		_graphicsManager->setWorld(_worlds[_worldIndex ^ 1]);
		std::thread graphicsManagerThread(&GraphicsManager::run, _graphicsManager);
		graphicsManagerThread.detach();
	}

	void GameModule::_runLoop()
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

			if (sharedStatePtr->m_isPaused)
			{
				std::this_thread::sleep_for(microseconds(SLEEP_TIME_US));

				continue;
			}

			WorldSwapStatus transitionStatus = sharedStatePtr->m_worldSwapStatus;
			if (transitionStatus != WorldSwapStatus::INACTIVE)
			{
				_swapWorlds(transitionStatus);

				continue;
			}

			update();
		}
	}

	void GameModule::_swapWorlds(WorldSwapStatus transitionStatus)
	{
		switch (transitionStatus)
		{
		case WorldSwapStatus::INACTIVE:
			assert(false && "Swap status can't be inactive");
			break;

		case WorldSwapStatus::INITIATED:
			if (_sharedState->m_isUpdatingWorld || _sharedState->m_isRendering)
			{
				return;
			}
			_sharedState->m_worldSwapStatus = WorldSwapStatus::SWAPING_STATES;
			break;

		case WorldSwapStatus::SWAPING_STATES:
			_graphicsManager->setWorld(_worlds[_worldIndex]);
			_worldManager->copyWorld(_worlds[_worldIndex], _worlds[_worldIndex ^ 1]);
			_worldManager->setWorld(_worlds[_worldIndex ^ 1]);
			_worldIndex ^= 1;
			_sharedState->m_worldSwapStatus = WorldSwapStatus::INACTIVE;
			break;
		
		default:
			assert(false && "Unknown swap status");
			break;
		}
	}
}