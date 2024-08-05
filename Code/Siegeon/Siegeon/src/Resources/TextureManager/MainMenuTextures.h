#pragma once

#include <memory>
#include <SFML/Graphics.hpp>


namespace TextureManager
{
	class MainMenuTextures
	{
	public:

		void loadTextures();
		void unloadTextures();

		std::shared_ptr<sf::Texture> getLogoTexture();


	private:

		bool isLoaded;

		std::shared_ptr<sf::Texture> _logoTexture;


		MainMenuTextures();
		~MainMenuTextures();


		friend class TextureManager;

	};
}
