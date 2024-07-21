#include "WorldManager.h"
#include "../../Core/Window/WindowManager.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using BaseSharedState = GameModule::SharedState;
using BaseWorld = GameModule::World;


namespace GameModules
{
	namespace MainMenu
	{
		WorldManager::WorldManager(std::shared_ptr<SharedState> sharedState) :
			GameModule::WorldManager(std::dynamic_pointer_cast<BaseSharedState>(sharedState))
		{
			this->sharedState = sharedState;
		}
		
		WorldManager::~WorldManager() { }

		void WorldManager::setWorld(std::shared_ptr<BaseWorld> world)
		{
			this->world = std::dynamic_pointer_cast<World>(world);
		}
		
		void WorldManager::copyWorld(std::shared_ptr<BaseWorld> from, std::shared_ptr<BaseWorld> to)
		{
			World* fromWorld = dynamic_cast<World*>(from.get());
			World* toWorld = dynamic_cast<World*>(to.get());

			toWorld->pos = fromWorld->pos;
		}

		void WorldManager::init()
		{

		}

		void WorldManager::devicesUpate()
		{
			//sf::Event event;
			//sf::RenderWindow& window = Window::WindowManager::getInstance().getWindow();
			//
			//while (window.pollEvent(event))
			//{
			//	if (event.type == sf::Event::Closed)
			//	{
			//		sharedState->m_exitGame = true;
			//	}
			//
			//
			//}
		}
		
		void WorldManager::lightUpdate(double elapsedTime)
		{

		}
		
		void WorldManager::heavyUpdate(double elapsedTime)
		{
			double speed = 0.1;
			world->pos += speed * elapsedTime;
			if (world->pos > 500)
			{
				world->pos = 200;
			}
		}
	}
}