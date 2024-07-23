#include "WindowManager.h"
#include "Constants.h"


namespace Window
{
	WindowManager& WindowManager::getInstance()
	{
		static WindowManager instance;

		return instance;
	}

	sf::RenderWindow& WindowManager::getWindow()
	{
		return _window;
	}

	void WindowManager::createWindow()
	{
		GameSettings::GameSettings& gameSettings = GameSettings::GameSettings::getInstance();
		sf::VideoMode videoMode = _getVideoMode(gameSettings.getResolutionInt());

		int32_t style = _getWindowStyle(gameSettings.getVideoMode());

		sf::ContextSettings contextSettings = _getContextSettings();

		if (_window.isOpen())
		{
			_window.close();
		}

		_window.create(videoMode, WINDOW_TITLE, style, contextSettings);

		_window.setKeyRepeatEnabled(false);

		_window.setActive(false);
	}

	void WindowManager::setWindowActive()
	{
		_window.setActive(true);
	}

	void WindowManager::setWindowInactive()
	{
		_window.setActive(false);
	}

	sf::Time WindowManager::getElapsedTime()
	{
		return _clock.getElapsedTime();
	}

	WindowManager::WindowManager()
	{
		createWindow();

		_clock.restart();
	}

	WindowManager::~WindowManager()
	{
		if (_window.isOpen())
		{
			_window.close();
		}
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
