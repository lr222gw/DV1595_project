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

	buyingSound.loadFromFile("../Sounds/buy_item.wav");
	soundPlayer.setBuffer(buyingSound);

	shopBox_texture.loadFromFile("../Images/shop_box.png");
	shopBox.setTexture(&shopBox_texture, true);
	shopBox.setSize(sf::Vector2f(400.f, 65.f));
	
	shopFont.loadFromFile("../Images/fonts/CatShop.ttf");
	
	shopText.setFont(shopFont);
	shopText.setCharacterSize(20);
	shopText.setFillColor(sf::Color::Black);
	shopText.setString("The Item Shop");
	shopText.setStyle(sf::Text::Underlined);
	shopNextItemNameText.setFont(shopFont);
	shopNextItemNameText.setCharacterSize(15);
	shopNextItemNameText.setFillColor(sf::Color::Black);
	
	shopNextItemPriceText.setFont(shopFont);
	shopNextItemPriceText.setCharacterSize(32);
	shopNextItemPriceText.setFillColor(sf::Color::Color(35,145,35));	
	shopNextItemPriceText.setStyle(sf::Text::Bold );
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
	shopBox.setPosition(
		this->gamePtr->getWindowSize().x / 2.f - shopBox.getSize().x / 2.f, 
		this->gamePtr->getWindowSize().y - shopBox.getSize().y
	);
	float margin = 12.f;
	shopText.setPosition(
		margin + this->gamePtr->getWindowSize().x / 2.f - shopBox.getSize().x / 2.f, 
		margin + this->gamePtr->getWindowSize().y - shopBox.getSize().y
	);
	
	shopNextItemNameText.setPosition(
		margin + this->gamePtr->getWindowSize().x / 2.f - shopBox.getSize().x / 2.f, 
		margin*3 + this->gamePtr->getWindowSize().y - shopBox.getSize().y
	);
	shopNextItemPriceText.setPosition(
		margin + this->gamePtr->getWindowSize().x / 2.f + shopBox.getSize().x / 15.f,
		margin  + this->gamePtr->getWindowSize().y - shopBox.getSize().y
	);

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


std::string Shop::presentItemName()
{
		
	return nrOfItem > 0 ? items[0]->getName()  : "Nothing left";
}

std::string Shop::presentItemPrice()
{
	return nrOfItem > 0 ? std::to_string(items[0]->getPrice()) : "";
}

void Shop::buyItem(Player* buyer)
{
	if (nrOfItem > 0 && buyer->getMoney() >= items[0]->getPrice()) {
		soundPlayer.play();
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
		items[0]->setPosition(this->gamePtr->getWindowSize().x / 2.f + 135.f , this->gamePtr->getWindowSize().y - 40.f );
		items[0]->setThumbnailScale();
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

	shopNextItemNameText.setString("Buy Item: " + this->presentItemName());
	shopNextItemPriceText.setString( "$" + this->presentItemPrice() );
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
		
	target.draw(shopBox);
	if (nrOfItem > 0 ) {
		target.draw(*items[0]);
		target.draw(shopNextItemNameText);
		target.draw(shopNextItemPriceText);
	}
	target.draw(shopText);
	
}
