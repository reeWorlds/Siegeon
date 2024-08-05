#pragma once

#include "../GameModule/World.h"
#include "../../Graphics/UI/Interface.h"
#include "../../Graphics/UI/WidgetGroup.h"
#include "../../Graphics/UI/Button.h"
#include "../../Graphics/UI/TextureHolder.h"


namespace GameModules
{
	namespace MainMenu
	{
		class World : public GameModule::World
		{
		public:

			std::shared_ptr<UI::Interface> interface;

			std::shared_ptr<UI::WidgetGroup> menuGroup;
			std::shared_ptr<UI::Button> newGameButton;
			std::shared_ptr<UI::Button> continueGameButton;
			std::shared_ptr<UI::Button> settingsButton;
			std::shared_ptr<UI::Button> exitButton;

			double logoTimeX;
			double logoTimeY;
			std::shared_ptr<UI::TextureHolder> logo;


			World();
			World(const World& other);
			~World();


		private:

			void _initInterfaceComponents();
			void _initMenuButton(std::shared_ptr<UI::Button>& button, double centerY, const char* text);
			void _copyInterfaceComponents(const World& other);
			void _constructInterface();

		};
	}
}