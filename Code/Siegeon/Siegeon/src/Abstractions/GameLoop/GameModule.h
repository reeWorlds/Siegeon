#pragma once

#include <memory>

#include "WorldState.h"
#include "SharedState.h"
#include "GameStateManager.h"
#include "GraphicsManager.h"


namespace GameLoop
{
	class GameModule
	{
	public:

		GameModule();
		virtual ~GameModule();

		virtual void run() final;

		virtual void initOnRun() = 0;
		virtual void update() = 0;

		virtual void runSubGameLoop(std::shared_ptr<GameModule> subGame) final;


	protected:

		std::shared_ptr<WorldState> _worldState[2];
		int32_t _activeWorldState;

		std::shared_ptr<SharedState> _sharedState;

		std::shared_ptr<GameStateManager> _gameStateManager;
		std::shared_ptr<GraphicsManager> _graphicsManager;


		void setWorldState(int32_t index, std::shared_ptr<WorldState> state);
		void setSharedState(std::shared_ptr<SharedState> state);
		void setGameStateManager(std::shared_ptr<GameStateManager> state);
		void setGraphicsManager(std::shared_ptr<GraphicsManager> state);


	private:

		virtual void _initOnRun() final;
		virtual void _runLoop() final;

		void _switchWorldState(WorldStateTransitionStatus transitionStatus);

	};
}
