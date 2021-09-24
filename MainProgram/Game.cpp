#include "Game.h"
#include <iostream>
#include "State.h"

Game::Game()
	:GameState("Game"), circle(50.f)
{
	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(10.f, 250.f);
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
}

Game::~Game()
{
}

State Game::update()
{
	
	elapsedTimeSinceLastUpdate += clock.restart();
	
	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;
		circle.move(4.f, 0);


	}
	
	/*

	om ingen förändring har skett ska retur göras motsvarande ingen förändring och annars ska State HIGHSCORE_INPUT returneras

	*/
	
	return State();
}

void Game::render()
{
	window.clear();
	window.draw(circle);
	window.display();
}

void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}






