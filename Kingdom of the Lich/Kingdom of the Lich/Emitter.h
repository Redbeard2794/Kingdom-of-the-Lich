#ifndef EMITTER_H
#define EMITTER_H

#include "Particle.h"

class Emitter : public sf::Sprite
{
private:
	std::vector<Particle*> particles;

	int particleType;

	int numParticlesPerSecond;//the number of particles to spaw each second

	sf::Clock spawnClock;

	enum Directions
	{
		NORTH,//0
		SOUTH,//1
		EAST,//2
		WEST,//3
		NOTMOVING//4
	};
	int direction;

	bool emit;

	sf::Texture texture;
	int lastAddedPrint;

public:
	/*constructor. params: position, type of particles to spawn, number of particles to spawn per second*/
	Emitter(sf::Vector2f pos, int t, int numPs);

	/*destructor*/
	~Emitter();

	/*Update. param is direction to move particles in*/
	void Update(int dir);

	/*Add a new particle*/
	void AddParticle();

	/*Remove any particles that are tagged as removable*/
	void RemoveParticles();

	/*Draw the particles controlled by the emitter*/
	void DrawParticles(sf::RenderTarget& window);
};

#endif
