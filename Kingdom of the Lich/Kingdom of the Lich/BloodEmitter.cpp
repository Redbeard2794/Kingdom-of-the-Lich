#include "stdafx.h"
#include "BloodEmitter.h"

BloodEmitter::BloodEmitter(sf::Vector2f pos, float spawnT, int numPs, int wType)
	:Emitter(pos, spawnT, numPs)
{
	type = wType;
}

void BloodEmitter::AddParticle()
{
	if (type == MINOR)
	{
		BloodParticle* p = new BloodParticle(4, getPosition(), type);
		particles.push_back(p);
	}
	else if (type == MAJOR)
	{
		BloodParticle* p = new BloodParticle(3, getPosition(), type);
		particles.push_back(p);
	}
	else if (type == FATAL)
	{
		BloodParticle* p = new BloodParticle(2, getPosition(), type);
		particles.push_back(p);
	}
}
