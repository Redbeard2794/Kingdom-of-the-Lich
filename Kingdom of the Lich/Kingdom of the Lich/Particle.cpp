#include "stdafx.h"
#include "Particle.h"

/*constructor. params are the time to live and the position to draw them at*/
Particle::Particle(float ttl, sf::Vector2f pos) : timeToLive(ttl)
{
	lifeClock.restart();//start the clock

	removable = false;

	setPosition(pos);
}

/*destructor*/
Particle::~Particle()
{
	texture.~Texture();//destroy the texture
}

/*Load the correct texture based on the type*/
void Particle::LoadTexture()
{

}

/*Check if the time to live is up*/
void Particle::Update()
{
	if (lifeClock.getElapsedTime().asSeconds() >= timeToLive && !removable)//is the time to live up and this has not already been tagged as removable
	{
		removable = true;
	}
}

/*Is the particle removable?*/
bool Particle::IsRemovable()
{
	return removable;
}
