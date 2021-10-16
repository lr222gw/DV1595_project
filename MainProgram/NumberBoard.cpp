#include "NumberBoard.h"
#include "Animal.h"

void NumberBoard::expandPooArray()
{
	pooCapacity += 5*5;
	Poo** temp = new Poo * [pooCapacity];

	for (int i = 0; i < nrOfPoos; i++ ) {
		temp[i] = this->poos[i];
	}
	delete[] this->poos;

	this->poos = temp;
}

NumberBoard::NumberBoard(sf::FloatRect gameArea)
{
	srand(time(NULL));
	float squareSize = gameArea.width / 10.f;
	float margin = 1.f;

	background.setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)80, (sf::Uint8)5, (sf::Uint8)40));
	background.setSize(sf::Vector2f(squareSize* 5.f + (5.f * margin), squareSize * 5.f + (5.f * margin)));
	background.setPosition(gameArea.left + (gameArea.width / 4.f) - 2.5f, (gameArea.height / 6.f) - 2.5f);

	bingoFont.loadFromFile("../Images/fonts/BingoReky.ttf");
	Tile::resetAllStaticData();
	for (int i = 0; i < 5 * 5; i++) {
		this->tiles[i] = new Tile();
		squares[i].setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)150, (sf::Uint8)45, (sf::Uint8)105));
		squares[i].setSize(sf::Vector2f(squareSize- margin, squareSize - margin));
		float posX = gameArea.left + (gameArea.width / 4.f) + squareSize * (i % 5);
		float posY = (gameArea.height / 6.f) + squareSize * ((i / 5));
		squares[i].setPosition(posX, posY);
		texts[i].setFont(bingoFont);
		texts[i].setCharacterSize(50);
		texts[i].setPosition(posX + squareSize/6.f, posY + squareSize / 6.f);
		texts[i].setString(std::to_string(this->tiles[i]->getValue()));
	}
	nrOfPoos = 0;
	//pooCapacity = 5 * 5;
	pooCapacity = 2;
	poos = new Poo * [pooCapacity];
}

NumberBoard::~NumberBoard()
{
	for (int i = 0; i < 5 * 5; i++) {
		delete tiles[i];
	}
	for (int i = 0; i < nrOfPoos; i++) {
		delete poos[i];
	}
	delete[] poos;
}

void NumberBoard::cleanTile(int tileID)
{
	unmarkTileAsCrapped(squares[tileID].getGlobalBounds());
}

void NumberBoard::markTileAsCrapped(sf::FloatRect marking)
{
	for (int i = 0; i < 5 * 5 ; i++) {
		if (squares[i].getGlobalBounds().intersects(marking) && !tiles[i]->isSoiled()) {
			squares[i].setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)100, (sf::Uint8)25, (sf::Uint8)105));
			tiles[i]->soilTile();
		}
	}
}

void NumberBoard::unmarkTileAsCrapped(sf::FloatRect marking)
{	
	for (int i = 0; i < 5 * 5; i++) {
		if (squares[i].getGlobalBounds().intersects(marking) && tiles[i]->isSoiled()) {			
			squares[i].setFillColor(sf::Color((sf::Uint8)0, (sf::Uint8)150, (sf::Uint8)45, (sf::Uint8)105));
			tiles[i]->unsoilTile();
		}
	}
}

Poo* NumberBoard::collidedWithPoo(Entity& entity)
{
	Poo* collidedPoo = nullptr;

	for (int i = 0; i < nrOfPoos && !collidedPoo; i++) {
		if (entity.hitBy(poos[i]->getBounds())) {
			collidedPoo = poos[i];
		}
	}
	return collidedPoo;	
}

Tile* NumberBoard::getTile(int index)
{
	return tiles[index];
}

Poo** NumberBoard::getPoos() const
{
	return this->poos;
}

const int NumberBoard::getNrOfPoos() const
{
	return nrOfPoos;
}

void NumberBoard::recievePoo(Poo* poo)
{
	if (nrOfPoos == pooCapacity) 
	{
		expandPooArray();
	}
	
	this->poos[nrOfPoos++] = poo;
	
}

sf::FloatRect NumberBoard::getBounds() const
{
	return this->background.getGlobalBounds();
}

void NumberBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background);
	for (int i = 0; i < 5 * 5; i++) {
		target.draw(squares[i]);
		target.draw(texts[i]);
	}
	for (int i = 0; i < nrOfPoos; i++) {
		target.draw(*poos[i]);
	}
}
