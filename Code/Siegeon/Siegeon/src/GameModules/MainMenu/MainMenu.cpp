#include "MainMenu.h"
#include "../GameModule/Constants.h"

#include <thread>
#include <chrono>

using namespace std::chrono;


namespace GameModules
{
	namespace MainMenu
	{
		MainMenu::MainMenu() { }

		MainMenu::~MainMenu() { }

		void MainMenu::initOnRun()
		{
			worlds[0] = std::shared_ptr<World>(new World());
			worlds[1] = std::shared_ptr<World>(new World());
			sharedState = std::shared_ptr<SharedState>(new SharedState());
			worldManager = std::shared_ptr<WorldManager>(new WorldManager(sharedState));
			graphicsManager = std::shared_ptr<GraphicsManager>(new GraphicsManager(sharedState));

			_setWorld(0, worlds[0]);
			_setWorld(1, worlds[1]);
			_setSharedState(sharedState);
			_setWorldManager(worldManager);
			_setGraphicsManager(graphicsManager);
		}

		void MainMenu::update()
		{
			std::this_thread::sleep_for(microseconds(::GameModule::SLEEP_TIME_US));
		}
	}
}