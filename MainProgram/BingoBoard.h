#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "NumberBoard.h"
#include "Tile.h"

class BingoBoard : public sf::Drawable {
private:

	sf::RectangleShape squares[5 * 5];
	sf::Text texts[5 * 5];
	sf::Font bingoFont;

	Tile* numberBoardsTiles[5 * 5]; 
	Tile* specialTiles_x1[1];
	Tile* specialTiles_x3[3];
	Tile* specialTiles_x5[5];

public:
	BingoBoard(NumberBoard* numberBoard, sf::Vector2f drawPos);

	void updateBingoBoard();
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
