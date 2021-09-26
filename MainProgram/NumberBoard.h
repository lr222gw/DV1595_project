#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class NumberBoard : public sf::Drawable {
private:
	Tile* tiles[5*5];
	sf::RectangleShape squares[5*5];
	sf::Text texts[5*5];
	sf::RectangleShape background;
	sf::Font bingoFont;
public:
	NumberBoard(sf::FloatRect gameArea);
	~NumberBoard();

	bool checkBingo();
	void cleanTile();
	void markTileAsCrapped(sf::FloatRect marking);

	sf::FloatRect getBounds() const;


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};