#ifndef DOOR_H
#define DOOR_H

class Door : public sf::Sprite
{
private:
	enum DoorType
	{
		TrapDoor,
		StoneDoorway,
		HouseDoorOne,
		HouseExitDoor
	};
	int type;//deciding sprite

	sf::Texture texture;
	bool open;

	enum Areas
	{
		TUTORIAL,
		SEWER,
		GENERALSTORE1,
		House1,
		House2,
		TheDrunkenDragonInn
	};
	int area;

	int id;

public:
	/*constructor. params: type, position, whether its open or not, area it leads to, id*/
	Door(int t, sf::Vector2f pos, bool o, int a, int i);

	//destructor
	~Door();

	//check if the player is standing in the doorway
	bool IsPlayerInDoorway(sf::Vector2f playerPos);

	//is the door open
	bool IsOpen();

	void SetOpen(bool o);

	int GetArea();

	int GetId();
};

#endif