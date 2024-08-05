#include "Button.h"
#include "../../Core/GameSettings/Constants.h"
#include "../../Core/GameSettings/GameSettings.h"
#include "../../Resources/FontManager/FontManager.h"

#include <cassert>


namespace UI
{
	using namespace ButtonHelpers;


	Button::Button()
	{
		type = WidgetType::BUTTON;

		_init(DEFAULT_CEXTER_X, DEFAULT_CEXTER_Y, DEFAULT_HALF_WIDTH, DEFAULT_HALF_HEIGHT);
	}

	Button::Button(double centerX, double centerY, double halfWidth, double halfHeight)
	{
		type = WidgetType::BUTTON;

		_init(centerX, centerY, halfWidth, halfHeight);
	}

	Button::Button(const Button& other)
	{
		type = WidgetType::BUTTON;

		_rect = other._rect;
		_text = other._text;

		copyState(other);
	}

	Button::~Button() { }

	void Button::update(Core::Entities::WindowEventData& windowEvent)
	{
		if (_hidden == true)
		{
			return;
		}

		assert(_isConstructed == true && "Button::update: Button is not constructed.");

		_states.second = _states.first;
		_states.first = ButtonState::IDLE;

		if (_available == false)
		{
			return;
		}

		sf::Event event = windowEvent.event;
		sf::Vector2i mousePos = windowEvent.mousePosition;

		bool currentlyHovered = _rect->getGlobalBounds().contains(float(mousePos.x), float(mousePos.y));
		bool currentlyActioned = event.mouseButton.button == sf::Mouse::Left;

		if (_states.second == ButtonState::ACTIVE)
		{
			if (currentlyHovered)
			{
				_states.first = ButtonState::ACTIVE;

				if (currentlyActioned && event.type == sf::Event::MouseButtonReleased)
				{
					_states.first = ButtonState::IDLE;

					_wasPressed = true;
				}
			}
			else
			{
				_states.first = ButtonState::IDLE;
			}
		}
		else
		{
			if (currentlyHovered)
			{
				_states.first = ButtonState::HOVER;

				if (currentlyActioned && event.type == sf::Event::MouseButtonPressed)
				{
					_states.first = ButtonState::ACTIVE;
				}
			}
		}
	}

	void Button::render(sf::RenderWindow& window)
	{
		if (_hidden == true)
		{
			return;
		}

		assert(_isConstructed == true && "Button::render: Button is not constructed.");

		_setRectColor();
		window.draw(*_rect);
		window.draw(*_text);
	}

	void Button::construct(int32_t windowX, int32_t windowY, sf::Font* font)
	{
		double windowCenterX = windowX / 2.0;
		double windowCenterY = windowY / 2.0;
		double halfWindowWidth = windowX / 2.0;
		double halfWindowHeight = windowY / 2.0;

		double scaleX = double(GameSettings::DEFAULT_RESOLUTION_INT.x) / windowX;
		double scaleY = double(GameSettings::DEFAULT_RESOLUTION_INT.y) / windowY;
		double maxScale = std::max(scaleX, scaleY);
		scaleX /= maxScale;
		scaleY /= maxScale;
		
		halfWindowWidth *= scaleX;
		halfWindowHeight *= scaleY;

		double rectCenterX = windowCenterX + _centerX * halfWindowWidth;
		double rectCenterY = windowCenterY + _centerY * halfWindowHeight;
		double rectHalfWidth = _halfWidth * halfWindowWidth;
		double rectHalfHeight = _halfHeight * halfWindowHeight;

		_rect->setSize(sf::Vector2f(float(rectHalfWidth * 2.0), float(rectHalfHeight * 2.0)));
		_rect->setPosition(float(rectCenterX - rectHalfWidth), float(rectCenterY - rectHalfHeight));

		_text->setFont(*font);
		sf::FloatRect textRect = _text->getLocalBounds();
		_text->setPosition(float(rectCenterX - textRect.width / 2.0f - textRect.left),
			float(rectCenterY - textRect.height / 2.0f - textRect.top));

		_isConstructed = true;
		_needReconstuction = false;
	}

	sf::FloatRect Button::boundingBox()
	{
		return _rect->getGlobalBounds();
	}

	void Button::copyState(const Button& other)
	{
		_isConstructed = other._isConstructed;
		_hidden = other._hidden;
		_available = other._available;
		_wasPressed = other._wasPressed;

		_needReconstuction = false;

		_states = other._states;

		_idleColor = other._idleColor;
		_hoverColor = other._hoverColor;
		_activeColor = other._activeColor;
		_unavailableColor = other._unavailableColor;

		_centerX = other._centerX;
		_centerY = other._centerY;
		_halfWidth = other._halfWidth;
		_halfHeight = other._halfHeight;

		if (other._needReconstuction)
		{
			reconstruct();
		}
	}

	void Button::reconstruct()
	{
		if (_isConstructed == false)
		{
			return;
		}

		sf::Vector2i resolution = GameSettings::GameSettings::getInstance().getResolutionInt();
		std::string fontName = GameSettings::GameSettings::getInstance().getFontName();
		sf::Font* font = FontManager::FontManager::getInstance().getFont(fontName);

		construct(resolution.x, resolution.y, font);
	}

	bool Button::getWasPressed() const
	{
		return _wasPressed;
	}

	bool Button::getWasPressedAndReset()
	{
		bool wasPressed = _wasPressed;
		_wasPressed = false;

		return wasPressed;
	}

	void Button::setHidden(bool hidden)
	{
		_hidden = hidden;
	}

	bool Button::getHidden() const
	{
		return _hidden;
	}

	void Button::setAvailable(bool available)
	{
		_available = available;
	}

	bool Button::getAvailable() const
	{
		return _available;
	}

	void Button::setOutlineColor(const sf::Color& color)
	{
		_rect->setOutlineColor(color);
	}

	sf::Color Button::getOutlineColor() const
	{
		return _rect->getOutlineColor();
	}

	void Button::setOutlineThickness(float thickness)
	{
		_rect->setOutlineThickness(thickness);
	}

	float Button::getOutlineThickness() const
	{
		return _rect->getOutlineThickness();
	}

	void Button::setTextColor(const sf::Color& color)
	{
		_text->setFillColor(color);
	}

	sf::Color Button::getTextColor() const
	{
		return _text->getFillColor();
	}

	void Button::setTextCharacterSize(uint32_t size)
	{
		_text->setCharacterSize(size);

		_needReconstuction = true;
	}

	uint32_t Button::getTextCharacterSize() const
	{
		return _text->getCharacterSize();
	}

	void Button::setTextOutlineColor(const sf::Color& color)
	{
		_text->setOutlineColor(color);
	}

	sf::Color Button::getTextOutlineColor() const
	{
		return _text->getOutlineColor();
	}

	void Button::setTextOutlineThickness(float thickness)
	{
		_text->setOutlineThickness(thickness);
	}

	float Button::getTextOutlineThickness() const
	{
		return _text->getOutlineThickness();
	}

	void Button::setTextString(const std::string& string)
	{
		_text->setString(string);

		_needReconstuction = true;
	}

	std::string Button::getTextString() const
	{
		return _text->getString().toAnsiString();
	}

	void Button::setTextStyle(sf::Uint32 style)
	{
		_text->setStyle(style);

		_needReconstuction = true;
	}

	sf::Uint32 Button::getTextStyle() const
	{
		return _text->getStyle();
	}

	void Button::setColors(const sf::Color& idleColor, const sf::Color& hoverColor,
		const sf::Color& activeColor, const sf::Color& disabledColor)
	{
		_idleColor = idleColor;
		_hoverColor = hoverColor;
		_activeColor = activeColor;
		_unavailableColor = disabledColor;
	}

	void Button::setIdleColor(const sf::Color& color)
	{
		_idleColor = color;
	}

	sf::Color Button::getIdleColor() const
	{
		return _idleColor;
	}

	void Button::setHoverColor(const sf::Color& color)
	{
		_hoverColor = color;
	}

	sf::Color Button::getHoverColor() const
	{
		return _hoverColor;
	}

	void Button::setActiveColor(const sf::Color& color)
	{
		_activeColor = color;
	}

	sf::Color Button::getActiveColor() const
	{
		return _activeColor;
	}

	void Button::setDisabledColor(const sf::Color& color)
	{
		_unavailableColor = color;
	}

	sf::Color Button::getDisabledColor() const
	{
		return _unavailableColor;
	}

	void Button::setGeometry(double centerX, double centerY, double halfWidth, double halfHeight)
	{
		_centerX = centerX;
		_centerY = centerY;
		_halfWidth = halfWidth;
		_halfHeight = halfHeight;
	}

	void Button::initWithDefaultStyle()
	{
		_idleColor = DEFAULT_IDLE_COLOR;
		_hoverColor = DEFAULT_HOVER_COLOR;
		_activeColor = DEFAULT_ACTIVE_COLOR;
		_unavailableColor = DEFAULT_UNAVAILABLE_COLOR;

		_rect->setOutlineColor(DEFAULT_RECT_OUTLINE_COLOR);
		_rect->setOutlineThickness(DEFAULT_RECT_OUTLINE_THICKNESS);

		_text->setFillColor(DEFAULT_TEXT_COLOR);
		_text->setCharacterSize(DEFAULT_TEXT_SIZE);
		_text->setOutlineColor(DEFAULT_TEXT_OUTLINE_COLOR);
		_text->setOutlineThickness(DEFAULT_TEXT_OUTLINE_THICKNESS);
		_text->setString(DEFAULT_TEXT_STRING);
		_text->setStyle(DEFAULT_TEXT_STYLE);
	}

	void Button::_init(double centerX, double centerY, double halfWidth, double halfHeight)
	{
		_centerX = centerX;
		_centerY = centerY;
		_halfWidth = halfWidth;
		_halfHeight = halfHeight;

		_isConstructed = false;
		_hidden = false;
		_available = true;
		_wasPressed = false;

		_needReconstuction = false;

		_states = std::make_pair(ButtonState::IDLE, ButtonState::IDLE);

		_rect = std::make_shared<sf::RectangleShape>();

		_text = std::make_shared<sf::Text>();

		initWithDefaultStyle();
	}

	void Button::_setRectColor()
	{
		if (_available == false)
		{
			_rect->setFillColor(_unavailableColor);
			return;
		}

		switch (_states.first)
		{
		case ButtonState::IDLE:
			_rect->setFillColor(_idleColor);
			break;
		case ButtonState::HOVER:
			_rect->setFillColor(_hoverColor);
			break;
		case ButtonState::ACTIVE:
			_rect->setFillColor(_activeColor);
			break;
		default:
			assert(false && "Button::_setRectColor: Invalid ButtonState.");
		}
	}
}
