#include "Resources/FontManager/FontManager.h"
#include "Core/GameSettings/GameSettings.h"
#include "Core/Window/WindowManager.h"


void initSingletons()
{
	FontManager::FontManager::getInstance();
	GameSettings::GameSettings::getInstance();
	Window::WindowManager::getInstance();
}



int main()
{
	initSingletons();

	

	return 0;
}