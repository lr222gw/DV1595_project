#include "BingoBoard.h"

BingoBoard::BingoBoard(NumberBoard* numberBoard, sf::Vector2f drawPos)
	
{
	
	Tile* tempArr[5*5]{ 0 };
	for (int i = 0; i < 5 * 5;i++) {
		tempArr[i] = numberBoard->getTile(i);
	}
	float squareSize = 30.f;
	float margin = 1.f;
	bingoFont.loadFromFile("../Images/fonts/BingoReky.ttf");
	for (int i = 0; i < 5 * 5; i++) {

		/// Pick random Tile from theNumberBoard, for each tile of the bingo board
		int index = rand() % ((5*5) - i );
		this->numberBoardsTiles[i] = tempArr[index];
		Tile* temp = tempArr[((5 * 5 - 1) - i)];
		tempArr[index] = temp;

		this->texts[i].setString(std::to_string(this->numberBoardsTiles[i]->getValue()));

		squares[i].setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)150, (sf::Uint8)45));
		squares[i].setSize(sf::Vector2f(squareSize - margin, squareSize - margin));
		float posX = drawPos.x + squareSize * (i % 5);
		float posY = drawPos.y + squareSize * ((i / 5));
		squares[i].setPosition(posX, posY);
		texts[i].setFont(bingoFont);
		texts[i].setCharacterSize(20);
		texts[i].setPosition(posX + squareSize / 6.f, posY + squareSize / 6.f);
	}
}

void BingoBoard::updateBingoBoard()
{
	for (int i = 0; i < 5 * 5; i++) {
		if (numberBoardsTiles[i]->isSoiled()) {
			squares[i].setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)100, (sf::Uint8)25));
		}
	}
}

void BingoBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < 5 * 5; i++) {
		target.draw(squares[i]);
		target.draw(texts[i]);
	}
}
