#include "WindowEventData.h"


namespace Core
{
	namespace Entities
	{
		WindowEventData::WindowEventData() : event(), mousePosition(), time()
		{

		}

		WindowEventData::WindowEventData(const sf::Event& event, const sf::Vector2i& mousePosition,
			const sf::Time& time) : event(event), mousePosition(mousePosition), time(time)
		{

		}

		WindowEventData::WindowEventData(const WindowEventData& other)
			: event(other.event), mousePosition(other.mousePosition), time(other.time)
		{

		}

		WindowEventData& WindowEventData::operator=(const WindowEventData& other)
		{
			if (this != &other)
			{
				event = other.event;
				mousePosition = other.mousePosition;
				time = other.time;
			}

			return *this;
		}

		WindowEventData::WindowEventData(WindowEventData&& other) noexcept :
			event(std::move(other.event)), mousePosition(std::move(other.mousePosition)),
			time(std::move(other.time))
		{

		}

		WindowEventData& WindowEventData::operator=(WindowEventData&& other) noexcept
		{
			if (this != &other)
			{
				event = std::move(other.event);
				mousePosition = std::move(other.mousePosition);
				time = std::move(other.time);
			}

			return *this;
		}

		WindowEventData::~WindowEventData() { }
	}
}