#pragma once

#include "Widget.h"
#include "../../Core/Entities/WindowEventData.h"

#include <memory>
#include <SFML/Graphics.hpp>


namespace UI
{
	class Interface
	{
	public:

		Interface();
		Interface(const Interface& other);
		~Interface();

		void addWidget(std::shared_ptr<Widget> widget);

		void update(Core::Entities::WindowEventData& windowEvent);
		void render(sf::RenderWindow& window);

		void copyState(const Interface& other);

		void construct(int32_t newWindowX, int32_t newWindowY, const std::string& newFontName);


	private:

		std::vector<std::shared_ptr<Widget>> _widgets;

		int32_t _lastWindowX, _lastWindowY;
		std::string _lastFontName;

	};
}
