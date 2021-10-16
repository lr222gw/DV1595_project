#include "Player.h"
#include "Shop.h"




Player::Player(PlayerId player, sf::RectangleShape* gameArea)
	: Entity(4), bingoBoard(nullptr), wonTheGame(false), nrOfItems(0), selectedItem(0), shop(shop)
{
	static ControllerConfigurator configurator;	
	configurator.loadConfig();

	this->gameArea = gameArea;
	this->status_font.loadFromFile("../Images/fonts/BingoReky.ttf");
	this->status_string.setFont(status_font);
	this->status_string.setCharacterSize(30);
	this->status_string.setString("Money: 0");
	
	playerInfoBox.setFillColor(sf::Color::Black);

	nextItemTexture.loadFromFile("../Images/NEXT.png");
	nextItem.setTexture(nextItemTexture);
	nextItem.setScale(0.08f, 0.08f);
	updateNextItemIconPosition();

	switch (player) {
		case PlayerId::PlayerOne:
			
			upKey	 = configurator.getActionKey(Actions::P1_Up);
			downKey  = configurator.getActionKey(Actions::P1_Down);
			leftKey  = configurator.getActionKey(Actions::P1_Left);
			rightKey = configurator.getActionKey(Actions::P1_Right);
			bingoKey = configurator.getActionKey(Actions::P1_Bingo);
			buyKey	 = configurator.getActionKey(Actions::P1_Buy);
			actionKey= configurator.getActionKey(Actions::P1_Action);

			this->setTexture("../Images/sprites/player1_test.png", 4,4,4,4);
			this->getAnimationHelper()->setRowAnimationInstruction(1, 0, 2, 3, 0);
			this->moveSprite(100.f, 0.f);
			this->playerId = PlayerId::PlayerOne;				

			break;
		case PlayerId::PlayerTwo:
			upKey	 = configurator.getActionKey(Actions::P2_Up);
			downKey  = configurator.getActionKey(Actions::P2_Down);
			leftKey  = configurator.getActionKey(Actions::P2_Left);
			rightKey = configurator.getActionKey(Actions::P2_Right);
			bingoKey = configurator.getActionKey(Actions::P2_Bingo);
			buyKey	 = configurator.getActionKey(Actions::P2_Buy);
			actionKey= configurator.getActionKey(Actions::P2_Action);
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

		this->bingoBoard = new BingoBoard(numberBoard,sf::Vector2f(0.f, 0.f));
		this->status_string.setPosition(sf::Vector2f(40.f, 500.f));
		playerInfoBox.setSize(sf::Vector2f(gameArea->getGlobalBounds().left, gameArea->getGlobalBounds().height));
		playerInfoBox.setPosition(0.f, 0.f);
		float margin = (gameArea->getGlobalBounds().left / 2.f) - this->bingoBoard->getBingoBoardSize().x / 2.f; // Needs to be executed after initialization of bingoBoard...
		this->bingoBoard->setPosition(sf::Vector2f(margin, margin));
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
		float margin = (gameArea->getGlobalBounds().left / 2.f) - this->bingoBoard->getBingoBoardSize().x / 2.f; // Needs to be executed after initialization of bingoBoard...
		this->bingoBoard->setPosition(sf::Vector2f(margin + this->gameArea->getGlobalBounds().left + this->gameArea->getGlobalBounds().width, margin));

		playerInfoBox.setSize(sf::Vector2f(gameArea->getGlobalBounds().left, gameArea->getGlobalBounds().height));
		playerInfoBox.setPosition(gameArea->getGlobalBounds().left + gameArea->getGlobalBounds().width, 0.f);
	}
}

void Player::setShop(Shop* shop)
{
	this->shop = shop;
}

void Player::setOpponent(Player* opponent)
{
	this->opponent = opponent;
}

const sf::Vector2f Player::getDirection() const
{
	return direction;
}

void Player::recieveItem(Item* item)
{
	if (nrOfItems < itemsCAP) {
		this->items[nrOfItems++] = item;
		float distanceFromTop = 300.f;
		float distanceBetweenItems = 20.f;
		int itemsPerRow = 5;
		int widthOfRow = 100;
		if (this->playerId == PlayerId::PlayerOne) {

			this->items[nrOfItems - 1]->setPosition(40.f + ((nrOfItems -2) * (int)distanceBetweenItems) % widthOfRow, distanceFromTop + ((nrOfItems - 2) / itemsPerRow)* distanceBetweenItems);
			
			updateNextItemIconPosition();						
		}
		else if (this->playerId == PlayerId::PlayerTwo) {

			this->items[nrOfItems - 1]->setPosition(				
					this->gameArea->getGlobalBounds().left + this->gameArea->getGlobalBounds().width + 40.f  + ((nrOfItems - 2) * (int)distanceBetweenItems) % widthOfRow,
					distanceFromTop + ((nrOfItems - 2) / itemsPerRow) * distanceBetweenItems
			);

			updateNextItemIconPosition();
		}

		this->items[nrOfItems - 1]->setThumbnailScale();
	}
	
}

void Player::addMoney(int amount)
{
	this->money += amount;
	updateStatusString();
	
}

int Player::getMoney() const
{
	return money;
}

void Player::removeMoney(int amount)
{
	this->money -= amount;
	updateStatusString();
}

bool Player::hasWon() const
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

void Player::checkEventInput(sf::Event event)
{ 
	if (!punished) {

		if (event.type == event.KeyPressed && event.key.code == (this->bingoKey))
		{
			if (this->bingoBoard->checkBingo()) {
				this->wonTheGame = true;
				//Rotate player to look into camera...
				this->getAnimationHelper()->animateDown();
			}
			else if (opponent->bingoBoard->checkBingo()) {
				// sabbotage...
				opponent->bingoBoard->sabbotageBingo();
			}
			else {
				//Punish! Cant use item for 5 seconds...
				this->setSpriteColor(sf::Color::Color(255, 200, 200, 100));
				punished = true;
				countPunishedTime = 0;
			}
		}

		if (event.type == event.KeyPressed && event.key.code == (this->buyKey))
		{
			this->shop->buyItem(this);

		}
	
		if (event.type == event.KeyPressed && event.key.code == (this->actionKey) && items[selectedItem])
		{
			if (items[selectedItem]->use(this)) {
				items[selectedItem]->setDefaultScale();
				items[selectedItem] = nullptr;
				items[selectedItem] = items[--nrOfItems];
				updateNextItemIconPosition();
			}
		}
	}
	else {
		// Play a bad sound...
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

	if (nrOfItems != 0 && items[selectedItem]) {
		items[selectedItem]->setPosition(this->getBounds().left, this->getBounds().top);
		
	}
		
	this->bingoBoard->updateBingoBoard();
	if (this->bingoBoard->checkSpecialTiles()) {
		money += 50;
	}

	count++;
	if (punished && count % 60 == 0) {
		countPunishedTime = (countPunishedTime + 1) % (punishTime +1);
	}
	if (punishTime <= countPunishedTime) {
		punished = false;
		this->resetSpriteColor();
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw( target, states);
	target.draw(this->playerInfoBox);
	
	target.draw(*bingoBoard);
	target.draw(this->status_string);
	target.draw(nextItem);
}


void Player::updateNextItemIconPosition()
{
	if (nrOfItems > 1) {
		float distanceFromTop = 300.f;
		float distanceBetweenItems = 20.f;
		int itemsPerRow = 5;
		int widthOfRow = 100;

		if (this->playerId == PlayerId::PlayerOne)
		{
			nextItem.setPosition((float)(40.f + (nrOfItems - 2) * (int)distanceBetweenItems % widthOfRow), distanceBetweenItems + (float)(distanceFromTop + ((nrOfItems - 2) / itemsPerRow) * distanceBetweenItems));
		}
		else
		{
			nextItem.setPosition(
				this->gameArea->getGlobalBounds().left + this->gameArea->getGlobalBounds().width + 40.f + ((nrOfItems - 2) * (int)distanceBetweenItems) % widthOfRow,
				distanceBetweenItems + distanceFromTop + ((nrOfItems - 2) / itemsPerRow) * distanceBetweenItems
			);
		}
	}
	else {

		nextItem.setPosition(-100.f, -100.f);
	}
}

void Player::updateStatusString()
{
	this->status_string.setString("Money: " + std::to_string(this->money));
}
