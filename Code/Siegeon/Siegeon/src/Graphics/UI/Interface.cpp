#include "Interface.h"
#include "../../Core/GameSettings/GameSettings.h"
#include "../../Resources/FontManager/FontManager.h"
#include "WidgetGroup.h"
#include "Button.h"


namespace UI
{
	Interface::Interface()
	{
		_lastWindowX = -1;
		_lastWindowY = -1;
		_lastFontName = "";
	}

	Interface::Interface(const Interface& other)
	{
		copyState(other);
	}
	
	Interface::~Interface() { }

	void Interface::addWidget(std::shared_ptr<Widget> widget)
	{
		_widgets.push_back(widget);
	}

	void Interface::update(Core::Entities::WindowEventData& windowEvent)
	{
		GameSettings::GameSettings& gameSettings = GameSettings::GameSettings::getInstance();

		sf::Vector2i resolution = gameSettings.getResolutionInt();
		std::string newFontName = gameSettings.getFontName();

		if (resolution.x != _lastWindowX || resolution.y != _lastWindowY || newFontName != _lastFontName)
		{
			_lastWindowX = resolution.x;
			_lastWindowY = resolution.y;
			_lastFontName = newFontName;

			construct(resolution.x, resolution.y, newFontName);
		}

		for (auto& widget : _widgets)
		{
			widget->update(windowEvent);
		}
	}
	
	void Interface::render(sf::RenderWindow& window)
	{
		for (auto& widget : _widgets)
		{
			widget->render(window);
		}
	}

	void Interface::copyState(const Interface& other)
	{
		_lastWindowX = other._lastWindowX;
		_lastWindowY = other._lastWindowY;
		_lastFontName = other._lastFontName;
	}

	void Interface::construct(int32_t newWindowX, int32_t newWindowY, const std::string& newFontName)
	{
		sf::Font* font = FontManager::FontManager::getInstance().getFont(newFontName);

		for (auto& widget : _widgets)
		{
			widget->construct(newWindowX, newWindowY, font);
		}
	}
}