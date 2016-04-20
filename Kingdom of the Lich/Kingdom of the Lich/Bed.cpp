#include "stdafx.h"
#include "Bed.h"

/*constructor. params are an id and a position*/
Bed::Bed(int i, sf::Vector2f pos) : id(i)
{
	if (texture.loadFromFile("Assets/bedRoll.png")) {}
	else texture.loadFromFile("Assets/Debug.png");

	setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setPosition(pos);
	setColor(sf::Color::Cyan);
}

//destructor
Bed::~Bed()
{
	texture.~Texture();
}

/*Retrieve this beds id*/
int Bed::GetId()
{
	return id;
}
