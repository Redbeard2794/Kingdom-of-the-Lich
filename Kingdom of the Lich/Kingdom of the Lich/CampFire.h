#ifndef CAMPFIRE_H
#define CAMPFIRE_H

class CampFire : public sf::Sprite
{
private:
	sf::Texture texture;//texture

	//animation stuff. frame properties etc
	sf::Vector2i framePosition;
	sf::Vector2i frameSize;
	sf::IntRect frame;
	int numFrames;
	float animationTime;
	sf::Clock animationClock;

	int id;
public:
	/*constructor. params: position and id*/
	CampFire(sf::Vector2f pos, int i);

	//destructor
	~CampFire();

	//animate the fire
	void Update();
};

#endif
