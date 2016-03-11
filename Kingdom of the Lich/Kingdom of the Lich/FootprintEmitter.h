#ifndef FOOTPRINTEMITTER_H
#define FOOTPRINTEMITTER_H

class FootprintEmitter : public Emitter
{
private:

	int lastAddedPrint;//which print(left or right) was added last

	//all possible directions to face
	enum Directions
	{
		NORTH,//0
		SOUTH,//1
		EAST,//2
		WEST,//3
		NOTMOVING//4
	};
	int direction;//this emitters direction

public:
	/*constructor. params: position to spawn at, how long between particle spawns, how many particles to spawn*/
	FootprintEmitter(sf::Vector2f pos, float spawnT, int numPs);

	/*Add a new particle*/
	void AddParticle();

	/*set this emitters direction*/
	void SetDirection(int dir);
};

#endif
