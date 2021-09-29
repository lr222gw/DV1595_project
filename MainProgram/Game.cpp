#include "Game.h"
#include <iostream>
#include "State.h"

void Game::sortEntities()
{
	for (int i = 0; i < nrOfEntities-1; i++) {
		int lowestEntityIndex = i;
		float lowestEntityValue = allEntities[lowestEntityIndex]->getBounds().height + allEntities[lowestEntityIndex]->getBounds().top;
		for (int j = i + 1; j < nrOfEntities; j++ ) {
			float yPosOfEntityJ = allEntities[j]->getBounds().height + allEntities[j]->getBounds().top;
			
			if (lowestEntityValue > yPosOfEntityJ) {
				lowestEntityIndex = j;
				lowestEntityValue = allEntities[lowestEntityIndex]->getBounds().height + allEntities[lowestEntityIndex]->getBounds().top;
			}
		}
		Entity* temp = allEntities[i];
		allEntities[i] = allEntities[lowestEntityIndex];
		allEntities[lowestEntityIndex] = temp;
	}
}

Game::Game()
	:GameState("Game"),
	playerOne(PlayerId::PlayerOne, &this->gameArea),
	playerTwo(PlayerId::PlayerTwo, &this->gameArea)
{
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);

	srand(time(NULL));

	playerOneInfoBox.setFillColor(sf::Color::Cyan);
	playerTwoInfoBox.setFillColor(sf::Color::Cyan);

	float oneSixthOfScreenWidth = window.getSize().x / 6.f;
	float fourSixthOfScreenWidth = oneSixthOfScreenWidth * 4;
	playerOneInfoBox.setSize(sf::Vector2f(oneSixthOfScreenWidth, window.getSize().y));
	playerOneInfoBox.setPosition(0.f, 0.f);
	playerTwoInfoBox.setSize(sf::Vector2f(oneSixthOfScreenWidth, window.getSize().y));
	playerTwoInfoBox.setPosition(window.getSize().x - oneSixthOfScreenWidth, 0.f);

	float padding = 4;
	gameArea.setFillColor(sf::Color::Green);
	gameArea.setSize(sf::Vector2f(fourSixthOfScreenWidth - padding, window.getSize().y));
	gameArea.setPosition(oneSixthOfScreenWidth + padding/2, 0.f);	

	theNumberBoard = new NumberBoard(gameArea.getGlobalBounds());
	playerOne.initBingoBoard(theNumberBoard);
	playerTwo.initBingoBoard(theNumberBoard);

	cowCapacity = 2;
	cows = new Cow * [cowCapacity];
	for (int i = 0; i < cowCapacity; i++)
	{
		cows[i] = new Cow(theNumberBoard, theNumberBoard->getBounds(), 2);
		nrOfCows++;
	}
	
	allEntities[0] = cows[0];
	allEntities[1] = cows[1];
	allEntities[2] = &playerOne;
	allEntities[3] = &playerTwo;

	currentState = State::NO_CHANGE;	
}

Game::~Game()
{
	for (int i = 0; i < nrOfCows; i++)
	{
		delete cows[i];
	}
	delete[] cows;
	delete theNumberBoard;
}


State Game::update()
{
	State finalState = currentState;
	
	elapsedTimeSinceLastUpdate += clock.restart();
	
	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;
		
		
		
		playerOne.update();
		playerTwo.update();
		
		for (int i = 0; i < nrOfCows; i++)
		{
			cows[i]->update();
			cows[i]->updateTimeCounter();
		}
	
	}

	theNumberBoard->markTileAsCrapped(this->playerOne.getBounds());
	
	/*

	om ingen förändring har skett ska retur göras motsvarande ingen förändring och annars ska State HIGHSCORE_INPUT returneras

	*/

	
	return finalState;
}

void Game::render()
{
	window.clear();
	
	window.draw(playerOneInfoBox);
	window.draw(playerTwoInfoBox);
	window.draw(gameArea);
	
	window.draw(*theNumberBoard);

	this->sortEntities();
	for (int i = 0; i < nrOfEntities; i++) {
		window.draw(*allEntities[i]);
	}
	window.display();
}

void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			currentState = State::EXIT;
			window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				currentState = State::MENU;
			}
		}
	}
}






