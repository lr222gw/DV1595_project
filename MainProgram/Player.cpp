#include "Player.h"

Player::Player(PlayerId player)
	: Entity("../Images/sprites/player1.png",4,4,4)
{
	
	switch (player) {
	case PlayerId::PlayerOne:
		upKey	= sf::Keyboard::Key::W;
		downKey = sf::Keyboard::Key::S;
		leftKey = sf::Keyboard::Key::A;
		rightKey= sf::Keyboard::Key::D;

		this->setTexture("../Images/sprites/player1.png");
		this->moveSprite(100.f, 0.f);

		break;
	case PlayerId::PlayerTwo:
		upKey	= sf::Keyboard::Key::Up;
		downKey = sf::Keyboard::Key::Down;
		leftKey = sf::Keyboard::Key::Left;
		rightKey= sf::Keyboard::Key::Right;
		this->setTexture("../Images/sprites/player2.png");
		this->moveSprite(60.f,0.f);
		break;
	}
}


void Player::move()
{
	if (sf::Keyboard::isKeyPressed(this->upKey))
	{
		this->getAnimationHelper()->animateUp();
		this->moveSprite(0.f,UP);
	}
	else if (sf::Keyboard::isKeyPressed(this->downKey))
	{
		this->getAnimationHelper()->animateDown();
		this->moveSprite(0.f, DOWN);
	}else if (sf::Keyboard::isKeyPressed(this->rightKey))
	{
		this->getAnimationHelper()->animateRight();
		this->moveSprite(RIGHT, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(this->leftKey)) {
		this->getAnimationHelper()->animateLeft();
		this->moveSprite(LEFT, 0.f);
	}
	else {
		this->getAnimationHelper()->animateIdle();
	}


}
