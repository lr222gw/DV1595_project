#include "GameState.h"

GameState::GameState(std::string title)
	:window(sf::VideoMode(600, 600), title)
{
}

GameState::~GameState()
{
}
