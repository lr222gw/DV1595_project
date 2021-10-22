#include "GameState.h"

GameState::GameState(std::string title, sf::RenderWindow* window)	
{
	this->window = window;
	this->window->setTitle(title);
}

GameState::~GameState()
{
}
