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

	NumberBoard* theNumberBoard;
	
	sf::Texture bingoImage_texture;
	sf::Sprite bingoImage_sprite;

	Tile* numberBoardsTiles[5 * 5]; 
	Tile* specialTiles[5];

	bool updateSpecialTile(int currentIndex, bool isSoiled);

	Tile* findCommonBingoTile();

	float squareSize;
	sf::Vector2f drawPos;
	sf::Vector2f bingoBoardSize;

public:
	BingoBoard(NumberBoard* numberBoard, sf::Vector2f drawPos);

	bool checkBingo() const;
	void sabbotageBingo();
	bool checkSpecialTiles();	
	void updateBingoBoard();
	sf::Vector2f getBingoBoardSize();
	void setPosition(sf::Vector2f pos);
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
