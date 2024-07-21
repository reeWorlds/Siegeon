#pragma once

#include "../GameModule/GraphicsManager.h"
#include "SharedState.h"
#include "World.h"


namespace GameModules
{
	namespace MainMenu
	{
		class GraphicsManager : public GameModule::GraphicsManager
		{
		public:

			std::shared_ptr<SharedState> sharedState;
			std::shared_ptr<World> world;


			GraphicsManager(std::shared_ptr<SharedState> sharedState);
			~GraphicsManager();

			void setWorld(std::shared_ptr<GameModule::World> world) override;

			void init() override;

			void render() override;
		};
	}
}