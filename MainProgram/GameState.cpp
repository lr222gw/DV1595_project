#include "GameState.h"

GameState::GameState(std::string title)
	:window(sf::VideoMode(1200, 600), title)
{
}

GameState::~GameState()
{
}
