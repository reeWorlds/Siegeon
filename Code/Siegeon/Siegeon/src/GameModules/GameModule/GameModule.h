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

		virtual void _setWorld(int32_t index, std::shared_ptr<World> world) final;
		virtual void _setSharedState(std::shared_ptr<SharedState> sharedState) final;
		virtual void _setWorldManager(std::shared_ptr<WorldManager> worldManager) final;
		virtual void _setGraphicsManager(std::shared_ptr<GraphicsManager> graphicsManager) final;

		virtual int32_t _getWorldIndex() final;

	private:

		std::shared_ptr<World> _worlds[2];
		int32_t _worldIndex;

		std::shared_ptr<SharedState> _sharedState;

		std::shared_ptr<WorldManager> _worldManager;
		std::shared_ptr<GraphicsManager> _graphicsManager;


		virtual void _initOnRun() final;
		virtual void _runLoop() final;

		virtual void _swapWorlds(WorldSwapStatus swapStatus) final;

	};
}
