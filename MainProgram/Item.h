#pragma once
#include "Entity.h"

class Player;
class Item : public Entity {

private:
	bool shouldTerminate;
	int price;
	float defaultScale;
	float thumbnailScale;
	Player* owner;
protected:
	virtual void resetItemSpecifics() = 0;
public:
	Item(float speed, int price, float defaultScale = 1.f, float thumbnailScale = 1.f);
	bool isTerminated();
	void terminate();
	int getPrice() const;
	void setDefaultScale();
	void setThumbnailScale();

	void setOwner(Player* playerPtr);
	Player* getOwner() const;

	void resetItem();
	
	virtual std::string getName() = 0;
	virtual bool use(Player* playerPtr) = 0;
	virtual void collided(Entity* collidedWith) = 0;


};
