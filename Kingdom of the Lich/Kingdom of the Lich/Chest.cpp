#include "stdafx.h"
#include "Chest.h"

/*Constructor*/
Chest::Chest(std::string itemKey, int quantity) : keyForStoredItem(itemKey), quantityOfStoredItem(quantity)
{
	//set up the texture and sprite
	texture.loadFromFile("Assets/Chests/plainChest.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(sf::Vector2f(SCREENWIDTH/2, SCREENHEIGHT/2));//setPosition rather than sprite.setPosition?

	opened = false;//The chest is not open yet
}

/*Destructor*/
Chest::~Chest()
{

}

/*Add the items contained in the chest to the inventory and open the chest*/
void Chest::OpenChest(Inventory* inv)
{
	inv->AddItemToInventory(keyForStoredItem, quantityOfStoredItem);
	opened = true;
}

void Chest::draw(sf::RenderTarget& window, sf::RenderStates state) const {}

/*Draw*/
void Chest::draw(sf::RenderTarget& window)
{
	//change the colour based in whether the chest is open or not
	if (opened == true)
	{
		sprite.setColor(sf::Color(255, 255, 255, 127));
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255, 255));
	}
	window.draw(sprite, getTransform());
}