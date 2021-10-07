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

	bool updateSpecialTile(int currentIndex, bool isSoiled);

	SpecialTile checkSpecialTiles();	

	float squareSize;
	sf::Vector2f drawPos;
	sf::Vector2f bingoBoardSize;

public:
	BingoBoard(NumberBoard* numberBoard, sf::Vector2f drawPos);

	bool checkBingo();
	void updateBingoBoard();
	sf::Vector2f getBingoBoardSize();
	void setPosition(sf::Vector2f pos);
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
