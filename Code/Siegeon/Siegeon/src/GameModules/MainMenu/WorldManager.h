#pragma once

#include "../GameModule/WorldManager.h"
#include "SharedState.h"
#include "World.h"

#include <memory>


namespace GameModules
{
	namespace MainMenu
	{
		class WorldManager : public GameModule::WorldManager
		{
		public:

			std::shared_ptr<SharedState> sharedState;
			std::shared_ptr<World> world;


			WorldManager(std::shared_ptr<SharedState> sharedState);
			~WorldManager();

			void setWorld(std::shared_ptr<GameModule::World> world) override;
			void copyWorld(std::shared_ptr<GameModule::World> from,
				std::shared_ptr<GameModule::World> to) override;

			void init() override;

			void devicesUpdate() override;
			void lightUpdate(double elapsedTime) override;
			void heavyUpdate(double elapsedTime) override;

		};
	}
}