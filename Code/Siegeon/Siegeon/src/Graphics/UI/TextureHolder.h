#pragma once

#include "Widget.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>


namespace UI
{
	class TextureHolder : public Widget
	{
	public:

		TextureHolder();
		TextureHolder(double centerX, double centerY, double halfWidth, double halfHeight);
		TextureHolder(const TextureHolder& other);
		~TextureHolder();

		void update(Core::Entities::WindowEventData& windowEvent) override;
		void render(sf::RenderWindow& window) override;
		void construct(int32_t windowX, int32_t windowY, sf::Font* font) override;
		sf::FloatRect boundingBox() override;

		void copyState(const TextureHolder& other);

		void reconstruct();

		void setHidden(bool hidden);
		bool getHidden() const;

		void setTexture(const sf::Texture& texture);
		const sf::Texture& getTexture() const;
		void setTextureRect(const sf::IntRect& rect);
		const sf::IntRect getTextureRect() const;

		void setScalingMode(TextureHolderHelpers::ScalingMode mode);
		TextureHolderHelpers::ScalingMode getScalingMode() const;

		void setCenter(double centerX, double centerY);
		void setSize(double halfWidth, double halfHeight);


	private:

		bool _isConstructed;
		bool _hidden;

		sf::Sprite _sprite;

		bool _needReconstuction;

		TextureHolderHelpers::ScalingMode _scalingMode;

		double _centerX, _centerY, _halfWidth, _halfHeight;


		void _init(double centerX, double centerY, double halfWidth, double halfHeight);

	};
}
