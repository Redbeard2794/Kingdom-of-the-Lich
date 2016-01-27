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

	bool CheckCollisionRightSide(sf::FloatRect boundsToCheck, sf::Vector2f objectPosition);
	bool CheckCollisionLeftSide(sf::FloatRect boundsToCheck, sf::Vector2f objectPosition);
	bool CheckCollisionTopSide(sf::FloatRect boundsToCheck, sf::Vector2f objectPosition);
	bool CheckCollisionBottomSide(sf::FloatRect boundsToCheck, sf::Vector2f objectPosition);

	/*Check if the Collidable Objects global bounds contains the point passed in*/
	bool CheckContainsPoint(sf::Vector2f pointToCheck);
};

#endif;
