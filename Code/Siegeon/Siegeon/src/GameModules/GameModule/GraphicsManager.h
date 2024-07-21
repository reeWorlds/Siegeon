#pragma once

#include <memory>
#include <SFML/System.hpp>

#include "World.h"
#include "SharedState.h"


namespace GameModule
{
	class GraphicsManager
	{
	public:

		GraphicsManager(std::shared_ptr<SharedState> sharedState);
		virtual ~GraphicsManager();

		virtual void setWorld(std::shared_ptr<World> world) = 0;

		virtual void init() = 0;
		virtual void run() final;

		virtual void render() = 0;


	private:

		std::shared_ptr<SharedState> _sharedState;

		sf::Clock _clock;
		double _timer;


		virtual void _runInnerLoop() final;

	};
}