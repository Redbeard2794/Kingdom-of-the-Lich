#include "stdafx.h"
#include "Item.h"

Item::Item(std::string key, std::string texturePath, int val)
{
	itemKey = key;

	if(texture.loadFromFile(texturePath)){}
	else texture.loadFromFile("Assets/Debug.png");
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setTexture(texture);
	setPosition(50, 50);
	scale(2, 2);

	value = val;
}

Item::~Item()
{
	texture.~Texture();
}

std::string Item::RetrieveKey()
{
	return itemKey;
}

int Item::GetValue()
{
	return value;
}
