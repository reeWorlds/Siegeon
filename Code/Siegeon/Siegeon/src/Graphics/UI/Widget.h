#pragma once

#include "../../Core/Entities/WindowEventData.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>


namespace UI
{
	class Widget
	{
	public:

		WidgetType type;


		Widget();
		virtual ~Widget();

		virtual void update(Core::Entities::WindowEventData& windowEvent) = 0;

		virtual void render(sf::RenderWindow& window) = 0;

		virtual void construct(int32_t windowX, int32_t windowY, sf::Font* font) = 0;

		virtual sf::FloatRect boundingBox() = 0;

	};
}
