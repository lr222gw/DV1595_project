#include "BingoBoard.h"

bool BingoBoard::checkBingo()
{
	bool gotBingo = false;

	// Check each Row
	for (int i = 0; i < 5 && !gotBingo; i++) {
		int j = 0;
		while (j < 5 && this->numberBoardsTiles[(i * 5) + j]->isSoiled()) {
			j++;
		}
		if (j == 5) {
			gotBingo = true;
		}
		else {
			j = 0;
		}
	}

	// Check each Column
	for (int i = 0; i < 5 && !gotBingo; i++) {
		int j = 0;
		while (j < 5 && this->numberBoardsTiles[((j * 5)) + i]->isSoiled()) {
			j++;
		}
		if (j == 5) {
			gotBingo = true;
		}
		else {
			j = 0;
		}
	}

	// Check first Diagonal
	int i = 0;
	while (i <= 24 && this->numberBoardsTiles[i]->isSoiled()) {
		i += 6;
	}
	gotBingo = i == 30 ? true : gotBingo;

	// Check second Diagonal
	i = 4;
	while (i <= 20 && this->numberBoardsTiles[i]->isSoiled()) {
		i += 4;
	}
	gotBingo = i == 24 ? true : gotBingo;


	return gotBingo;
}

bool BingoBoard::updateSpecialTile(int currentIndex, bool isSoiled )
{
	auto temp = numberBoardsTiles[currentIndex];
	bool wasSpecial = false;

	for (int j = 0; j < 5; j++) {
		if (specialTiles[j] == temp) {
			wasSpecial = true;
			if (isSoiled) {
				squares[currentIndex].setFillColor(sf::Color((sf::Uint8)130, (sf::Uint8)120, (sf::Uint8)0)); 
			}
			else {
				squares[currentIndex].setFillColor(sf::Color((sf::Uint8)200, (sf::Uint8)180, (sf::Uint8)30));

			}
		}
	}
	return wasSpecial;
}

bool BingoBoard::checkSpecialTiles()
{
	bool hadUnusedSpecialTile = false;
	for (int i = 0; i < 5; i++) {

		if (specialTiles[i] && specialTiles[i]->isSoiled()) {
			hadUnusedSpecialTile = true;
			specialTiles[i] = nullptr;
		}
	}
	return hadUnusedSpecialTile;
}

BingoBoard::BingoBoard(NumberBoard* numberBoard, sf::Vector2f drawPos)
{

	this->drawPos = drawPos;
	this->bingoImage_texture.loadFromFile("../Images/bingo.png");
	this->bingoImage_sprite.setTexture(bingoImage_texture);
	this->bingoImage_sprite.setScale(.2,.2f);
	this->bingoImage_sprite.setPosition(drawPos.x, drawPos.y + 150.f);
	this->bingoImage_sprite.setColor(sf::Color(0, 0, 0, 0));
	
	Tile* tempArr[5*5]{ 0 };
	Tile* specialTilesArr[5 * 5];
	Tile* specialTilesArr_temp[5 * 5];
	for (int i = 0; i < 5 * 5;i++) {
		tempArr[i] = numberBoard->getTile(i);
		specialTilesArr[i] = tempArr[i];
	}

	/// generate SpecialTiles
	for (int i = 0; i < 5 * 5; i++) {
		int index = rand() % ((5 * 5 ) - i);
		Tile* temp = specialTilesArr[index];
		specialTilesArr[index] = specialTilesArr[(5 * 5 - 1) - i];
		specialTilesArr[(5 * 5 - 1) - i] = nullptr; //nullptr to mark it's used...

		specialTilesArr_temp[i] = temp;
	}

	specialTiles[0] = specialTilesArr_temp[4];
	specialTiles[1] = specialTilesArr_temp[5];
	specialTiles[2] = specialTilesArr_temp[6];
	specialTiles[3] = specialTilesArr_temp[7];
	specialTiles[4] = specialTilesArr_temp[8];
	

	/// Setup bingo board
	this->squareSize = 30.f;
	float margin = 1.f;
	this->bingoBoardSize = sf::Vector2f(squareSize * 5.f + 5.f, squareSize * 5.f + 5.f );
	bingoFont.loadFromFile("../Images/fonts/BingoReky.ttf");
	for (int i = 0; i < 5 * 5; i++) {

		/// Pick random Tile from theNumberBoard, for each tile of the bingo board
		int index = rand() % ((5*5) - i );
		this->numberBoardsTiles[i] = tempArr[index];
		Tile* temp = tempArr[((5 * 5 - 1) - i)];
		tempArr[index] = temp;

		this->texts[i].setString(std::to_string(this->numberBoardsTiles[i]->getValue()));

		bool wasSpecial = false;

		if (!wasSpecial) {
		
			squares[i].setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)150, (sf::Uint8)45));
		}
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


		bool soiled = numberBoardsTiles[i]->isSoiled();
		if (soiled) {
			if (!updateSpecialTile(i, soiled)) {

				squares[i].setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)100, (sf::Uint8)25));
			}
		}
		else if (!soiled) {
			if (!updateSpecialTile(i, soiled)) {

				squares[i].setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)150, (sf::Uint8)45));
			}
		}
	}	

	if (checkBingo()) 
	{
		this->bingoImage_sprite.setColor(sf::Color(255, 255, 255, 255));
	}
}

sf::Vector2f BingoBoard::getBingoBoardSize()
{
	return this->bingoBoardSize;
}

void BingoBoard::setPosition(sf::Vector2f pos)
{
	this->drawPos = pos;
	for (int i = 0; i < 5 * 5; i++) {

		float posX = drawPos.x + squareSize * (i % 5);
		float posY = drawPos.y + squareSize * ((i / 5));
		squares[i].setPosition(posX, posY);
		texts[i].setPosition(posX + squareSize / 6.f, posY + squareSize / 6.f);
	}
}

void BingoBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < 5 * 5; i++) {
		target.draw(squares[i]);
		target.draw(texts[i]);
	}
	target.draw(bingoImage_sprite);
}
