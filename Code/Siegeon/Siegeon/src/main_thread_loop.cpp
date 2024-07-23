#include "main_thread_loop.h"

#include "Resources/FontManager/FontManager.h"
#include "Core/GameSettings/GameSettings.h"
#include "Core/Window/WindowManager.h"
#include "GameModules/MainMenu/MainMenu.h"
#include "GameModules/GameModule/Constants.h"


void start()
{
	_init_singletons();

	_main_thread_loop();
}

void _init_singletons()
{
	FontManager::FontManager::getInstance();
	GameSettings::GameSettings::getInstance();
	Window::WindowManager::getInstance();
}

void _main_thread_loop()
{
	constexpr const int32_t MAX_EVENTS_PER_LOOP = 32;

	using namespace GameModules::MainMenu;
	using WindowEventData = Core::Entities::WindowEventData;
	using ThreadDeque = Core::Containers::ThreadDeque<WindowEventData>;

	std::unique_ptr<MainMenu> menu;

	while (true)
	{
		sf::Event event;
		sf::RenderWindow& window = Window::WindowManager::getInstance().getWindow();
		ThreadDeque& eventDeque = Window::WindowManager::getInstance().eventDeque;

		int32_t eventsCount = 0;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				
				exit(0);
			}

			WindowEventData eventData;
			eventData.event = event;
			eventData.mousePosition = sf::Mouse::getPosition(window);
			eventData.time = Window::WindowManager::getInstance().getElapsedTime();

			eventDeque.push_back(eventData);

			eventsCount++;
			if (eventsCount >= MAX_EVENTS_PER_LOOP) { break; }
		}

		if (menu == nullptr)
		{
			menu = std::make_unique<MainMenu>();
			std::thread menuThread(&MainMenu::run, menu.get());
			menuThread.detach();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(GameModule::SLEEP_TIME_US));
	}
}
