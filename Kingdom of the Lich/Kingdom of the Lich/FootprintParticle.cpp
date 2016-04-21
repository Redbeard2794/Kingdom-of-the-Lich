#include "stdafx.h"
#include "FootprintParticle.h"

/*constructor. params: time to live, position to spawn at, type(left or right i.e 0 or 1) and rotation*/
FootprintParticle::FootprintParticle(float ttl, sf::Vector2f pos, int t, float r)
	:Particle(ttl, pos)
{
	setRotation(r);//set the rotation
	type = t;
	LoadTexture();
}

/*Load the correct texture*/
void FootprintParticle::LoadTexture()
{
	if (type == LEFT)//if it should be a left foot print
	{
		if (texture.loadFromFile("Assets/Particles/FootPrints/leftFootPrintR.png")) {}
		else texture.loadFromFile("Assets/Debug.png");
		scale(.25, .25);
	}
	else if (type == RIGHT)//if it should be a right foot print
	{
		if (texture.loadFromFile("Assets/Particles/FootPrints/rightFootPrintR.png")) {}
		else texture.loadFromFile("Assets/Debug.png");
		scale(.25, .25);
	}

	setTexture(texture);
}

/*Update the particle*/
void FootprintParticle::Update()
{
	if (lifeClock.getElapsedTime().asSeconds() >= timeToLive && !removable)//is the time to live up and this has not already been tagged as removable
	{
		removable = true;
	}
	else setColor(sf::Color(getColor().r, getColor().g, getColor().b, getColor().a - 0.5));//slowly fade out
}
