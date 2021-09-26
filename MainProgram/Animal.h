#pragma once
#include "Entity.h"
#include <stdlib.h>
#include "NumberBoard.h"

enum class Direction { Left, Right, Up, Down };
class Animal : public Entity {
private:
	sf::FloatRect gameArea;
	bool relieavingWaste;

	int maxTimeBetweenCrap;
	int minTimeBetweenCrap;
		
	/// Timer stuff
	int updateTime;
	int timeCounter;
	int crapTimeCount = 0;
	int crapIntervalCount = 0;
	int crapTime = 2;
	int crapInterval;
protected:
	NumberBoard* theNumberBoard;
	Direction currentDirection;
	
public:

	Animal(NumberBoard* theNumberBoard,sf::FloatRect gameArea, float speed, int maxTimeBetweenCrap, int minTimeBetweenCrap);
	sf::FloatRect	getGameArea();
	Direction		getCurrentDirection();
	void			setCurrentDirection(Direction dir);

	bool			isRelieavingWaste();
	void			setRelieavingWaste(bool status);	
	void			resetCrapTimeInterval();
	void			setCrapTimeInterval(int minTimeBetweenCrap, int maxTimeBetweenCrap);

	int		getCrapIntervalCount() const;
	int		getCrapTimeCount() const;

	void updateTimeCounter();

	virtual void crapOnTile() = 0;
	// Inherited via Entity
	virtual void move() override = 0;

};