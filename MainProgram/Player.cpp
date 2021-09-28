#include "Player.h"

Player::Player(PlayerId player, sf::RectangleShape *gameArea)
	: Entity(4), bingoBoard(nullptr)
{
	this->gameArea = gameArea;
	switch (player) {
	case PlayerId::PlayerOne:
		upKey	= sf::Keyboard::Key::W;
		downKey = sf::Keyboard::Key::S;
		leftKey = sf::Keyboard::Key::A;
		rightKey= sf::Keyboard::Key::D;

		this->setTexture("../Images/sprites/player1_test.png", 4,4,4,4);
		this->getAnimationHelper()->setRowAnimationInstruction(1, 0, 2, 3, 0);
		this->moveSprite(100.f, 0.f);
		this->playerId = PlayerId::PlayerOne;

		break;
	case PlayerId::PlayerTwo:
		upKey	= sf::Keyboard::Key::Up;
		downKey = sf::Keyboard::Key::Down;
		leftKey = sf::Keyboard::Key::Left;
		rightKey= sf::Keyboard::Key::Right;
		this->setTexture("../Images/sprites/xperiment2.png", 4, 4, 4, 4);
		this->getAnimationHelper()->setRowAnimationInstruction(1,0,2,3,0);
		this->moveSprite(60.f,0.f);

		this->playerId = PlayerId::PlayerTwo;
		break;
	}
}

Player::~Player()
{
	delete bingoBoard;
}

void Player::initBingoBoard(NumberBoard* numberBoard)
{
	if (this->playerId == PlayerId::PlayerOne) {

		this->bingoBoard = new BingoBoard(numberBoard,sf::Vector2f());
	}
	else if (this->playerId == PlayerId::PlayerTwo) {

		this->bingoBoard = new BingoBoard(numberBoard, 
			sf::Vector2f(this->gameArea->getGlobalBounds().left + this->gameArea->getGlobalBounds().width,0.f));
	}
}


void Player::move()
{
	if (sf::Keyboard::isKeyPressed(this->upKey))
	{
		if (this->gameArea->getGlobalBounds().top < this->getBounds().top) 
		{
			this->getAnimationHelper()->animateUp();
			this->moveSprite(0.f,UP);
		}
	}
	else if (sf::Keyboard::isKeyPressed(this->downKey))
	{
		if (this->gameArea->getGlobalBounds().height > this->getBounds().top + this->getBounds().height)
		{
			this->getAnimationHelper()->animateDown();
			this->moveSprite(0.f, DOWN);
		}
	}else if (sf::Keyboard::isKeyPressed(this->rightKey))
	{
		if (this->gameArea->getGlobalBounds().left + this->gameArea->getGlobalBounds().width > this->getBounds().left + this->getBounds().width)
		{
			this->getAnimationHelper()->animateRight();
			this->moveSprite(RIGHT, 0.f);
		}
	}
	else if (sf::Keyboard::isKeyPressed(this->leftKey)) 
	{
		if (this->gameArea->getGlobalBounds().left < this->getBounds().left)
		{
			this->getAnimationHelper()->animateLeft();
			this->moveSprite(LEFT, 0.f);
		}
	}
	else {
		this->getAnimationHelper()->animateIdle();
	}

	//TODO: should be placed somewhere else... Optimally only if a Animal defecates...
	this->bingoBoard->updateBingoBoard();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw( target, states);
	target.draw(*bingoBoard);
}
