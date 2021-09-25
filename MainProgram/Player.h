#pragma once

#include "Entity.h"
enum class PlayerId {PlayerOne, PlayerTwo};
class Player : public Entity {

private:
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;

	sf::RectangleShape* gameArea;

public :
	Player(PlayerId player, sf::RectangleShape *gameArea);



	// Inherited via Entity

	virtual void move() override;

};