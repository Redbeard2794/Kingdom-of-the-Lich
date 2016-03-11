#include "stdafx.h"
#include "Emitter.h"

/*constructor. params: position, type of particles to spawn, number of particles to spawn per second*/
Emitter::Emitter(sf::Vector2f pos, float spawnT, int numPs) : spawnTime(spawnT), numParticlesPerSpawn(numPs)
{
	if (texture.loadFromFile("Assets/Particles/Emitter/emitterDebug.png")) {}
	else texture.loadFromFile("Assets/Debug.png");

	setTexture(texture);

	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	setPosition(pos);

	spawnClock.restart();

	emit = true;

	std::cout << "Emitter created." << std::endl;
}

/*destructor*/
Emitter::~Emitter()
{
	//blank for now
}

/*Update. param is direction to move particles in, defaults to -1*/
void Emitter::Update()//int dir)
{
	//particle spawning
	if (spawnClock.getElapsedTime().asSeconds() >= spawnTime && emit == true)//if a second has passed and emitter currently emitting
	{
		for (int i = 0; i < numParticlesPerSpawn; i++)//add numParticlesPerSecond number of particles
		{
			AddParticle();
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
	if (particles.size() > 0)
	{
		for (int i = 0; i < particles.size(); i++)
		{
			window.draw(*particles.at(i));
		}
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
