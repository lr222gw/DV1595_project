#include "Shop.h"

Shop::Shop()
	: nrOfItem(0)
{
	this->itemsCAP = 3;
	items = new Item * [this->itemsCAP]{nullptr};	
	soldItems = new Item * [this->itemsCAP]{nullptr};


	Stone* tempStone = new Stone();
	Stone* tempStone2 = new Stone();
	Stone* tempStone3 = new Stone();
	items[this->nrOfItem++] = tempStone;
	items[this->nrOfItem++] = tempStone2;
	items[this->nrOfItem++] = tempStone3;
}

Shop::~Shop()
{
	for (int i = 0; i < this->nrOfItem; i++) {
		delete this->items[i];
	}
	for (int i = 0; i < this->nrOfSoldItem; i++) {
		delete this->soldItems[i];
	}

	delete[] this->soldItems;
	delete[] this->items;
}


std::string Shop::presentItem()
{
		
	return nrOfItem > 0 ? items[0]->present() + " " + std::to_string(items[0]->getPrice()) : "Nothing left";
}

void Shop::buyItem(Player* buyer)
{
	if (nrOfItem > 0 && buyer->getMoney() >= items[0]->getPrice()) {
		buyer->removeMoney(items[0]->getPrice());
		soldItems[nrOfSoldItem++] = items[0];
		items[0] = items[--nrOfItem];
		if (nrOfSoldItem >= soldItemsCAP) {
			//Expand
		}
		
		buyer->recieveItem(soldItems[nrOfSoldItem-1]);
	}		
}

void Shop::updateItems()
{
	for (int i = 0; i < this->nrOfSoldItem; i++) {
		this->soldItems[i]->move();
		if (this->soldItems[i]->isTerminated()) {
			auto temp = this->soldItems[i];
			this->soldItems[i] = this->soldItems[this->nrOfSoldItem--];
			delete temp;
		}
	}
}

Item* Shop::checkCollision(sf::FloatRect entityBounds)
{
	Item* item = nullptr;
	for (int i = 0; i < nrOfSoldItem && !item; i++) {
		if (soldItems[i]) {
			if (soldItems[i]->hitBy(entityBounds)){
				item = soldItems[i];
			}
		}
	}
	return item;
}

void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (int i = 0; i < nrOfSoldItem; i++) {
		
		target.draw(*soldItems[i]);
		
	}
}
