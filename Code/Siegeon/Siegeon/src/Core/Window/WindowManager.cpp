#include "WindowManager.h"
#include "Constants.h"


namespace Window
{
	WindowManager& WindowManager::getInstance()
	{
		static WindowManager instance;

		return instance;
	}

	void WindowManager::createWindow()
	{
		GameSettings::GameSettings& gameSettings = GameSettings::GameSettings::getInstance();
		sf::VideoMode videoMode = _getVideoMode(gameSettings.getResolutionInt());

		int32_t style = _getWindowStyle(gameSettings.getVideoMode());

		sf::ContextSettings contextSettings = _getContextSettings();
		contextSettings.antialiasingLevel = 4;

		_window.create(videoMode, WINDOW_TITLE, style, contextSettings);
	}

	WindowManager::WindowManager()
	{
		createWindow();
	}

	WindowManager::~WindowManager()
	{

	}

	sf::VideoMode WindowManager::_getVideoMode(sf::Vector2i resolution)
	{
		return sf::VideoMode(resolution.x, resolution.y, WINDOW_DEPTH_BITS);
	}

	int32_t WindowManager::_getWindowStyle(GameSettings::VideoMode mode)
	{
		if (mode == GameSettings::VideoMode::WINDOWED)
		{
			return sf::Style::Titlebar | sf::Style::Close;
		}
		else
		{
			return sf::Style::Fullscreen;
		}
	}

	sf::ContextSettings WindowManager::_getContextSettings()
	{
		sf::ContextSettings contextSettings = sf::ContextSettings();
		contextSettings.antialiasingLevel = 4;

		return contextSettings;
	}
}
