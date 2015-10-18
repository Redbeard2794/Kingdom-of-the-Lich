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

	sf::Sprite hudBackground;
	sf::Texture hudBackgroundTexture;

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


public:
	Player();
	~Player();

	void Update();

	//void boundary();

	void Move(sf::Vector2f direction);

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

	//end gets
	//start sets
	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	void setSpeed(float s) { speed = s; }
	void setIsRunning(bool r) { isRunning = r; }

	void setRace(int r) { race = r; }
	void setGender(int g) { gender = g; }
	void setClass(int c) { playerClass = c; }

	//end sets
#pragma endregion

};

#endif