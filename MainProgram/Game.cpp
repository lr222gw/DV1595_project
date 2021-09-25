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

	currentState = State::NO_CHANGE;	
}

Game::~Game()
{
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

	window.draw(playerOne);
	window.draw(playerTwo);

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






