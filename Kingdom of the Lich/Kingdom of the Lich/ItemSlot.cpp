#include "stdafx.h"
#include "ItemSlot.h"

//constructor. param is slotNumber
ItemSlot::ItemSlot(std::string key, int number, sf::Font f) : font(f)
{
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(20);

	currentItemKey = key;
	slotNumber = number;
	open = false;
	selected = false;
	text.setPosition(sf::Vector2f(50, slotNumber * 75));
}

//destructor
ItemSlot::~ItemSlot()
{

}

//Fill an empty slot. param is key of item to store in slot
void ItemSlot::FillSlot(std::string key)
{
	if (open)
	{
		std::cout << "Filling slot " << slotNumber << " with " << key << std::endl;
		currentItemKey = key;
		open = false;
		text.setString(key);
	}
}

//Empty a filled slot
void ItemSlot::EmptySlot()
{
	if (!open)
	{
		std::cout << "Emptying slot " << slotNumber << " of all " << currentItemKey << std::endl;
		currentItemKey = "";
		open = true;//Should I do this here?
	}
}

//Get the key of the currently stored item
std::string ItemSlot::GetCurrentItemKey()
{
	return currentItemKey;
}

//get the slot number
int ItemSlot::GetSlotNumber()
{
	return slotNumber;
}

//is the slot open?
bool ItemSlot::IsOpen()
{
	return open;
}

//reset the slot number and its position
void ItemSlot::ResetSlotNumAndPos(int number)
{
	slotNumber = number;
	text.setPosition(sf::Vector2f(50, slotNumber * 50));
}

void ItemSlot::Draw(sf::RenderTarget & window, int quantity, sf::Color col, bool sel)
{
	selected = sel;
	text.setColor(col);
	text.setString(currentItemKey + " x" + std::to_string(quantity));
	window.draw(text);
}
