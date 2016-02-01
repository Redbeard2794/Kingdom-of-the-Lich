#include "stdafx.h"
#include "Door.h"

Door::Door(int t, sf::Vector2f pos, bool o) : type(t), open(o)
{
	if (type == TrapDoor)
	{
		texture.loadFromFile("Assets/Tiles/sewerLevel/entrances and exits/entranceHatch50x50.png");
	}
	else if (type == Doorway)
	{
		texture.loadFromFile("Assets/Tiles/sewerLevel/entrances and exits/entranceExitWall50x50.png");
	}

	setTexture(texture);
	setPosition(pos);
}

Door::~Door()
{

}

bool Door::IsPlayerInDoorway(sf::Vector2f playerPos)
{
	if (getGlobalBounds().contains(playerPos))
		return true;
	else return false;
}

bool Door::IsOpen()
{
	return open;
}

void Door::SetOpen(bool o)
{
	open = o;
}
