#pragma once
#include "GameState.h"

class Game : public GameState
{
private:

	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;

	sf::RectangleShape playerOneInfoBox;
	sf::RectangleShape playerTwoInfoBox;
	sf::RectangleShape gameArea;

public:
	Game();
	virtual ~Game();
	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

};
