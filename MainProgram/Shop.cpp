#include "Shop.h"

Shop::Shop()
	: nrOfItem(0)
{
	this->itemsCAP = 3;
	items = new Item * [this->itemsCAP]{nullptr};	


	Stone* tempStone = new Stone();
	items[this->nrOfItem++] = tempStone;
}

Shop::~Shop()
{
	for (int i = 0; i < this->nrOfItem; i++) {
		delete this->items[i];
	}
	delete[] this->items;
}


void Shop::buyItem(Player* buyer)
{

	buyer->recieveItem(items[0]);
	
}

void Shop::updateItems()
{
	for (int i = 0; i < this->nrOfItem; i++) {
		this->items[i]->move();
		if (this->items[i]->isTerminated()) {
			auto temp = this->items[i];
			this->items[i] = this->items[this->nrOfItem--];
			delete temp;
		}
	}
}

Item* Shop::checkCollision(sf::FloatRect entityBounds)
{
	Item* item = nullptr;
	for (int i = 0; i < itemsCAP && !item; i++) {
		if (items[i]) {
			if (items[i]->hitBy(entityBounds)){
				item = items[i];
			}
		}
	}
	return item;
}

void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (int i = 0; i < nrOfItem; i++) { 	
		
		target.draw(*items[i]);
		
	}
}
