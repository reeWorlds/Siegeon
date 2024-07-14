#pragma once

#include <memory>
#include <SFML/System.hpp>

#include "WorldState.h"
#include "SharedState.h"


namespace GameLoop
{
	class GameStateManager
	{
	public:

		GameStateManager(std::shared_ptr<WorldState> worldState, std::shared_ptr<SharedState> sharedState);
		virtual ~GameStateManager();

		virtual void setWorldState(std::shared_ptr<WorldState> worldState) = 0;
		virtual void transitionGameState(std::shared_ptr<WorldState> from, std::shared_ptr<WorldState> to) = 0;

		virtual void init() = 0;
		virtual void run() final;

		virtual void deviceUpate() = 0;
		virtual void lightUpdate(double elapsedTime) = 0;
		virtual void heavyUpdate(double elapsedTime) = 0;


	private:

		std::shared_ptr<WorldState> _worldState;
		std::shared_ptr<SharedState> _sharedState;

		sf::Clock _clock;
		double lightTimer;
		double heavyTimer;


		void _runInnerLoop();

	};
}