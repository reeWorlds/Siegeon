#pragma once

#include "../GameModule/World.h"
#include "../../Graphics/UI/Interface.h"
#include "../../Graphics/UI/Button.h"


namespace GameModules
{
	namespace MainMenu
	{
		class World : public GameModule::World
		{
		public:

			double pos;

			std::shared_ptr<UI::Interface> interface;
			std::shared_ptr<UI::Button> button;


			World();
			World(const World& other);
			~World();


		private:

			void _initInterfaceComponents();
			void _copyInterfaceComponents(const World& other);
			void _constructInterface();

		};
	}
}