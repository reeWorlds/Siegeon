#pragma once

#include "../GameModule/GameModule.h"
#include "SharedState.h"
#include "World.h"
#include "WorldManager.h"
#include "GraphicsManager.h"

#include <memory>


namespace GameModules
{
	namespace MainMenu
	{
		class MainMenu : public GameModule::GameModule
		{
		public:

			std::shared_ptr<World> worlds[2];

			std::shared_ptr<SharedState> sharedState;

			std::shared_ptr<WorldManager> worldManager;
			std::shared_ptr<GraphicsManager> graphicsManager;


			MainMenu();
			~MainMenu();

			void initOnRun() override;
			void update() override;

		};
	}
}