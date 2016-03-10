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

	enum Directions
	{
		NORTH,//0
		SOUTH,//1
		EAST,//2
		WEST,//3
		NOTMOVING//4
	};

public:
	/*constructor. params are the time to live, the type, the position to draw them at and the rotation*/
	Particle(float ttl, int t, sf::Vector2f pos, float r);

	/*destructor*/
	~Particle();

	/*Load the correct texture based on the type*/
	void LoadTexture();

	/*Check if the time to live is up*/
	void Update();

	/*Is the particle removable?*/
	bool IsRemovable();

	/*Get what type of particle this is*/
	int GetType();
};

#endif
