#pragma once

#include "Entity.h"
#include "BingoBoard.h"
//#include "Stone.h"
#include "Item.h"
#include "ControllerConfigurator.h"

class Shop;
enum class PlayerId {PlayerOne, PlayerTwo};
class Player : public Entity {

private:		
	PlayerId playerId;
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;
	sf::Keyboard::Key bingoKey;
	sf::Keyboard::Key actionKey;
	sf::Keyboard::Key buyKey;
	
	sf::Vector2f direction;

	sf::RectangleShape playerInfoBox;
	sf::RectangleShape* gameArea;
	BingoBoard *bingoBoard;
	Shop *shop;
	int money; 

	//TODO: Rethink array... 
	static const int itemsCAP = 10;
	int nrOfItems;
	int selectedItem;
	Item* items[itemsCAP];
	
	sf::Font status_font;
	sf::Text status_string;

	bool wonTheGame;

public :
	Player(PlayerId player, sf::RectangleShape *gameArea);
	virtual ~Player();
	void initBingoBoard(NumberBoard* numberBoard);
	void setShop(Shop* shop);

	const sf::Vector2f getDirection() const;

	void recieveItem(Item* item);
	void addMoney(int amount);
	int getMoney() const;
	void removeMoney(int amount);
	bool hasWon();	

	std::string getPlayerIdentity();

	void checkEventInput(sf::Event event);

	// Inherited via Entity
	virtual void move() override;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};