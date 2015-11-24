#ifndef PLAYER_H
#define PLAYER_H
#include "Compass.h"
#include "Npc.h"
class Player : public sf::Drawable, public sf::Transformable
{
private:
	sf::Vector2f velocity;
	sf::Sprite mSprite;

	sf::Texture mTexture;

	float speed;

	float health;

	sf::Vector2f direction;

	//character info
	int race;
	int gender;
	int playerClass;

	bool isRunning;

	sf::Font font;

	enum Race
	{
		HUMAN,
		ELF,
		Dwarf
	};

	enum Gender
	{
		MALE,
		FEMALE
	};

	enum Class
	{
		ARCHER,
		KNIGHT,
		SPELLBLADE
	};

	enum Directions
	{
		NORTH,//0
		SOUTH,//1
		EAST,//2
		WEST,//3
		NOTMOVING//4
	};
	int currentDirection;
	int previousDirection;
	int lockedDirection;

public:
	//constructor(param is a font)
	Player(sf::Font f);
	//destructor
	~Player();

	void Update();//sf::Vector2f objectivePos, std::string currentQuestName);

	//Set the player's texture based on their chosen race
	void setTextures();

	/*Move the player in the direction they are travelling in
	Don't allow them to move if that direction is locked due to collision with another object*/
	void Move(int newDir);

	/*Check to see if the player is colliding with a chest*/
	bool CollisionWithChest(sf::Sprite chestSprite);

	/*Check to see if the player is colliding with an npc*/
	bool CollisionWithNpc(Npc* npc);

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;

	/*Draw the player*/
	void Player::draw(sf::RenderTarget& window);

#pragma region Properties
	//start gets
	sf::Vector2f getVelocity() { return velocity; }
	sf::Sprite getSprite() { return mSprite; }
	float getSpeed() { return speed; }
	float getHealth() { return health; }
	bool getIsRunning() { return isRunning; }

	int getRace() { return race; }
	int getGender() { return gender; }
	int getClass() { return playerClass; }
	int getCurrentDirection() { return currentDirection; }

	int getPreviousDirection() { return previousDirection; }
	//end gets
	//start sets
	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	void setSpeed(float s) { speed = s; }
	void setIsRunning(bool r) { isRunning = r; }

	void setRace(int r) { race = r; }
	void setGender(int g) { gender = g; }
	void setClass(int c) { playerClass = c; }

	void setCurrentDirection(int currDir) { currentDirection = currDir; }
	void setPreviousDirection(int pDir) { previousDirection = pDir; }
	//end sets
#pragma endregion

};

#endif