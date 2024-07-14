#include <cassert>
#include <thread>
#include <chrono>

#include "GameModule.h"
#include "../../Constants/GameLoop.h"

using GameModulePtr = std::shared_ptr<GameLoop::GameModule>;
using WorldStatePtr = std::shared_ptr<GameLoop::WorldState>;
using SharedStatePtr = std::shared_ptr<GameLoop::SharedState>;
using GameStateManagerPtr = std::shared_ptr<GameLoop::GameStateManager>;
using GraphicsManagerPtr = std::shared_ptr<GameLoop::GraphicsManager>;

using namespace std::chrono;


namespace GameLoop
{
	GameModule::GameModule(): _activeWorldState(0) {}

	GameModule::~GameModule() { }

	void GameModule::setWorldState(int32_t index, std::shared_ptr<WorldState> state)
	{
		assert(index >= 0 && index < 2 && "Index out of bounds");
		_worldState[index] = state;
	}

	void GameModule::setSharedState(std::shared_ptr<SharedState> state)
	{
		_sharedState = state;
	}

	void GameModule::setGameStateManager(std::shared_ptr<GameStateManager> state)
	{
		_gameStateManager = state;
	}

	void GameModule::setGraphicsManager(std::shared_ptr<GraphicsManager> state)
	{
		_graphicsManager = state;
	}

	void GameModule::run()
	{
		_initOnRun();

		_runLoop();
	}

	void GameModule::runSubGameLoop(std::shared_ptr<GameModule> subGame)
	{
		auto runSubGameLoop = [this, subGame]()
		{
			_sharedState->m_isRunningSubGameLoop = true;

			assert(subGame != nullptr && "SubGame is nullptr");
			subGame->run();

			_sharedState->m_isRunningSubGameLoop = false;
		};

		std::thread subGameThread(runSubGameLoop);
		subGameThread.detach();
	}

	void GameModule::_initOnRun()
	{
		initOnRun();

		assert(_worldState[0] != nullptr && "WorldState[0] is nullptr");
		assert(_worldState[1] != nullptr && "WorldState[1] is nullptr");
		assert(_sharedState != nullptr && "SharedState is nullptr");

		assert(_gameStateManager != nullptr && "GameStateManager is nullptr");
		std::thread gameStateManagerThread(&GameStateManager::run, _gameStateManager);
		gameStateManagerThread.detach();

		assert(_graphicsManager != nullptr && "GraphicsManager is nullptr");
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

			if (sharedStatePtr->m_isRunningSubGameLoop)
			{
				std::this_thread::sleep_for(milliseconds(SLEEP_WHEN_INACTIVE_MS));

				continue;
			}

			if (sharedStatePtr->m_isPaused)
			{
				std::this_thread::sleep_for(microseconds(SLEEP_TIME_US));

				continue;
			}

			WorldStateTransitionStatus transitionStatus = sharedStatePtr->m_worldStateTransitionState;
			if (transitionStatus != WorldStateTransitionStatus::TS_INACTIVE)
			{
				_switchWorldState(transitionStatus);

				continue;
			}

			update();
		}
	}

	void GameModule::_switchWorldState(WorldStateTransitionStatus transitionStatus)
	{
		switch (transitionStatus)
		{
		case WorldStateTransitionStatus::TS_INACTIVE:
			assert(false && "Transition status can't be inactive");
			break;

		case WorldStateTransitionStatus::TS_INITIATED:
			if (_sharedState->m_isUpdatingState || _sharedState->m_isUpdatingGraphics)
			{
				return;
			}
			_sharedState->m_worldStateTransitionState = WorldStateTransitionStatus::TS_SWITCHING_STATES;
			break;

		case WorldStateTransitionStatus::TS_SWITCHING_STATES:
			_graphicsManager->setWorldState(_worldState[_activeWorldState]);
			_gameStateManager->transitionGameState(_worldState[_activeWorldState],
				_worldState[_activeWorldState ^ 1]);
			_gameStateManager->setWorldState(_worldState[_activeWorldState ^ 1]);
			_activeWorldState ^= 1;
			_sharedState->m_worldStateTransitionState = WorldStateTransitionStatus::TS_INACTIVE;
			break;
		
		default:
			assert(false && "Unknown transition status");
			break;
		}
	}
}