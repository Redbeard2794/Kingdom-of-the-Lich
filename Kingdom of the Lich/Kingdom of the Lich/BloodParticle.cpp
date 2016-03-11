#include "stdafx.h"
#include "BloodParticle.h"

BloodParticle::BloodParticle(float ttl, sf::Vector2f pos)
	:Particle(ttl, pos)
{
	LoadTexture();
}

void BloodParticle::LoadTexture()
{
	int randomTextureNum = rand() % 7 + 1;//generate a random number to choose a random texture

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

	setTexture(texture);
}

void BloodParticle::Update()
{
	if (lifeClock.getElapsedTime().asSeconds() >= timeToLive && !removable)//is the time to live up and this has not already been tagged as removable
	{
		removable = true;
	}
	else setPosition(sf::Vector2f(getPosition().x, getPosition().y + 0.1));
}
