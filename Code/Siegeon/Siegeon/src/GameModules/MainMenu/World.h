#pragma once

#include "../GameModule/World.h"


namespace GameModules
{
	namespace MainMenu
	{
		class World : public GameModule::World
		{
		public:

			double pos;

			World();
			~World();

		};
	}
}