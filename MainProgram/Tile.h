#pragma once
#include <stdlib.h>

class Tile {

	int id;
	int value;
	bool soiled;

	static int getUniqueID();
	static int getUniqueValue(int id);
public:
	Tile();
	int getId();
	int getValue();
	bool isSoiled();
	void soilTile();
	void unsoilTile();
};