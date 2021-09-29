#pragma once

#include "Entity.h"
#include "BingoBoard.h"
enum class PlayerId {PlayerOne, PlayerTwo};
class Player : public Entity {

private:
	PlayerId playerId;
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;
	sf::Keyboard::Key bingoKey;
	sf::Keyboard::Key actionKey;

	sf::RectangleShape* gameArea;

	BingoBoard *bingoBoard;

	bool wonTheGame;

public :
	Player(PlayerId player, sf::RectangleShape *gameArea);
	virtual ~Player();
	void initBingoBoard(NumberBoard* numberBoard);

	bool hasWon();

	std::string getPlayerIdentity();

	// Inherited via Entity
	virtual void move() override;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};