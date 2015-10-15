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
	sf::String race;
	sf::String gender;
	sf::String playerClass;

	bool isRunning;

	sf::Sprite hudBackground;
	sf::Texture hudBackgroundTexture;

	Compass* compass;

public:
	Player(sf::String r, sf::String g, sf::String c);
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
	//end gets
	//start sets
	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	void setSpeed(float s) { speed = s; }
	void setIsRunning(bool r) { isRunning = r; }
	//end sets
#pragma endregion

};

#endif