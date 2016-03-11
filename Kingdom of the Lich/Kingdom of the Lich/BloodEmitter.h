#ifndef BLOODEMITTER_H
#define BLOODEMITTER_H

class BloodEmitter : public Emitter
{
private:

public:
	/*constructor. params: position to spawn at, how long between particle spawns, how many particles to spawn*/
	BloodEmitter(sf::Vector2f pos, float spawnT, int numPs);

	/*Add a new particle*/
	void AddParticle();
};

#endif
