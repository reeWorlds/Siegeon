#include "World.h"
#include "../../Core/GameSettings/GameSettings.h"


namespace GameModules
{
	namespace MainMenu
	{
		World::World()
		{
			pos = 200.0;

			_initInterfaceComponents();
			_constructInterface();
		}

		World::World(const World& other)
		{
			pos = other.pos;

			_copyInterfaceComponents(other);
			_constructInterface();
		}

		World::~World() { }

		void World::_initInterfaceComponents()
		{
			interface = std::make_shared<UI::Interface>();
			button = std::make_shared<UI::Button>();
		}
		
		void World::_copyInterfaceComponents(const World& other)
		{
			interface = std::make_shared<UI::Interface>(*other.interface);
			button = std::make_shared<UI::Button>(*other.button);
		}
		
		void World::_constructInterface()
		{
			interface->addWidget(std::static_pointer_cast<UI::Widget>(button));

			sf::Vector2i resolution = GameSettings::GameSettings::getInstance().getResolutionInt();
			std::string fontName = GameSettings::GameSettings::getInstance().getFontName();
			interface->construct(resolution.x, resolution.y, fontName);
		}
	}
}