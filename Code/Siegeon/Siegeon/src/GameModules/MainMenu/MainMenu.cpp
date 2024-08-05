#include "MainMenu.h"
#include "../GameModule/Constants.h"
#include "../../Resources/TextureManager/TextureManager.h"

#include <thread>
#include <chrono>

using namespace std::chrono;


namespace GameModules
{
	namespace MainMenu
	{
		MainMenu::MainMenu()
		{
			TextureManager::TextureManager::getMainMenuTexturesInstance().loadTextures();
		}

		MainMenu::~MainMenu()
		{
			TextureManager::TextureManager::getMainMenuTexturesInstance().unloadTextures();
		}

		void MainMenu::initOnRun()
		{
			worlds[0] = std::make_shared<World>();
			worlds[1] = std::make_shared<World>(*worlds[0]);
			sharedState = std::make_shared<SharedState>();
			worldManager = std::make_shared<WorldManager>(sharedState);
			graphicsManager = std::make_shared<GraphicsManager>(sharedState);

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