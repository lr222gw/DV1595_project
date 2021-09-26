#include "Tile.h"
int Tile::getUniqueID()
{
	static int ID = 0;
	
	return ID++;
}
int Tile::getUniqueValue(int id)
{
	static int valueArray[5 * 5]{0};
	static bool first = true;
	// Put unique random values from 0 to 24 in a array
	if (first) {		
		//Use a temporary array with values from 0 to 24 in sorted order
		int tempArr[5 * 5];		
		for (int i = 0; i < 5 * 5; i++) {
			tempArr[i] = i;
		}
		for (int i = 0; i < 5 * 5; i++) {
			// for each iteration, pick one of the values from the sorted array
			// then remove that value by replacing it with whatever value currently is 
			// in the end of that array.
			int randomIndex = rand() % (5*5 - i); // Ignores all values that already has been picked
			valueArray[i] = tempArr[randomIndex];
			int temp = tempArr[((5 * 5 -1) - i)];
			tempArr[randomIndex] = temp;
		}
		first = false;
	}

	return valueArray[id];
}
Tile::Tile()
{
	this->id = getUniqueID();
	this->soiled = false;
	this->value = getUniqueValue(this->id);
}

int Tile::getId()
{
	return this->id;
}

int Tile::getValue()
{
	return this->value;
}

bool Tile::isSoiled()
{
	return soiled;
}

void Tile::soilTile()
{
	this->soiled = true;
}

void Tile::unsoilTile()
{
	this->soiled = false;
}
