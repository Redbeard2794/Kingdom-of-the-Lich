#ifndef PARTICLE_H
#define PARTICLE_H

class Particle : public sf::Sprite
{
private:
	float timeToLive;

	sf::Clock lifeClock;

	enum Types
	{
		LeftFootPrint,
		RightFootPrint,
		Blood
	};
	int type;

	sf::Texture texture;

	bool removable;

public:
	/*constructor. params are the time to live, the type and the position to draw them at*/
	Particle(float ttl, int t, sf::Vector2f pos);

	/*destructor*/
	~Particle();

	/*Load the correct texture based on the type*/
	void LoadTexture();

	/*Check if the time to live is up*/
	void Update();

	/*Is the particle removable?*/
	bool IsRemovable();
};

#endif
