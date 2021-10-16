#include "Shop.h"
#include "Game.h"

Shop::Shop()
	: nrOfItem(0), gamePtr(nullptr), nrOfSoldItem(0), nrOfTerminatedItems(0)
{
	this->itemsCAP = 12;
	this->soldItemsCAP = 12;
	this->terminatedItemsCAP = 12;
	items = new Item * [this->itemsCAP]{ nullptr };
	soldItems = new Item * [this->soldItemsCAP]{ nullptr };
	terminatedItems = new Item * [this->terminatedItemsCAP]{ nullptr };
}

Shop::~Shop()
{
	for (int i = 0; i < this->nrOfItem; i++) {
		delete this->items[i];
	}
	for (int i = 0; i < this->nrOfSoldItem; i++) {
		delete this->soldItems[i];
	}
	for (int i = 0; i < this->nrOfTerminatedItems; i++) {
		delete this->terminatedItems[i];
	}
	
	delete[] this->items;
	delete[] this->soldItems;
	delete[] this->terminatedItems;
}

void Shop::restockItems()
{
	for (int i = 0; nrOfTerminatedItems != 0 ; i++) {
		terminatedItems[i]->resetItem();
		items[nrOfItem++] = terminatedItems[i];
		
		terminatedItems[i] = terminatedItems[--nrOfTerminatedItems];
		terminatedItems[nrOfTerminatedItems] = nullptr;
	}
}

void Shop::setGamePtr(Game* gamePtr)
{
	this->gamePtr = gamePtr;
}

void Shop::initShop()
{
	items[this->nrOfItem++] = new Stone(gamePtr);
	items[this->nrOfItem++] = new Stone(gamePtr);
	items[this->nrOfItem++] = new Wheat(gamePtr);
	items[this->nrOfItem++] = new DungBeetle(gamePtr);
	items[this->nrOfItem++] = new Stone(gamePtr);
	items[this->nrOfItem++] = new Wheat(gamePtr);
	items[this->nrOfItem++] = new Stone(gamePtr);
	items[this->nrOfItem++] = new Wheat(gamePtr);
	items[this->nrOfItem++] = new DungBeetle(gamePtr);
	items[this->nrOfItem++] = new Stone(gamePtr);
	items[this->nrOfItem++] = new Stone(gamePtr);
	items[this->nrOfItem++] = new Wheat(gamePtr);
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
		items[nrOfItem] = nullptr;

		if (nrOfSoldItem >= soldItemsCAP) {
			//Expand
			this->soldItemsCAP += 10;
			Item** temp = new Item * [this->soldItemsCAP]{ nullptr };
			for (int i = 0; i < nrOfSoldItem; i++) {
				temp[i] = this->soldItems[i];
			}
			delete[] this->soldItems;
			this->soldItems = temp;
		}

		if (nrOfItem == 0) {
			restockItems();
		}
		
		buyer->recieveItem(soldItems[nrOfSoldItem-1]);
	}		
}

void Shop::updateItems()
{
	for (int i = 0; i < this->nrOfSoldItem; i++) {
		if (this->soldItems[i]) {			
			this->soldItems[i]->update();
			if (this->soldItems[i]->isTerminated()) {
				auto temp = this->soldItems[i];
				this->soldItems[i] = this->soldItems[--this->nrOfSoldItem];
				
				terminatedItems[nrOfTerminatedItems++] = temp;
				restockItems();
			}
		}
	}
}

Item* Shop::checkCollision(sf::FloatRect entityBounds) const
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
		
		if (soldItems[i]) {
			target.draw(*soldItems[i]);
		}
		
	}
}
