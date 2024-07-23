#pragma once

#include "../GameSettings/GameSettings.h"
#include "../Containers/ThreadDeque.hpp"
#include "../Entities/WindowEventData.h"

#include <SFML/Graphics.hpp>


namespace Window
{
	class WindowManager
	{
	public:

		Core::Containers::ThreadDeque<Core::Entities::WindowEventData> eventDeque;


		static WindowManager& getInstance();

		sf::RenderWindow& getWindow();

		void createWindow();

		void setWindowActive();
		void setWindowInactive();

		sf::Time getElapsedTime();


	private:

		sf::RenderWindow _window;
		sf::Clock _clock;


		WindowManager();
		~WindowManager();

		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;
		WindowManager(WindowManager&&) = delete;
		WindowManager& operator=(WindowManager&&) = delete;

		sf::VideoMode _getVideoMode(sf::Vector2i resolution);
		int32_t _getWindowStyle(GameSettings::VideoMode mode);
		sf::ContextSettings _getContextSettings();
	};
}
