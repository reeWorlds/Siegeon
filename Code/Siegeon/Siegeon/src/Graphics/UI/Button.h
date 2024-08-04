#pragma once

#include "Widget.h"
#include "Constants.h"

#include <memory>


namespace UI
{
	class Button : public Widget
	{
	public:

		Button();
		Button(double centerX, double centerY, double halfWidth, double halfHeight);
		Button(const Button& other);
		~Button();

		void update(Core::Entities::WindowEventData& windowEvent) override;
		void render(sf::RenderWindow& window) override;
		void construct(int32_t windowX, int32_t windowY, sf::Font* font) override;
		sf::FloatRect boundingBox() override;

		void copyState(const Button& other);

		void reconstruct();

		bool getWasPressed() const;
		bool getWasPressedAndReset();

		void setHidden(bool hidden);
		bool getHidden() const;

		void setAvailable(bool available);
		bool getAvailable() const;

		void setOutlineColor(const sf::Color& color);
		sf::Color getOutlineColor() const;
		void setOutlineThickness(float thickness);
		float getOutlineThickness() const;

		void setTextColor(const sf::Color& color);
		sf::Color getTextColor() const;
		void setTextCharacterSize(uint32_t size);
		uint32_t getTextCharacterSize() const;
		void setTextOutlineColor(const sf::Color& color);
		sf::Color getTextOutlineColor() const;
		void setTextOutlineThickness(float thickness);
		float getTextOutlineThickness() const;
		void setTextString(const std::string& string);
		std::string getTextString() const;
		void setTextStyle(sf::Uint32 style);
		sf::Uint32 getTextStyle() const;

		void setColors(const sf::Color& idleColor, const sf::Color& hoverColor,
			const sf::Color& activeColor, const sf::Color& disabledColor);
		void setIdleColor(const sf::Color& color);
		sf::Color getIdleColor() const;
		void setHoverColor(const sf::Color& color);
		sf::Color getHoverColor() const;
		void setActiveColor(const sf::Color& color);
		sf::Color getActiveColor() const;
		void setDisabledColor(const sf::Color& color);
		sf::Color getDisabledColor() const;

		void setGeometry(double centerX, double centerY, double halfWidth, double halfHeight);

		void initWithDefaultStyle();
		

	private:

		bool _isConstructed;
		bool _hidden;
		bool _available;
		bool _wasPressed;

		bool _needReconstuction;
		
		std::pair<ButtonHelpers::ButtonState, ButtonHelpers::ButtonState> _states;

		std::shared_ptr<sf::RectangleShape> _rect;

		std::shared_ptr<sf::Text> _text;
		
		sf::Color _idleColor, _hoverColor, _activeColor, _unavailableColor;

		double _centerX, _centerY, _halfWidth, _halfHeight;


		void _init(double centerX, double centerY, double halfWidth, double halfHeight);
		void _setRectColor();

	};
}
