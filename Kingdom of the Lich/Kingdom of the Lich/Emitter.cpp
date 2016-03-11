#include "stdafx.h"
#include "Emitter.h"

/*constructor. params: position, type of particles to spawn, number of particles to spawn per second*/
Emitter::Emitter(sf::Vector2f pos, int t, int numPs) : particleType(t), numParticlesPerSecond(numPs)
{
	if (texture.loadFromFile("Assets/Particles/Emitter/emitterDebug.png")) {}
	else texture.loadFromFile("Assets/Debug.png");

	setTexture(texture);

	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	setPosition(pos);

	spawnClock.restart();

	emit = true;

	lastAddedPrint = 1;
}

/*destructor*/
Emitter::~Emitter()
{
	//blank for now
}

/*Update. param is direction to move particles in, defaults to -1*/
void Emitter::Update(int dir)
{
	//particle spawning
	if (spawnClock.getElapsedTime().asSeconds() >= .3 && emit == true)//if a second has passed and emitter currently emitting
	{
		for (int i = 0; i < numParticlesPerSecond; i++)//add numParticlesPerSecond number of particles
		{
			if (particleType == LeftFootPrint || particleType == RightFootPrint)
				AddFootprintParticle(dir);
			else if (particleType == Blood)
				AddBloodParticle();
			//std::cout << "Added a new Particle." << std::endl;
		}
		spawnClock.restart();//restart the spawn clock
	}

	//check for particles that are tagged as removable
	RemoveParticles();

	//update particles
	for (int i = 0; i < particles.size(); i++)
	{
		particles.at(i)->Update();
	}
}

/*Add a new footprint particle*/
void Emitter::AddFootprintParticle(int dir)
{
	float r = 0;
	sf::Vector2f pos = getPosition();

	switch (dir)
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

		if (lastAddedPrint == 1)
		{
			Particle* p = new Particle(2, 0, pos, r);
			particles.push_back(p);
			lastAddedPrint = 2;
		}
		else if (lastAddedPrint == 2)
		{

			Particle* p = new Particle(2, 1, pos, r);
			particles.push_back(p);
			lastAddedPrint = 1;
		}
}

void Emitter::AddBloodParticle()
{
	Particle* p = new Particle(2, 2, getPosition(), 0);
	particles.push_back(p);
}

/*Remove any particles that are tagged as removable*/
void Emitter::RemoveParticles()
{
	for (auto it = particles.begin(); it != particles.end();)
	{
		if ((*it)->IsRemovable())//if the particle can be removed
		{
			delete * it;//delete the pointer
			it = particles.erase(it);//erase the object(calls the objects destructor)
			//std::cout << "removed a particle." << std::endl;
		}
		else ++it;
	}
}

/*Draw the particles controlled by the emitter*/
void Emitter::DrawParticles(sf::RenderTarget & window)
{
	for (int i = 0; i < particles.size(); i++)
	{
		window.draw(*particles.at(i));
	}
}

bool Emitter::IsEmitting()
{
	return emit;
}

void Emitter::SetEmit(bool e)
{
	emit = e;
}
