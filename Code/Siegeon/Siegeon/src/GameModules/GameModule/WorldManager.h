#pragma once

#include <memory>
#include <SFML/System.hpp>

#include "World.h"
#include "SharedState.h"


namespace GameModule
{
	class WorldManager
	{
	public:

		WorldManager(std::shared_ptr<SharedState> sharedState);
		virtual ~WorldManager();

		virtual void setWorldState(std::shared_ptr<World> worldState) = 0;
		virtual void copyWorld(std::shared_ptr<World> from, std::shared_ptr<World> to) = 0;

		virtual void init() = 0;
		virtual void run() final;

		virtual void devicesUpate() = 0;
		virtual void lightUpdate(double elapsedTime) = 0;
		virtual void heavyUpdate(double elapsedTime) = 0;


	private:

		std::shared_ptr<SharedState> _sharedState;

		sf::Clock _clock;
		double _lightTimer;
		double _heavyTimer;


		virtual void _runInnerLoop() final;

	};
}