#pragma once

#include <SFML/Window.hpp>


namespace Core
{
	namespace Entities
	{
		class WindowEventData
		{
		public:

			sf::Event event;
			sf::Vector2i mousePosition;
			sf::Time time;


			WindowEventData();
			WindowEventData(const sf::Event& event, const sf::Vector2i& mousePosition,
				const sf::Time& time);

			WindowEventData(const WindowEventData& other);
			WindowEventData& operator=(const WindowEventData& other);

			WindowEventData(WindowEventData&& other) noexcept;
			WindowEventData& operator=(WindowEventData&& other) noexcept;
			
			~WindowEventData();

		};
	}
}