#include "Player.h"

Player::Player(PlayerId player)
{
	
	switch (player) {
	case PlayerId::PlayerOne:
		upKey	= sf::Keyboard::Key::W;
		downKey = sf::Keyboard::Key::S;
		leftKey = sf::Keyboard::Key::A;
		rightKey= sf::Keyboard::Key::D;

		this->setTexture("../Images/sprites/playerOne.png");

		break;
	case PlayerId::PlayerTwo:
		upKey	= sf::Keyboard::Key::Up;
		downKey = sf::Keyboard::Key::Down;
		leftKey = sf::Keyboard::Key::Left;
		rightKey= sf::Keyboard::Key::Right;
		this->setTexture("../Images/sprites/playerTwo.png");
		break;
	}
}


void Player::move()
{



}
