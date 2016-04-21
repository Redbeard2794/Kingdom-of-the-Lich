#include "stdafx.h"
#include "Door.h"

/*constructor. params: type, position, whether its open or not, area it leads to, id*/
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
		texture.loadFromFile("Assets/Tiles/houseEntranceC.png");
		scale(0.5, 1);
	}
	else if (type == HouseExitDoor)
	{
		texture.loadFromFile("Assets/Tiles/indoorTiles/indoor assets/indoorAssets1/doors/door50x50.png");
	}

	setTexture(texture);
	setPosition(pos);
}

//destructor
Door::~Door()
{

}

//check if the player is standing in the doorway
bool Door::IsPlayerInDoorway(sf::Vector2f playerPos)
{
	if (getGlobalBounds().contains(playerPos))
		return true;
	else return false;
}

//is the door open
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

int Door::GetId()
{
	return id;
}
