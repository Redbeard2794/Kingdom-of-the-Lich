#ifndef CAMPFIRE_H
#define CAMPFIRE_H

class CampFire : public sf::Sprite
{
private:
	sf::Texture texture;
	sf::Vector2i framePosition;
	sf::Vector2i frameSize;
	sf::IntRect frame;
	int numFrames;
	float animationTime;
	sf::Clock animationClock;

	int id;
public:
	CampFire(sf::Vector2f pos, int i);
	~CampFire();
	void Update();
};

#endif
