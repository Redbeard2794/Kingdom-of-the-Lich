#include "stdafx.h"
#include "Chest.h"

Chest::Chest(std::string itemKey, int quantity) : keyForStoredItem(itemKey), quantityOfStoredItem(quantity)
{
	texture.loadFromFile("Assets/Chests/plainChest.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(sf::Vector2f(SCREENWIDTH/2, SCREENHEIGHT/2));
	opened = false;
}

Chest::~Chest()
{

}

void Chest::OpenChest(Inventory* inv)
{
	inv->AddItemToInventory(keyForStoredItem, quantityOfStoredItem);
	opened = true;
}

void Chest::draw(sf::RenderTarget& window, sf::RenderStates state) const {}

void Chest::draw(sf::RenderTarget& window)
{
	if (opened == true)
	{
		sprite.setColor(sf::Color(255, 255, 255, 127));
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	window.draw(sprite);
}