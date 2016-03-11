#ifndef FOOTPRINTEMITTER_H
#define FOOTPRINTEMITTER_H

class FootprintEmitter : public Emitter
{
private:

	int lastAddedPrint;

	enum Directions
	{
		NORTH,//0
		SOUTH,//1
		EAST,//2
		WEST,//3
		NOTMOVING//4
	};
	int direction;

public:
	/*FootprintEmitter(sf::Vector2f pos, int t, int numPs);*/

	void AddParticle();
};

#endif
