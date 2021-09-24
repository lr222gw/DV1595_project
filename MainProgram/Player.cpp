#include "Player.h"

Player::Player(PlayerId player)
	: Entity("../Images/sprites/player1.png",4,4,1)
{
	
	switch (player) {
	case PlayerId::PlayerOne:
		upKey	= sf::Keyboard::Key::W;
		downKey = sf::Keyboard::Key::S;
		leftKey = sf::Keyboard::Key::A;
		rightKey= sf::Keyboard::Key::D;

		this->setTexture("../Images/sprites/player1.png");

		break;
	case PlayerId::PlayerTwo:
		upKey	= sf::Keyboard::Key::Up;
		downKey = sf::Keyboard::Key::Down;
		leftKey = sf::Keyboard::Key::Left;
		rightKey= sf::Keyboard::Key::Right;
		this->setTexture("../Images/sprites/player2.png");
		this->moveSprite(40.f,0.f);
		break;
	}
}


void Player::move()
{



}
