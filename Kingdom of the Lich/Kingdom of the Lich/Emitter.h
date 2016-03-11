#ifndef EMITTER_H
#define EMITTER_H

#include "Particle.h"

class Emitter : public sf::Sprite
{
protected:
	std::vector<Particle*> particles;

	int particleType;

	int numParticlesPerSpawn;//the number of particles to spaw each second

	sf::Clock spawnClock;

	float spawnTime;

	bool emit;

	sf::Texture texture;

public:
	/*constructor. params: position, type of particles to spawn, number of particles to spawn per second*/
	Emitter(sf::Vector2f pos, float spawnT, int numPs);

	/*destructor*/
	~Emitter();

	/*Update. param is direction to move particles in*/
	void Update();// int dir = -1);

	///*Add a new footprint particle*/
	//void AddFootprintParticle(int dir);

	///*Add a new blood drop particle*/
	//void AddBloodParticle();

	virtual void AddParticle() {}

	/*Remove any particles that are tagged as removable*/
	void RemoveParticles();

	/*Draw the particles controlled by the emitter*/
	void DrawParticles(sf::RenderTarget& window);

	bool IsEmitting();

	void SetEmit(bool e);
};

#endif
