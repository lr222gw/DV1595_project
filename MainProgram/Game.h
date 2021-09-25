#pragma once
#include "GameState.h"
#include "NumberBoard.h"
#include "Player.h"
#include "Cow.h"
#include <stdlib.h>

class Game : public GameState
{
private:

	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;

	sf::RectangleShape playerOneInfoBox;
	sf::RectangleShape playerTwoInfoBox;
	sf::RectangleShape gameArea;

	NumberBoard theNumberBoard;

	Player playerOne;
	Player playerTwo;

	int nrOfCows;
	int cowCapacity;
	Cow* *cows;

	State currentState;


public:
	Game();
	virtual ~Game();	

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

};
