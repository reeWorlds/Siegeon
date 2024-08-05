#include "Constants.h"
#include "MainMenuTextures.h"


namespace TextureManager
{
	void MainMenuTextures::loadTextures()
	{
		if (isLoaded == true)
		{
			return;
		}

		_logoTexture = std::make_shared<sf::Texture>();
		_logoTexture->loadFromFile(MainMenuHelpers::LOGO_PATH);
		_logoTexture->setSmooth(true);

		isLoaded = true;
	}

	void MainMenuTextures::unloadTextures()
	{
		if (isLoaded == false)
		{
			return;
		}

		isLoaded = false;

		_logoTexture.reset();
	}

	std::shared_ptr<sf::Texture> MainMenuTextures::getLogoTexture()
	{
		return _logoTexture;
	}

	MainMenuTextures::MainMenuTextures()
	{
		isLoaded = false;
	}

	MainMenuTextures::~MainMenuTextures()
	{
		if (isLoaded)
		{
			unloadTextures();
		}
	}
}
