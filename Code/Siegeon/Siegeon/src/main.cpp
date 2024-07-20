#include "Resources/FontManager/FontManager.h"
#include "Core/GameSettings/GameSettings.h"
#include "Core/RenderWindow/RenderWindowManager.h"


void initSingletons()
{
	FontManager::FontManager::getInstance();
	GameSettings::GameSettings::getInstance();
	//RenderWindowManager::getInstance();
}



int main()
{
	initSingletons();



	return 0;
}