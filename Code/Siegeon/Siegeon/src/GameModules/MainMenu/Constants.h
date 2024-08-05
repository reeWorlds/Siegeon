#pragma once

#include "../../Graphics/UI/Constants.h"

#include <SFML/Graphics.hpp>


namespace GameModules
{
	namespace MainMenu
	{
		inline const sf::Color CLEAR_COLOR = sf::Color::White;

		inline constexpr int32_t MAX_EVENTS_PER_LOOP = 32;

		inline constexpr double MENU_BUTTON_CEXTER_X = -0.65;
		inline constexpr double MENU_BUTTON_NEW_GAME_CEXTER_Y = -0.65;
		inline constexpr double MENU_BUTTON_CONTINUE_CEXTER_Y = -0.30;
		inline constexpr double MENU_BUTTON_SETTINGS_CEXTER_Y = 0.05;
		inline constexpr double MENU_BUTTON_EXIT_CEXTER_Y = 0.40;
		inline constexpr double MENU_BUTTON_HALF_WIDTH = 0.25;
		inline constexpr double MENU_BUTTON_HALF_HEIGHT = 0.1;

		inline const sf::Color MENU_BUTTON_IDLE_COLOR = sf::Color(173, 216, 230);
		inline const sf::Color MENU_BUTTON_HOVER_COLOR = sf::Color(144, 238, 144);
		inline const sf::Color MENU_BUTTON_ACTIVE_COLOR = sf::Color(60, 179, 113);
		inline const sf::Color MENU_BUTTON_UNAVAILABLE_COLOR = sf::Color(169, 169, 169);

		inline constexpr int32_t MENU_BUTTON_TEXT_SIZE = 45;
		inline const char* MENU_BUTTON_NEW_GAME_TEXT_STRING = "NEW GAME";
		inline const char* MENU_BUTTON_CONTINUE_TEXT_STRING = "CONTINUE";
		inline const char* MENU_BUTTON_SETTINGS_TEXT_STRING = "SETTINGS";
		inline const char* MENU_BUTTON_EXIT_TEXT_STRING = "EXIT";

		inline constexpr sf::Uint32 MENU_BUTTON_TEXT_STYLE = sf::Text::Bold;

		inline constexpr double LOGO_X_SPEED = 0.00127;
		inline constexpr double LOGO_Y_SPEED = 0.00149;
		inline constexpr double LOGO_SHIFT_AMPLITUDE = 0.03;
		inline constexpr double LOGO_CEXTER_X = 0.3;
		inline constexpr double LOGO_CEXTER_Y = 0.2;
		inline constexpr double LOGO_HALF_WIDTH = 0.65;
		inline constexpr double LOGO_HALF_HEIGHT = 0.75;
		inline constexpr UI::TextureHolderHelpers::ScalingMode LOGO_SCALING_MODE =
			UI::TextureHolderHelpers::ScalingMode::STRETCH;
	}
}
