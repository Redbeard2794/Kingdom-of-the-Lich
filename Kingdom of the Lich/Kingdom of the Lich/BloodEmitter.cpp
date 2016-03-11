#include "stdafx.h"
#include "BloodEmitter.h"

BloodEmitter::BloodEmitter(sf::Vector2f pos, float spawnT, int numPs)
	:Emitter(pos, spawnT, numPs)
{
}

void BloodEmitter::AddParticle()
{
		BloodParticle* p = new BloodParticle(2, getPosition());
		particles.push_back(p);
}
