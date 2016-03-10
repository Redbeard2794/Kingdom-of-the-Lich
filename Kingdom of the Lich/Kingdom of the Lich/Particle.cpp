#include "stdafx.h"
#include "Particle.h"

/*constructor. params are the time to live and the type*/
Particle::Particle(float ttl, int t, sf::Vector2f pos) : timeToLive(ttl), type(t)
{
	lifeClock.restart();//start the clock

	LoadTexture();

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
	if (type == LeftFootPrint)
	{
		if (texture.loadFromFile("Assets/Particles/FootPrints/leftFootPrintR.png")) {}
		else texture.loadFromFile("Assets/Debug.png");
		scale(.25, .25);
	}
	else if (type == RightFootPrint)
	{
		if (texture.loadFromFile("Assets/Particles/FootPrints/rightFootPrintR.png")) {}
		else texture.loadFromFile("Assets/Debug.png");
		scale(.25, .25);
	}
	else if (type == Blood)
	{
		//blank for now
	}
	//set the texture
	setTexture(texture);
}

/*Check if the time to live is up*/
void Particle::Update()
{
	if (lifeClock.getElapsedTime().asSeconds() >= timeToLive && !removable)//is the time to live up and this has not already been tagged as removable
	{
		removable = true;
	}



	if (type == LeftFootPrint || type == RightFootPrint)
	{
		//fade out slowly
	}
	else if (type == Blood)
	{
		//fall downwards
	}
}

/*Is the particle removable?*/
bool Particle::IsRemovable()
{
	return removable;
}
