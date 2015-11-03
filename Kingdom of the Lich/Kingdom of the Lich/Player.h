#ifndef PLAYER_H
#define PLAYER_H
#include "Compass.h"

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
	sf::Sprite hudBackground;
	sf::Texture hudBackgroundTexture;
	sf::Text currentQuestText;

	Compass* compass;
	enum Race
	{
		HUMAN,
		ELF,
		BEASTMAN
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
	int lockedDirection;

public:
	Player(sf::Font f);
	~Player();

	void Update(sf::Vector2f objectivePos, std::string currentQuestName);

	//void boundary();
	void setTextures();

	void Move(int newDir);

	bool CollisionWithChest(sf::Sprite chestSprite);//, Inventory* inv);

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
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
	//end gets
	//start sets
	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	void setSpeed(float s) { speed = s; }
	void setIsRunning(bool r) { isRunning = r; }

	void setRace(int r) { race = r; }
	void setGender(int g) { gender = g; }
	void setClass(int c) { playerClass = c; }

	void setCurrentDirection(int currDir) { currentDirection = currDir; }
	//end sets
#pragma endregion

};

#endif