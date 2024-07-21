#include "Resources/FontManager/FontManager.h"
#include "Core/GameSettings/GameSettings.h"
#include "Core/Window/WindowManager.h"

#include "GameModules/MainMenu/MainMenu.h"


void initSingletons()
{
	FontManager::FontManager::getInstance();
	GameSettings::GameSettings::getInstance();
	Window::WindowManager::getInstance();
}

void playGame()
{
	using namespace GameModules::MainMenu;

	std::unique_ptr<MainMenu> menu = std::make_unique<MainMenu>();
	menu->run();
}



int main()
{
	initSingletons();

	playGame();


	return 0;
}