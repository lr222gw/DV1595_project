#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "NumberBoard.h"
#include "Tile.h"

enum class SpecialTile {
	special_x1,
	special_x2,
	special_x3,
	no_special
};
class BingoBoard : public sf::Drawable {
private:
	
	sf::RectangleShape squares[5 * 5];
	sf::Text texts[5 * 5];
	sf::Font bingoFont;
	
	sf::Texture bingoImage_texture;
	sf::Sprite bingoImage_sprite;

	Tile* numberBoardsTiles[5 * 5]; 
	Tile* specialTiles_x1[1];
	Tile* specialTiles_x3[3];
	Tile* specialTiles_x5[5];

	bool checkBingo();
	SpecialTile checkSpecialTiles();

public:
	BingoBoard(NumberBoard* numberBoard, sf::Vector2f drawPos);

	void updateBingoBoard();
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
