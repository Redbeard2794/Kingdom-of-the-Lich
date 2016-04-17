#include "stdafx.h"
#include "Bed.h"

Bed::Bed(int i, sf::Vector2f pos) : id(i)
{
	if (texture.loadFromFile("Assets/bedRoll.png")) {}
	else texture.loadFromFile("Assets/Debug.png");

	setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setPosition(pos);
	setColor(sf::Color::Cyan);
}

Bed::~Bed()
{
	texture.~Texture();
}

int Bed::GetId()
{
	return id;
}
