#include "WorldManager.h"
#include "Constants.h"
#include "../../Core/Window/WindowManager.h"
#include "../../Core/Entities/WindowEventData.h"
#include "../../Core/Containers/ThreadDeque.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using BaseSharedState = GameModule::SharedState;
using BaseWorld = GameModule::World;
using WindowEventData = Core::Entities::WindowEventData;
using ThreadDeque = Core::Containers::ThreadDeque<WindowEventData>;


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

		void WorldManager::devicesUpdate()
		{
			int32_t eventsCount = 0;
			
			ThreadDeque& eventDeque = Window::WindowManager::getInstance().eventDeque;
			
			while (!eventDeque.empty())
			{
				std::optional<WindowEventData> eventData = eventDeque.front_and_pop();

				if (eventData.has_value())
				{
					sf::Event event = eventData.value().event;

					// if '+' was pressed
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
					{
						world->pos += 10;
					}
					// if '-' was pressed
					else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract)
					{
						world->pos -= 10;
					}
				}
				else
				{
					break;
				}
			
				eventsCount++;
				if (eventsCount >= MAX_EVENTS_PER_LOOP) { break; }
			}
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