#ifndef PARTICLE_H
#define PARTICLE_H

class Particle : public sf::Sprite
{
protected:
	float timeToLive;

	sf::Clock lifeClock;

	sf::Texture texture;

	bool removable;

public:
	/*constructor. params are the time to live and the position to draw them at*/
	Particle(float ttl, sf::Vector2f pos);

	/*destructor*/
	~Particle();

	/*Load the correct texture based on the type*/
	virtual void LoadTexture();

	/*Check if the time to live is up*/
	virtual void Update();

	/*Is the particle removable?*/
	bool IsRemovable();
};

#endif
