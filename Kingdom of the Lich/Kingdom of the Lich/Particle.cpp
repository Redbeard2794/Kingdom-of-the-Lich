#include "stdafx.h"
#include "Particle.h"

/*constructor. params are the time to live, the type, the position to draw them at and the rotation*/
Particle::Particle(float ttl, int t, sf::Vector2f pos, float r) : timeToLive(ttl), type(t)
{
	lifeClock.restart();//start the clock

	LoadTexture();

	removable = false;

	setPosition(pos);

	setRotation(r);
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
		int randomTextureNum = rand() % 7 + 1;

		if (randomTextureNum == 1)
		{
			if (texture.loadFromFile("Assets/Particles/Blood/bloodParticle1.png")) {}
			else texture.loadFromFile("Assets/Debug.png");
		}
		else if (randomTextureNum == 2)
		{
			if (texture.loadFromFile("Assets/Particles/Blood/bloodParticle2.png")) {}
			else texture.loadFromFile("Assets/Debug.png");
		}
		else if (randomTextureNum == 3)
		{
			if (texture.loadFromFile("Assets/Particles/Blood/bloodParticle3.png")) {}
			else texture.loadFromFile("Assets/Debug.png");
		}
		else if (randomTextureNum == 4)
		{
			if (texture.loadFromFile("Assets/Particles/Blood/bloodParticle4.png")) {}
			else texture.loadFromFile("Assets/Debug.png");
		}
		else if (randomTextureNum == 5)
		{
			if (texture.loadFromFile("Assets/Particles/Blood/bloodParticle5.png")) {}
			else texture.loadFromFile("Assets/Debug.png");
		}
		else if (randomTextureNum == 6)
		{
			if (texture.loadFromFile("Assets/Particles/Blood/bloodParticle6.png")) {}
			else texture.loadFromFile("Assets/Debug.png");
		}
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
		setColor(sf::Color(getColor().r, getColor().g, getColor().b, getColor().a - 0.5));
	}
	else if (type == Blood)
	{
		//fall downwards
		setPosition(sf::Vector2f(getPosition().x, getPosition().y + 0.1));
	}
}

/*Is the particle removable?*/
bool Particle::IsRemovable()
{
	return removable;
}

/*Get what type of particle this is*/
int Particle::GetType()
{
	return type;
}
