#pragma once

#include <memory>

#include "World.h"
#include "SharedState.h"
#include "WorldManager.h"
#include "GraphicsManager.h"


namespace GameModule
{
	class GameModule
	{
	public:

		GameModule();
		virtual ~GameModule();

		virtual void run() final;

		virtual void initOnRun() = 0;
		virtual void update() = 0;

		virtual void runSubGame(std::shared_ptr<GameModule> subGame) final;


	protected:

		std::shared_ptr<World> _worlds[2];
		int32_t _worldIndex;

		std::shared_ptr<SharedState> _sharedState;

		std::shared_ptr<WorldManager> _worldManager;
		std::shared_ptr<GraphicsManager> _graphicsManager;


		void setWorld(int32_t index, std::shared_ptr<World> world);
		void setSharedState(std::shared_ptr<SharedState> sharedState);
		void setWorldManager(std::shared_ptr<WorldManager> worldManager);
		void setGraphicsManager(std::shared_ptr<GraphicsManager> graphicsManager);


	private:

		virtual void _initOnRun() final;
		virtual void _runLoop() final;

		void _swapWorlds(WorldSwapStatus swapStatus);

	};
}
