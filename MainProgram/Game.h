#pragma once
#include "GameState.h"
#include "NumberBoard.h"
#include "Player.h"
#include "Cow.h"
#include "Entity.h"
#include "Shop.h"
#include <stdlib.h>

class Game : public GameState
{
private:
	int timeCount;
	int updateTime;

	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;

	sf::RectangleShape playerOneInfoBox;
	sf::RectangleShape playerTwoInfoBox;
	sf::RectangleShape gameArea;

	bool gameOver;
	sf::Font endFont;
	sf::Text endText;
	sf::Text storeText;
	Player* winner;
	sf::RectangleShape gameOverScreen;

	NumberBoard* theNumberBoard;

	Player playerOne;
	Player playerTwo;

	int nrOfCows;
	int cowCapacity;
	Cow* *cows;

	Shop shop;


	void sortEntities();
	static const int nrOfEntities = 4;
	Entity* allEntities[nrOfEntities];

	State currentState;


public:
	Game();
	virtual ~Game();	

	Cow* cowGoTo(sf::Vector2f pos);

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

};
