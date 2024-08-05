#include <cassert>

#include "TextureHolder.h"
#include "../../Core/GameSettings/GameSettings.h"
#include "../../Resources/FontManager/FontManager.h"


namespace UI
{
	using namespace TextureHolderHelpers;


	TextureHolder::TextureHolder()
	{
		type = WidgetType::TEXTUREHOLDER;

		_init(DEFAULT_TEXTUREHOLDER_CEXTER_X, DEFAULT_TEXTUREHOLDER_CEXTER_Y,
			DEFAULT_TEXTUREHOLDER_HALF_WIDTH, DEFAULT_TEXTUREHOLDER_HALF_HEIGHT);
	}

	TextureHolder::TextureHolder(double centerX, double centerY, double halfWidth, double halfHeight)
	{
		type = WidgetType::TEXTUREHOLDER;

		_init(centerX, centerY, halfWidth, halfHeight);
	}

	TextureHolder::TextureHolder(const TextureHolder& other)
	{
		type = WidgetType::TEXTUREHOLDER;

		copyState(other);
	}

	TextureHolder::~TextureHolder() { }

	void TextureHolder::update(Core::Entities::WindowEventData& windowEvent)
	{
		if (_hidden == true)
		{
			return;
		}

		assert(_isConstructed == true && "TextureHolder::update: TextureHolder is not constructed.");
	}

	void TextureHolder::render(sf::RenderWindow& window)
	{
		if (_hidden == true)
		{
			return;
		}

		assert(_isConstructed == true && "TextureHolder::render: TextureHolder is not constructed.");
		assert(_sprite.getTexture != nullptr && "TextureHolder::render: Texture is not set.");

		window.draw(_sprite);
	}

	void TextureHolder::construct(int32_t windowX, int32_t windowY, sf::Font* font)
	{
		double windowCenterX = windowX / 2.0;
		double windowCenterY = windowY / 2.0;
		double halfWindowWidth = windowX / 2.0;
		double halfWindowHeight = windowY / 2.0;

		double windowScaleX = double(GameSettings::DEFAULT_RESOLUTION_INT.x) / windowX;
		double windowScaleY = double(GameSettings::DEFAULT_RESOLUTION_INT.y) / windowY;
		double maxWindowScale = std::max(windowScaleX, windowScaleY);
		windowScaleX /= maxWindowScale;
		windowScaleY /= maxWindowScale;

		halfWindowWidth *= windowScaleX;
		halfWindowHeight *= windowScaleY;

		double rectCenterX = windowCenterX + _centerX * halfWindowWidth;
		double rectCenterY = windowCenterY + _centerY * halfWindowHeight;
		double rectHalfWidth, rectHalfHeight;

		sf::IntRect textureRect = _sprite.getTextureRect();

		if (_scalingMode == ScalingMode::PROPORTIONAL)
		{
			rectHalfWidth = _halfWidth * halfWindowWidth;
			rectHalfHeight = _halfHeight * halfWindowHeight;

			float scaleX = float(2.0 * rectHalfWidth / textureRect.width);
			float scaleY = float(2.0 * rectHalfHeight / textureRect.height);
			float scale = std::min(scaleX, scaleY);

			rectHalfWidth = textureRect.width * scale / 2.0;
			rectHalfHeight = textureRect.height * scale / 2.0;

			_sprite.setScale(scale, scale);
		}
		else
		{
			rectHalfWidth = _halfWidth * halfWindowWidth;
			rectHalfHeight = _halfHeight * halfWindowHeight;

			float scaleX = float(2.0 * rectHalfWidth / textureRect.width);
			float scaleY = float(2.0 * rectHalfHeight / textureRect.height);

			_sprite.setScale(scaleX, scaleY);
		}

		_sprite.setPosition(float(rectCenterX - rectHalfWidth), float(rectCenterY - rectHalfHeight));

		_isConstructed = true;
		_needReconstuction = false;
	}

	sf::FloatRect TextureHolder::boundingBox()
	{
		return _sprite.getGlobalBounds();
	}

	void TextureHolder::copyState(const TextureHolder& other)
	{
		_isConstructed = other._isConstructed;
		_hidden = other._hidden;

		_sprite = other._sprite;

		_needReconstuction = false;

		_scalingMode = other._scalingMode;

		_centerX = other._centerX;
		_centerY = other._centerY;
		_halfWidth = other._halfWidth;
		_halfHeight = other._halfHeight;

		if (other._needReconstuction)
		{
			reconstruct();
		}
	}

	void TextureHolder::reconstruct()
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

	void TextureHolder::setHidden(bool hidden)
	{
		_hidden = hidden;
	}

	bool TextureHolder::getHidden() const
	{
		return _hidden;
	}

	void TextureHolder::setTexture(const sf::Texture& texture)
	{
		_sprite.setTexture(texture);

		_needReconstuction = true;
	}

	const sf::Texture& TextureHolder::getTexture() const
	{
		return *_sprite.getTexture();
	}

	void TextureHolder::setTextureRect(const sf::IntRect& rect)
	{
		_sprite.setTextureRect(rect);

		_needReconstuction = true;
	}

	const sf::IntRect TextureHolder::getTextureRect() const
	{
		return _sprite.getTextureRect();
	}

	void TextureHolder::setScalingMode(TextureHolderHelpers::ScalingMode mode)
	{
		_scalingMode = mode;

		_needReconstuction = true;
	}

	TextureHolderHelpers::ScalingMode TextureHolder::getScalingMode() const
	{
		return _scalingMode;
	}

	void TextureHolder::setCenter(double centerX, double centerY)
	{
		_centerX = centerX;
		_centerY = centerY;

		_needReconstuction = true;
	}

	void TextureHolder::setSize(double halfWidth, double halfHeight)
	{
		_halfWidth = halfWidth;
		_halfHeight = halfHeight;

		_needReconstuction = true;
	}

	void TextureHolder::_init(double centerX, double centerY, double halfWidth, double halfHeight)
	{
		_centerX = centerX;
		_centerY = centerY;
		_halfWidth = halfWidth;
		_halfHeight = halfHeight;

		_isConstructed = false;
		_hidden = false;

		_needReconstuction = false;

		_scalingMode = DEFAULT_SCALING_MODE;
	}
}
