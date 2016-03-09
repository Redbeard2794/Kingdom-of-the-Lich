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
	int type;
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
	Door(int t, sf::Vector2f pos, bool o, int a, int i);

	~Door();

	bool IsPlayerInDoorway(sf::Vector2f playerPos);

	bool IsOpen();

	void SetOpen(bool o);

	int GetArea();
};

#endif