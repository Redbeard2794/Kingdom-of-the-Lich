#include "stdafx.h"
#include "Compass.h"

//constructor
Compass::Compass(int sW, int sH, float yPos)
{
	screenW = sW;
	screenH = sH;
	//load the correct texture or load the debug texture if something is wrong
	if (bodyTexture.loadFromFile("Assets/Compass/body/compass1366x768.png")) {}
	else bodyTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	compassBody.setOrigin(sf::Vector2f(bodyTexture.getSize().x / 2, bodyTexture.getSize().y / 2));
	compassBody.setTexture(bodyTexture);
	//compassBody.scale(1.4, 1.4);
	setPosition(screenW / 2, yPos);

	if (needleTexture.loadFromFile("Assets/Compass/CompassNeedle.png")) {}
	else needleTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	needle.setOrigin(sf::Vector2f(needleTexture.getSize().x, needleTexture.getSize().y / 2));
	needle.setTexture(needleTexture);
	needle.scale(2, 2);
	needle.setPosition(sf::Vector2f(getPosition().x,getPosition().y-25));
}

//destructor
Compass::~Compass()
{

}

//update the direction the compass needle is pointing in
void Compass::UpdateNeedle(sf::Vector2f playerPos, sf::Vector2f objectivePos)
{
	needle.setPosition(getPosition());

	//update the orientation of the needle
	sf::Vector2f dirMove = sf::Vector2f(playerPos - objectivePos);//vector between player and objective
	float length = sqrtf((dirMove.x * dirMove.x) + (dirMove.y * dirMove.y));

	dirMove.x /= length;
	dirMove.y /= length;

	float angle;

	angle = acos(dirMove.x);
	angle *= (180 / 3.14);

	if ((int)objectivePos.y < (int)playerPos.y)
		needle.setRotation(angle);
	else needle.setRotation(-angle);
}

void Compass::draw(sf::RenderTarget& window, sf::RenderStates state) const {}

//draw the compass and needle
void Compass::draw(sf::RenderTarget& window)
{
	window.draw(compassBody, getTransform());
	window.draw(needle);
}