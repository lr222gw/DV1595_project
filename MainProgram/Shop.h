#pragma once
#include <SFML/Graphics.hpp>
//#include "Item.h"
#include "Stone.h"
#include "Wheat.h"
#include "Player.h"
#include "DungBeetle.h"
class Game;
class Shop : public sf::Drawable {
private:
	int nrOfItem;
	int itemsCAP;
	Item** items;
	int nrOfSoldItem;
	int soldItemsCAP;
	Item** soldItems;
	int nrOfTerminatedItems;
	int terminatedItemsCAP;
	Item** terminatedItems;

	Game* gamePtr;
	void expand();
public:
	void restockItems();
	Shop();
	virtual ~Shop();
	void setGamePtr(Game* gamePtr);
	void initShop();
	
	std::string presentItem();
	void buyItem(Player* buyer);

	void updateItems();
	Item* checkCollision(sf::FloatRect entityBounds) const;
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};