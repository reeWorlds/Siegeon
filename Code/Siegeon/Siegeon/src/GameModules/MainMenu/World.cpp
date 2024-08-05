#include "World.h"
#include "Constants.h"
#include "../../Core/GameSettings/GameSettings.h"
#include "../../Resources/TextureManager/TextureManager.h"


namespace GameModules
{
	namespace MainMenu
	{
		World::World()
		{
			logoTimeX = 0.0;
			logoTimeY = 0.0;

			_initInterfaceComponents();
			_constructInterface();
		}

		World::World(const World& other)
		{
			logoTimeX = other.logoTimeX;
			logoTimeY = other.logoTimeY;

			_copyInterfaceComponents(other);
			_constructInterface();
		}

		World::~World() { }

		void World::_initInterfaceComponents()
		{
			TextureManager::MainMenuTextures& textures = TextureManager::
				TextureManager::getMainMenuTexturesInstance();

			interface = std::make_shared<UI::Interface>();

			menuGroup = std::make_shared<UI::WidgetGroup>();

			newGameButton = std::make_shared<UI::Button>();
			_initMenuButton(newGameButton, MENU_BUTTON_NEW_GAME_CEXTER_Y,
				MENU_BUTTON_NEW_GAME_TEXT_STRING);
			newGameButton->setAvailable(false); // todo
			continueGameButton = std::make_shared<UI::Button>();
			_initMenuButton(continueGameButton, MENU_BUTTON_CONTINUE_CEXTER_Y,
				MENU_BUTTON_CONTINUE_TEXT_STRING);
			continueGameButton->setAvailable(false); // todo
			settingsButton = std::make_shared<UI::Button>();
			_initMenuButton(settingsButton, MENU_BUTTON_SETTINGS_CEXTER_Y,
				MENU_BUTTON_SETTINGS_TEXT_STRING);
			settingsButton->setAvailable(false); // todo
			exitButton = std::make_shared<UI::Button>();
			_initMenuButton(exitButton, MENU_BUTTON_EXIT_CEXTER_Y, MENU_BUTTON_EXIT_TEXT_STRING);

			logo = std::make_shared<UI::TextureHolder>(LOGO_CEXTER_X, LOGO_CEXTER_Y, LOGO_HALF_WIDTH,
				LOGO_HALF_HEIGHT);
			logo->setTexture(*textures.getLogoTexture());
			logo->setScalingMode(LOGO_SCALING_MODE);
		}

		void World::_initMenuButton(std::shared_ptr<UI::Button>& button, double centerY, const char* text)
		{
			button->setGeometry(MENU_BUTTON_CEXTER_X, centerY, MENU_BUTTON_HALF_WIDTH,
				MENU_BUTTON_HALF_HEIGHT);
			button->setColors(MENU_BUTTON_IDLE_COLOR, MENU_BUTTON_HOVER_COLOR, MENU_BUTTON_ACTIVE_COLOR,
				MENU_BUTTON_UNAVAILABLE_COLOR);
			button->setTextString(text);
			button->setTextCharacterSize(MENU_BUTTON_TEXT_SIZE);
			button->setTextStyle(MENU_BUTTON_TEXT_STYLE);
		}
		
		void World::_copyInterfaceComponents(const World& other)
		{
			interface = std::make_shared<UI::Interface>(*other.interface);

			menuGroup = std::make_shared<UI::WidgetGroup>(*other.menuGroup);

			newGameButton = std::make_shared<UI::Button>(*other.newGameButton);
			continueGameButton = std::make_shared<UI::Button>(*other.continueGameButton);
			settingsButton = std::make_shared<UI::Button>(*other.settingsButton);
			exitButton = std::make_shared<UI::Button>(*other.exitButton);

			logo = std::make_shared<UI::TextureHolder>(*other.logo);
		}
		
		void World::_constructInterface()
		{
			interface->addWidget(std::static_pointer_cast<UI::Widget>(menuGroup));

			menuGroup->addWidget(std::static_pointer_cast<UI::Widget>(newGameButton));
			menuGroup->addWidget(std::static_pointer_cast<UI::Widget>(continueGameButton));
			menuGroup->addWidget(std::static_pointer_cast<UI::Widget>(settingsButton));
			menuGroup->addWidget(std::static_pointer_cast<UI::Widget>(exitButton));

			interface->addWidget(std::static_pointer_cast<UI::Widget>(logo));

			sf::Vector2i resolution = GameSettings::GameSettings::getInstance().getResolutionInt();
			std::string fontName = GameSettings::GameSettings::getInstance().getFontName();
			interface->construct(resolution.x, resolution.y, fontName);
		}
	}
}