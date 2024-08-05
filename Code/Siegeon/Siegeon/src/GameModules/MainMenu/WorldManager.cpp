#define _USE_MATH_DEFINES

#include "WorldManager.h"
#include "Constants.h"
#include "../../Core/Window/WindowManager.h"
#include "../../Core/Entities/WindowEventData.h"
#include "../../Core/Containers/ThreadDeque.hpp"
#include <cmath>

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

			toWorld->interface->copyState(*fromWorld->interface);

			toWorld->menuGroup->copyState(*fromWorld->menuGroup);

			toWorld->newGameButton->copyState(*fromWorld->newGameButton);
			toWorld->continueGameButton->copyState(*fromWorld->continueGameButton);
			toWorld->settingsButton->copyState(*fromWorld->settingsButton);
			toWorld->exitButton->copyState(*fromWorld->exitButton);

			toWorld->logoTimeX = fromWorld->logoTimeX;
			toWorld->logoTimeY = fromWorld->logoTimeY;
			toWorld->logo->copyState(*fromWorld->logo);
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
					world->interface->update(eventData.value());
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
			if (world->exitButton->getWasPressedAndReset())
			{
				Window::WindowManager::getInstance().getWindow().close();

				exit(0);
			}

			world->logoTimeX += elapsedTime * LOGO_X_SPEED;
			if (world->logoTimeX > 2 * M_PI)
			{
				world->logoTimeX -= 2 * M_PI;
			}
			world->logoTimeY += elapsedTime * LOGO_Y_SPEED;
			if (world->logoTimeY > 2 * M_PI)
			{
				world->logoTimeY -= 2 * M_PI;
			}

			world->logo->setCenter(LOGO_CEXTER_X + LOGO_SHIFT_AMPLITUDE * std::sin(world->logoTimeX),
				LOGO_CEXTER_Y + LOGO_SHIFT_AMPLITUDE * std::sin(world->logoTimeY));
		}
	}
}