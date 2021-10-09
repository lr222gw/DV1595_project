#pragma once
#include <stdlib.h>

class Tile {
private:
	static int valueArray[5 * 5];

	int id;
	int value;
	bool soiled;

	static int getUniqueID();
	static int getUniqueValue(int id);
public:
	Tile();
	static void resetAllStaticData();
	int getId();
	int getValue();
	bool isSoiled();
	void soilTile();
	void unsoilTile();
};
