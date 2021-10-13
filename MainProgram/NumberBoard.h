#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Poo.h"

class Animal;
class NumberBoard : public sf::Drawable {
private:
	Tile* tiles[5*5];
	sf::RectangleShape squares[5*5];
	sf::Text texts[5*5];
	sf::RectangleShape background;
	sf::Font bingoFont;

	int nrOfPoos;
	int pooCapacity;
	Poo** poos;

	void expandPooArray();

public:
	NumberBoard(sf::FloatRect gameArea);
	~NumberBoard();

	bool checkBingo();
	void cleanTile(int tileValue);
	void markTileAsCrapped(sf::FloatRect marking);
	void unmarkTileAsCrapped(sf::FloatRect marking);

	Poo* collidedWithPoo(Entity& animal);
	Tile* getTile(int index);
	Poo** getPoos() const;
	const int getNrOfPoos() const;

	void recievePoo(Poo* poo);

	sf::FloatRect getBounds() const;


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};