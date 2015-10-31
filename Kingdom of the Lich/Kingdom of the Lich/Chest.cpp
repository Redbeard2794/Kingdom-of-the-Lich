#include "stdafx.h"
#include "Chest.h"

Chest::Chest(std::string itemKey) : keyForStoredItem(itemKey)
{
	texture.loadFromFile("Assets/Chests/plainChest.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(sf::Vector2f(SCREENWIDTH/2, SCREENHEIGHT/2));
}

Chest::~Chest()
{

}

void Chest::draw(sf::RenderTarget& window, sf::RenderStates state) const {}

void Chest::draw(sf::RenderTarget& window)
{
	window.draw(sprite);
}