#ifndef COLLIDABLEOBJECT_H
#define COLLIDABLEOBJECT_H

class CollidableObject : public sf::RectangleShape
{
private:
	bool intersectable;
	bool visible;
public:
	/*
	Constructor
	params: x position, y position, width, height, visible and can objects intersect it
	*/
	CollidableObject(float xPos, float yPos, float w, float h, bool v, bool intersect);

	/*Destructor*/
	~CollidableObject();

	/*Check if the passed in rectangle intersects with the Collidable Objects global bounds*/
	bool CheckIntersectionRectangle(sf::FloatRect objectToCheck);

	/*Check if the Collidable Objects global bounds contains the point passed in*/
	bool CheckContainsPoint(sf::Vector2f pointToCheck);
};

#endif;
