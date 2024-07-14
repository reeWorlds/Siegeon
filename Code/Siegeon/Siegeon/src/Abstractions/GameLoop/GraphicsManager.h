#pragma once

#include <memory>
#include <SFML/System.hpp>

#include "WorldState.h"
#include "SharedState.h"


namespace GameLoop
{
	class GraphicsManager
	{
	public:

		GraphicsManager(std::shared_ptr<WorldState> worldState, std::shared_ptr<SharedState> sharedState);
		virtual ~GraphicsManager();

		virtual void setWorldState(std::shared_ptr<WorldState> worldState) = 0;

		virtual void init() = 0;
		virtual void run() final;

		virtual void render() = 0;


	private:

		std::shared_ptr<WorldState> _worldState;
		std::shared_ptr<SharedState> _sharedState;

		sf::Clock _clock;
		double timer;


		void _runInnerLoop();

	};
}