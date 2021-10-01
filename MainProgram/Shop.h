#pragma once
#include <SFML/Graphics.hpp>
//#include "Item.h"
#include "Stone.h"
#include "Player.h"

class Shop : public sf::Drawable {
private:
	int nrOfItem;
	int itemsCAP;
	Item** items;

	void expand();
public:
	Shop();
	virtual ~Shop();

	//Item* buyItem(void(*recieveItemFunc)(Item*));
	void buyItem(Player* buyer);

	void updateItems();
	Item* checkCollision(sf::FloatRect entityBounds);
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};