#include "stdafx.h"
#include "CollidableObject.h"

/*
Constructor
params: x position, y position, width, height, visible and can objects intersect it
*/
CollidableObject::CollidableObject(float x, float y, float w, float h, bool v, bool intersect) : visible(v), intersectable(intersect)
{
	setPosition(x, y);
	setSize(sf::Vector2f(w, h));
	setOutlineThickness(2);
	setOutlineColor(sf::Color(255, 0, 247, 255));
	setFillColor(sf::Color::Transparent);
}

/*Destructor*/
CollidableObject::~CollidableObject()
{

}

/*Check if the passed in rectangle intersects with the Collidable Objects global bounds*/
bool CollidableObject::CheckIntersectionRectangle(sf::FloatRect objectToCheck)
{
	if (getGlobalBounds().intersects(objectToCheck))
	{
		//std::cout << "Global bounds intersects the object passed in" << std::endl;
		return true;
	}
	else return false;
}

/*Check if the Collidable Objects global bounds contains the point passed in*/
bool CollidableObject::CheckContainsPoint(sf::Vector2f pointToCheck)
{
	if (getGlobalBounds().contains(pointToCheck))
	{
		std::cout << "Global bounds contains the point passed in" << std::endl;
		return true;
	}
	else return false;
}
