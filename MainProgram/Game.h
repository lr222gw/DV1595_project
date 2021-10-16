#pragma once
#include "GameState.h"
#include "NumberBoard.h"
#include "Player.h"
#include "Cow.h"
#include "Entity.h"
#include "Shop.h"
#include <stdlib.h>
#include <SFML/Audio.hpp>

class Game : public GameState
{
private:
	int timeCount;
	int updateTime;

	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
	
	sf::RectangleShape gameArea;

	sf::SoundBuffer gameOver_soundB;
	sf::Sound sound;
	bool gameOver;
	sf::Font endFont;
	sf::Text endText;
	sf::Text storeText;
	Player* winner;
	sf::RectangleShape gameOverScreen;
	sf::Sprite pauseSprite;
	sf::Texture pauseTexture;

	NumberBoard* theNumberBoard;

	Player playerOne;
	Player playerTwo;

	int nrOfCows;
	int cowCapacity;
	Cow* *cows;

	Shop shop;

	bool paused = false;	

	void togglePause();

	void sortEntities();
	static const int nrOfEntities = 4;
	Entity* allEntities[nrOfEntities];

	State currentState;


public:
	Game();
	virtual ~Game();	

	Cow* cowGoTo(sf::Vector2f pos);
	
	void checkCollisionPooAndItem() const;
	void unmarkTileAsCrapped_forwarded(sf::FloatRect poo_floatRect);
	bool isOutSideGameArea(sf::FloatRect floatRect) const;

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

};
