#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>


namespace UI
{
	enum class WidgetType : int32_t
	{
		NONE,
		WIDGETGROUP,
		BUTTON,
	};

	namespace ButtonHelpers
	{
		enum class ButtonState : int32_t
		{
			IDLE,
			HOVER,
			ACTIVE,
		};

		inline constexpr double DEFAULT_CEXTER_X = -0.85;
		inline constexpr double DEFAULT_CEXTER_Y = -0.9;
		inline constexpr double DEFAULT_HALF_WIDTH = 0.1;
		inline constexpr double DEFAULT_HALF_HEIGHT = 0.05;

		inline const sf::Color DEFAULT_IDLE_COLOR = sf::Color(220, 220, 220);
		inline const sf::Color DEFAULT_HOVER_COLOR = sf::Color(192, 192, 192);
		inline const sf::Color DEFAULT_ACTIVE_COLOR = sf::Color(128, 128, 128);
		inline const sf::Color DEFAULT_UNAVAILABLE_COLOR = sf::Color(169, 169, 169);

		inline const sf::Color DEFAULT_RECT_OUTLINE_COLOR = sf::Color::Black;
		inline constexpr float DEFAULT_RECT_OUTLINE_THICKNESS = 2.0;

		inline const sf::Color DEFAULT_TEXT_COLOR = sf::Color::Black;
		inline constexpr int32_t DEFAULT_TEXT_SIZE = 20;
		inline const sf::Color DEFAULT_TEXT_OUTLINE_COLOR = sf::Color::Black;
		inline constexpr float DEFAULT_TEXT_OUTLINE_THICKNESS = 1.0;
		inline constexpr const char* DEFAULT_TEST_STRING = "Button";
		inline constexpr sf::Uint32 DEFAULT_TEXT_STYLE = sf::Text::Regular;
	}
}