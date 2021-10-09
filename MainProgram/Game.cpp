#include "Game.h"
#include <iostream>
#include "State.h"

void Game::sortEntities()
{
	for (int i = 0; i < nrOfEntities-1; i++) 
	{
		int lowestEntityIndex = i;
		float lowestEntityValue = allEntities[lowestEntityIndex]->getBounds().height + allEntities[lowestEntityIndex]->getBounds().top;
		for (int j = i + 1; j < nrOfEntities; j++ ) 
		{
			float yPosOfEntityJ = allEntities[j]->getBounds().height + allEntities[j]->getBounds().top;
			
			if (lowestEntityValue > yPosOfEntityJ) 
			{
				lowestEntityIndex = j;
				lowestEntityValue = allEntities[lowestEntityIndex]->getBounds().height + allEntities[lowestEntityIndex]->getBounds().top;
			}
		}
		Entity* temp = allEntities[i];
		allEntities[i] = allEntities[lowestEntityIndex];
		allEntities[lowestEntityIndex] = temp;
	}
}

Game::Game()
	:GameState("Game"),
	playerOne(PlayerId::PlayerOne, &this->gameArea),
	playerTwo(PlayerId::PlayerTwo, &this->gameArea),
	gameOver(false),
	winner(nullptr), updateTime(60), timeCount(0), nrOfCows(0)
{
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);

	srand(time(NULL));

	

	float oneSixthOfScreenWidth = window.getSize().x / 6.f;
	float fourSixthOfScreenWidth = oneSixthOfScreenWidth * 4;

	float padding = 4;
	gameArea.setFillColor(sf::Color::Green);
	gameArea.setSize(sf::Vector2f(fourSixthOfScreenWidth - padding, window.getSize().y));
	gameArea.setPosition(oneSixthOfScreenWidth + padding/2, 0.f);	

	gameOverScreen.setSize(sf::Vector2f((float)this->window.getSize().x, (float)this->window.getSize().y));
	gameOverScreen.setFillColor(sf::Color::Black);
	endFont.loadFromFile("../Images/fonts/BingoReky.ttf");
	endText.setFont(endFont);
	endText.setCharacterSize(80);
	endText.setPosition(
		(float)this->window.getSize().x/4.f, 
		(float)this->window.getSize().y / 4.f 
	);    

	storeText.setFont(endFont);
	storeText.setCharacterSize(30);
	storeText.setPosition(
		(float)this->window.getSize().x / 3.f,
		(float)this->window.getSize().y / 1.2f
	);

	theNumberBoard = new NumberBoard(gameArea.getGlobalBounds());
	playerOne.initBingoBoard(theNumberBoard);
	playerTwo.initBingoBoard(theNumberBoard);
	playerOne.setShop(&shop);
	playerTwo.setShop(&shop);

	cowCapacity = 2;
	cows = new Cow * [cowCapacity];
	for (int i = 0; i < cowCapacity; i++)
	{
		cows[i] = new Cow(theNumberBoard, theNumberBoard->getBounds(), 2);
		nrOfCows++;
	}
	
	allEntities[0] = &playerOne;
	allEntities[1] = &playerTwo;
	allEntities[2] = cows[0];
	allEntities[3] = cows[1];

	shop.setGamePtr(this);
	//shop.restockItems();
	shop.initShop();


	currentState = State::NO_CHANGE;	
}

Game::~Game()
{
	for (int i = 0; i < nrOfCows; i++)
	{
		delete cows[i];
	}
	delete[] cows;
	delete theNumberBoard;
}

Cow* Game::cowGoTo(sf::Vector2f pos)
{
	Cow *goToCow = nullptr;
	for (int i = 0; i < nrOfCows && !goToCow; i++)
	{
		if (!cows[i]->hasGoal()) {
			goToCow = cows[i];
			sf::Vector2f cowPos(
				goToCow->getBounds().left + goToCow->getBounds().width / 2.f,
				goToCow->getBounds().top + goToCow->getBounds().height/ 2.f
			);
			goToCow->setGoal(pos - cowPos);
			
		}
	}
	return goToCow;
}

void Game::checkCollisionPooAndItem() const
{
	Poo** poos = this->theNumberBoard->getPoos();
	const int nrOfPoos = this->theNumberBoard->getNrOfPoos();
	for (int i = 0; i < nrOfPoos; i++) {
		Item* item = this->shop.checkCollision(poos[i]->getBounds());
		if (item) {
			item->collided(poos[i]);
		}
	}
}

void Game::unmarkTileAsCrapped_forwarded(sf::FloatRect poo_floatRect)
{
	this->theNumberBoard->unmarkTileAsCrapped(poo_floatRect);
}

bool Game::isOutSideGameArea(sf::FloatRect floatRect) const
{
	bool isOutside = false;
	if (floatRect.left + floatRect.width < this->gameArea.getGlobalBounds().left) {
		isOutside = true;
	}
	else if (floatRect.left > this->gameArea.getGlobalBounds().left + this->gameArea.getGlobalBounds().width) {
		isOutside = true;
	}
	else if (floatRect.top + floatRect.height  < this->gameArea.getGlobalBounds().top) {
		isOutside = true;
	}
	else if (floatRect.top > this->gameArea.getGlobalBounds().height) {
		isOutside = true;
	}

	return isOutside;
}


State Game::update()
{
	State finalState = currentState;
	
	elapsedTimeSinceLastUpdate += clock.restart();	
	
	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;
		
		
		if (!playerOne.hasWon() && !playerTwo.hasWon()) {
			
			playerOne.update();
			playerTwo.update();
		
			//Check if a item collides with any Cow
			for (int i = 0; i < nrOfCows; i++)
			{
				Item* item = shop.checkCollision(cows[i]->getBounds()); // Checks collision with all items...
				if (item) {
					item->collided(cows[i]);					
				}
				cows[i]->update();
				cows[i]->updateTimeCounter();
			}

			//Check if Poo Collides with any Items
			checkCollisionPooAndItem();
			/*for (int i = 0; i < this->theNumberBoard->collidedWithPoo()) {

			}*/
			

		}
		else if(!gameOver) {
			winner = playerOne.hasWon() ? &playerOne : &playerTwo;
			endText.setString("Game Over!\nThe Winner is\n"+winner->getPlayerIdentity());
			gameOver = true;
			winner->setPosition(endText.getPosition().x + endText.getGlobalBounds().width, 500.f );
			
		}
		
		this->shop.updateItems();
		storeText.setString("Buy Item: " + this->shop.presentItem());
	}

	//theNumberBoard->markTileAsCrapped(this->playerOne.getBounds());

	timeCount = (timeCount + 1) % (60*5);
	if (timeCount == 0) {
		playerOne.addMoney(5);
		playerTwo.addMoney(5);
	}

	/*

	om ingen förändring har skett ska retur göras motsvarande ingen förändring och annars ska State HIGHSCORE_INPUT returneras

	*/

	
	return finalState;
}

void Game::render()
{
	window.clear();
	
	window.draw(gameArea);
	
	if (!gameOver) {
		window.draw(*theNumberBoard);

		this->sortEntities();
		for (int i = 0; i < nrOfEntities; i++) {
			window.draw(*allEntities[i]);
		}
		
		window.draw(this->shop);
		window.draw(this->storeText);

		//window.draw(playerOneInfoBox);
		//window.draw(playerTwoInfoBox);
	}
	else {
		window.draw(gameOverScreen);
		window.draw(endText);
		window.draw(*winner);
	}

	window.display();
}

void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		
		if (event.type == sf::Event::Closed)
		{
			currentState = State::EXIT;
			window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				currentState = State::MENU;
			}
		}

		playerOne.checkEventInput(event);
		playerTwo.checkEventInput(event);
	}
}






