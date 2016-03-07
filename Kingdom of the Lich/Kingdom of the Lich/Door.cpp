#include "stdafx.h"
#include "Door.h"

Door::Door(int t, sf::Vector2f pos, bool o, int a, int i) : type(t), open(o), area(a), id(i)
{
	if (type == TrapDoor)
	{
		texture.loadFromFile("Assets/Tiles/sewerLevel/entrances and exits/entranceHatch50x50.png");
	}
	else if (type == StoneDoorway)
	{
		texture.loadFromFile("Assets/Tiles/sewerLevel/entrances and exits/entranceExitWall50x50.png");
	}
	else if (type == HouseDoorOne)
	{
		texture.loadFromFile("Assets/Tiles/indoorTiles/indoor assets/newHouseDoor.png");
		scale(1.3, 1.4);
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

int Door::GetArea()
{
	return area;
}
