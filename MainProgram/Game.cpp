#include "Game.h"
#include <iostream>
#include "State.h"

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

	cowCapacity = 1;
	cows = new Cow * [cowCapacity];
	for (int i = 0; i < cowCapacity; i++)
	{
		cows[i] = new Cow(theNumberBoard, theNumberBoard->getBounds(), 2);
		nrOfCows++;
	}

	currentState = State::NO_CHANGE;	
}

Game::~Game()
{
	for (int i = 0; i < nrOfCows; i++)
	{
		delete cows[i];
	}
	delete[] cows;
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

		theNumberBoard->markTileAsCrapped(playerOne.getBounds());
	}
	
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

	window.draw(playerOne);
	window.draw(playerTwo);
	for (int i = 0; i < nrOfCows; i++)
	{
		window.draw(*cows[i]);
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






