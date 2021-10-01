#include "Player.h"

Player::Player(PlayerId player, sf::RectangleShape* gameArea)
	: Entity(4), bingoBoard(nullptr), wonTheGame(false), nrOfItems(0), selectedItem(0)
{
	this->gameArea = gameArea;
	this->status_font.loadFromFile("../Images/fonts/BingoReky.ttf");
	this->status_string.setFont(status_font);
	this->status_string.setCharacterSize(30);
	this->status_string.setString("Money: 0");
	switch (player) {
	case PlayerId::PlayerOne:
		upKey	= sf::Keyboard::Key::W;
		downKey = sf::Keyboard::Key::S;
		leftKey = sf::Keyboard::Key::A;
		rightKey= sf::Keyboard::Key::D;
		bingoKey = sf::Keyboard::Key::C;
		actionKey = sf::Keyboard::Key::Space;

		this->setTexture("../Images/sprites/player1_test.png", 4,4,4,4);
		this->getAnimationHelper()->setRowAnimationInstruction(1, 0, 2, 3, 0);
		this->moveSprite(100.f, 0.f);
		this->playerId = PlayerId::PlayerOne;		

		break;
	case PlayerId::PlayerTwo:
		upKey	= sf::Keyboard::Key::Numpad8;
		downKey = sf::Keyboard::Key::Numpad5;
		leftKey = sf::Keyboard::Key::Numpad4;
		rightKey= sf::Keyboard::Key::Numpad6;
		bingoKey = sf::Keyboard::Key::Numpad3;
		actionKey = sf::Keyboard::Key::Enter;
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
		this->status_string.setPosition(sf::Vector2f(40.f, 500.f));
	}
	else if (this->playerId == PlayerId::PlayerTwo) {

		this->bingoBoard = new BingoBoard(numberBoard, 
			sf::Vector2f(this->gameArea->getGlobalBounds().left + this->gameArea->getGlobalBounds().width,0.f)
		);
		this->status_string.setPosition(
			sf::Vector2f(
				this->gameArea->getGlobalBounds().left + this->gameArea->getGlobalBounds().width +40.f,
				500.f)
		);
	}
}

const sf::Vector2f Player::getDirection() const
{
	return direction;
}

void Player::recieveItem(Item* item)
{
	if (nrOfItems < itemsCAP) {
		this->items[nrOfItems++] = item;
	}
}

void Player::addMoney(int amount)
{
	this->money += amount;
	this->status_string.setString("Money: "+ std::to_string(this->money));
}

int Player::getMoney() const
{
	return money;
}

bool Player::hasWon()
{
	return wonTheGame;
}

std::string Player::getPlayerIdentity()
{
	std::string toReturn; 
	if (this->playerId == PlayerId::PlayerOne) 
	{
		toReturn = "Player One";
	}
	else if(this->playerId == PlayerId::PlayerTwo) 
	{
		toReturn = "Player Two";

	}
	return toReturn;
}


void Player::move()
{
	if (sf::Keyboard::isKeyPressed(this->upKey))
	{
		if (this->gameArea->getGlobalBounds().top < this->getBounds().top) 
		{
			this->getAnimationHelper()->animateUp();
			this->moveSprite(0.f,UP);
			direction.x = 0.f;
			direction.y = UP;
		}
	}
	else if (sf::Keyboard::isKeyPressed(this->downKey))
	{
		if (this->gameArea->getGlobalBounds().height > this->getBounds().top + this->getBounds().height)
		{
			this->getAnimationHelper()->animateDown();
			this->moveSprite(0.f, DOWN);
			direction.x = 0.f;
			direction.y = DOWN;
		}
	}else if (sf::Keyboard::isKeyPressed(this->rightKey))
	{
		if (this->gameArea->getGlobalBounds().left + this->gameArea->getGlobalBounds().width > this->getBounds().left + this->getBounds().width)
		{
			this->getAnimationHelper()->animateRight();
			this->moveSprite(RIGHT, 0.f);
			direction.x = RIGHT;
			direction.y = 0.f;
		}
	}
	else if (sf::Keyboard::isKeyPressed(this->leftKey)) 
	{
		if (this->gameArea->getGlobalBounds().left < this->getBounds().left)
		{
			this->getAnimationHelper()->animateLeft();
			this->moveSprite(LEFT, 0.f);
			direction.x = LEFT;
			direction.y = 0.f;
		}
	}
	else {
		this->getAnimationHelper()->animateIdle();
	}

	if (sf::Keyboard::isKeyPressed(this->bingoKey))
	{
		if (this->bingoBoard->checkBingo()) {
			this->wonTheGame = true;
			//Rotate player to look into camera...
			this->getAnimationHelper()->animateDown();
		}
	}

	if (nrOfItems != 0 && items[selectedItem]) {
		items[selectedItem]->setPosition(this->getBounds().left, this->getBounds().top);
		
	}

	if (sf::Keyboard::isKeyPressed(this->actionKey) && items[selectedItem])
	{
		items[selectedItem]->use(this);
		items[selectedItem] = nullptr;
	}
	

	//TODO: should be placed somewhere else... Optimally only if a Animal defecates...
	this->bingoBoard->updateBingoBoard();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw( target, states);
	target.draw(*bingoBoard);	

	target.draw(this->status_string);
}
