#include "TextureManager.h"


namespace TextureManager
{
	MainMenuTextures& TextureManager::getMainMenuTexturesInstance()
	{
		static MainMenuTextures instance;
		
		return instance;
	}
}
