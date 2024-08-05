#include "GraphicsManager.h"
#include "Constants.h"
#include "../../Core/Window/WindowManager.h"

using BaseGraphicsManager = GameModule::GraphicsManager;
using BaseSharedState = GameModule::SharedState;


namespace GameModules
{
	namespace MainMenu
	{
		GraphicsManager::GraphicsManager(std::shared_ptr<SharedState> sharedState) :
			BaseGraphicsManager(std::dynamic_pointer_cast<BaseSharedState>(sharedState))
		{
			this->sharedState = sharedState;
		}

		GraphicsManager::~GraphicsManager() { }

		void GraphicsManager::setWorld(std::shared_ptr<GameModule::World> world)
		{
			this->world = std::dynamic_pointer_cast<World>(world);
		}

		void GraphicsManager::init()
		{
			
		}

		void GraphicsManager::render()
		{
			sf::RenderWindow& window = Window::WindowManager::getInstance().getWindow();

			window.clear(CLEAR_COLOR);

			world->interface->render(window);

			window.display();
		}
	}
}