#ifndef BLOODEMITTER_H
#define BLOODEMITTER_H

class BloodEmitter : public Emitter
{
private:
	enum WoundTypes
	{
		MINOR,
		MAJOR,
		FATAL
	};
	int type;

public:
	/*constructor. params: position to spawn at, how long between particle spawns, how many particles to spawn*/
	BloodEmitter(sf::Vector2f pos, float spawnT, int numPs, int wType);

	/*Add a new particle*/
	void AddParticle();
};

#endif
