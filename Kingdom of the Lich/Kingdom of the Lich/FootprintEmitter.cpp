#include "stdafx.h"
#include "FootprintEmitter.h"

/*constructor. params: position to spawn at, how long between particle spawns, how many particles to spawn*/
FootprintEmitter::FootprintEmitter(sf::Vector2f pos, float spawnT, int numPs)
	: Emitter(pos, spawnT, numPs)
{
	//std::cout << "Footprint emitter created." << std::endl;
	lastAddedPrint = 0;
}

/*Add a new particle*/
void FootprintEmitter::AddParticle()
{
		float r = 0;
		sf::Vector2f pos = getPosition();
	
		//sort out the orientation for the new particle
		switch (direction)
		{
		case NORTH:
			r = 270;
			pos = sf::Vector2f(getPosition().x - 3, getPosition().y + 5);
			break;
		case SOUTH:
			r = 90;
			pos = sf::Vector2f(getPosition().x, getPosition().y + 5);
			break;
		case EAST:
			r = 0;
			pos = sf::Vector2f(getPosition().x - 10, getPosition().y + 17);
			break;
		case WEST:
			r = 180;
			pos = sf::Vector2f(getPosition().x + 10, getPosition().y + 23);
			break;
		case NOTMOVING:
	
			break;
		}
	
		if (lastAddedPrint == 0 && direction != NOTMOVING)
		{
			FootprintParticle* p = new FootprintParticle(2, pos, lastAddedPrint, r);
			particles.push_back(p);
			lastAddedPrint = 1;
		}
		else if (lastAddedPrint == 1 && direction != NOTMOVING)
		{
	
			FootprintParticle* p = new FootprintParticle(2, pos, lastAddedPrint, r);
			particles.push_back(p);
			lastAddedPrint = 0;
		}
}

/*set this emitters direction*/
void FootprintEmitter::SetDirection(int dir)
{
	direction = dir;
}
