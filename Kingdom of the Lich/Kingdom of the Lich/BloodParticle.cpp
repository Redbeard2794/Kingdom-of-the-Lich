#include "stdafx.h"
#include "BloodParticle.h"

BloodParticle::BloodParticle(float ttl, sf::Vector2f pos, int wType)
	:Particle(ttl, pos)
{
	type = wType;
	LoadTexture();

	if (type == MAJOR)
	{
		int div = rand() % 100 + 10;
		speed = rand() % 2;
		speed /= div;
		int negCoin = rand() % 2;
		if (negCoin == 1)
			speed = -speed;
	}
	else if (type == FATAL)
	{
		int div = rand() % 100 + 10;
		speed = rand() % 6 + 3;
		speed /= div;
		int negCoin = rand() % 2;
		if (negCoin == 1)
			speed = -speed;
	}

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
	else
	{
		if (type == MINOR)
		{
			setPosition(sf::Vector2f(getPosition().x, getPosition().y + 0.1));
		}
		else if (type == MAJOR)
		{
			setPosition(sf::Vector2f(getPosition().x + speed, getPosition().y + 0.25));
		}
		else if (type == FATAL)
		{
			setPosition(sf::Vector2f(getPosition().x + speed, getPosition().y + 0.25));
		}
	}
}
