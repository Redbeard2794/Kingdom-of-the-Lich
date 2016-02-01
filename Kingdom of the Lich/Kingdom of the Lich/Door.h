#ifndef DOOR_H
#define DOOR_H

class Door : public sf::Sprite
{
private:
	enum DoorType
	{
		TrapDoor,
		Doorway
	};
	int type;
	sf::Texture texture;
	bool open;

public:
	Door(int t, sf::Vector2f pos, bool o);

	~Door();

	bool IsPlayerInDoorway(sf::Vector2f playerPos);

	bool IsOpen();

	void SetOpen(bool o);
};

#endif