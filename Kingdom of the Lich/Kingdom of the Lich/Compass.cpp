#include "stdafx.h"
#include "Compass.h"

Compass::Compass()
{
	//load the correct texture or load the debug texture if something is wrong
	if (bodyTexture.loadFromFile("Assets/Compass.png")) {}
	else bodyTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	compassBody.setOrigin(sf::Vector2f(bodyTexture.getSize().x / 2, bodyTexture.getSize().y / 2));
	compassBody.setTexture(bodyTexture);

	if (needleTexture.loadFromFile("Assets/CompassNeedle.png")) {}
	else needleTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	needle.setOrigin(sf::Vector2f(needleTexture.getSize().x, needleTexture.getSize().y / 2));
	needle.setTexture(needleTexture);
	needle.setPosition(sf::Vector2f(getPosition().x,getPosition().y-25));
}

Compass::~Compass()
{

}

void Compass::UpdateNeedle(sf::Vector2f playerPos, sf::Vector2f objectivePos)
{
	setPosition(playerPos.x+350, playerPos.y+250);
	needle.setPosition(getPosition());
	//update the orientation of the needle

	sf::Vector2f dirMove = sf::Vector2f(playerPos - objectivePos);
	float length = sqrtf((dirMove.x * dirMove.x) + (dirMove.y * dirMove.y));

	dirMove.x /= length;
	dirMove.y /= length;

	float angle;

	angle = acos(dirMove.x);// +dirMove.y*(180 / 3.14);//angle is in degrees
	angle *= (180 / 3.14);
	if ((int)objectivePos.y < (int)playerPos.y)
		needle.setRotation(angle);
	else needle.setRotation(-angle);
}

void Compass::draw(sf::RenderTarget& window, sf::RenderStates state) const {}

void Compass::draw(sf::RenderTarget& window)
{
	window.draw(compassBody, getTransform());
	window.draw(needle);
}