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

	int count = 0; 
	int countPunishedTime = 0;
	int punishTime = 5;

	Player* opponent;

	PlayerId playerId;
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;
	sf::Keyboard::Key bingoKey;
	sf::Keyboard::Key actionKey;
	sf::Keyboard::Key buyKey;
	
	sf::Vector2f direction;
	
	sf::SoundBuffer illegalAction;
	sf::Sound soundPlayer;

	sf::Texture nextItemTexture;
	sf::Sprite nextItem;
	sf::Texture playerInfoBox_texture;
	sf::Sprite playerInfoBox;
	sf::RectangleShape* gameArea;
	BingoBoard *bingoBoard;
	Shop *shop;
	int money; 

	static const int itemsCAP = 12;  //TOOD: Should be based on how many items the Shop allows...
	int nrOfItems;
	int selectedItem;
	Item* items[itemsCAP];
	
	sf::Font status_font;
	sf::Text status_string;

	bool punished;
	bool wonTheGame;

	void updateNextItemIconPosition();
	void updateStatusString();

public :
	Player(PlayerId player, sf::RectangleShape *gameArea);
	virtual ~Player();
	void initBingoBoard(NumberBoard* numberBoard);
	void setShop(Shop* shop);
	void setOpponent(Player* opponent);

	const sf::Vector2f getDirection() const;

	void recieveItem(Item* item);
	void addMoney(int amount);
	int getMoney() const;
	void removeMoney(int amount);
	bool hasWon() const;	

	void punish();

	std::string getPlayerIdentity();

	void checkEventInput(sf::Event event);

	// Inherited via Entity
	virtual void move() override;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};