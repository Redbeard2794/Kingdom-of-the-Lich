#ifndef PLAYER_H
#define PLAYER_H

class Player : public sf::Drawable, public sf::Transformable
{
private:
	sf::Vector2f velocity;
	sf::Sprite mSprite;

	sf::Texture mTexture;

	float speed;

	float health;

	sf::Vector2f direction;

public:
	Player();
	~Player();

	void Update();

	//void boundary();

	void Move();

	void draw(sf::RenderTarget& window, sf::RenderStates state) const;
	void Player::draw(sf::RenderTarget& window);

#pragma region Properties
	//start gets
	sf::Vector2f getVelocity() { return velocity; }
	sf::Sprite getSprite() { return mSprite; }
	float getSpeed() { return speed; }
	float getHealth() { return health; }
	//end gets
	//start sets
	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	void setSpeed(float s) { speed = s; }
	//end sets
#pragma endregion

};

#endif