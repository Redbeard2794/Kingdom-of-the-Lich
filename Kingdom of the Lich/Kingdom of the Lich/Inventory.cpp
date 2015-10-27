#include "stdafx.h"
#include "Inventory.h"

/*Constructor*/
Inventory::Inventory()
{
	inventoryItems["Health Potion"] = 0;
	inventoryItems["Bottle of Ale"] = 0;
	inventoryItems["Loaf of Bread"] = 0;
	inventoryItems["Apple"] = 0;
	inventoryItems["Gems"] = 13;//Currency
	inventoryItems["Baracks Key"] = 0;
	inventoryItems["Parchment"] = 0;
	inventoryItems["Ink Bottle"] = 0;
	inventoryItems["Quill"] = 0;

	backgroundTexture.loadFromFile("Assets/BackPackInterior.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(15, 5);
}

/*Destructor*/
Inventory::~Inventory()
{

}

/*Prints out the contents of the inventory(all items+quantities)
For debugging mostly.
*/
void Inventory::PrintAllInventory()
{
	std::map<std::string, int>::iterator it;

	std::cout << "The inventory consists of: " << std::endl;
	for (it = inventoryItems.begin(); it != inventoryItems.end(); ++it)
	{
		std::cout << "Item: "<< it->first  // string (key)
			<< ", Quantity: "
			<< it->second   // string's value 
			<< std::endl;
	}
}

/*
Checks the quantity of an item
parameter is the item name
*/
int Inventory::CheckQuantity(std::string itemToCheck)
{
	std::map<std::string, int>::iterator it;

	std::cout << "Checking the player's inventory for the quantity of: " << itemToCheck << std::endl;
	for (it = inventoryItems.begin(); it != inventoryItems.end(); ++it)
	{
		if (it->first == itemToCheck)
		{
			std::cout << it->second << std::endl;
			return it->second;
		}
	}
	std::cout << "Could not find that item in the player inventory" << std::endl;
	return 0;
}

/*
Adds an item to the inventory
parameter 1 is the name of the item you want to add
parameter 2 is the amount of that item that you want to add
*/
void Inventory::AddItemToInventory(std::string itemToAddTo, int quantityToAdd)
{
	std::map<std::string, int>::iterator it;
	for (it = inventoryItems.begin(); it != inventoryItems.end(); ++it)
	{
		if (it->first == itemToAddTo)
		{
			std::cout << "Adding " << quantityToAdd << " to " << itemToAddTo << std::endl;
			inventoryItems[itemToAddTo] = it->second + quantityToAdd;
		}
	}
}

/*
Remove an item from the inventory
parameter 1 is the name of the item you want to remove
parameter 2 is the amount of that item that you want to remove
*/
void Inventory::RemoveItemFromInventory(std::string itemToRemoveFrom, int quantityToRemove)
{
	std::map<std::string, int>::iterator it;
	for (it = inventoryItems.begin(); it != inventoryItems.end(); ++it)
	{
		if (it->first == itemToRemoveFrom)
		{
			if (it->second > 0)
			{
				std::cout << "Removing " << quantityToRemove << " from " << itemToRemoveFrom << std::endl;
				inventoryItems[itemToRemoveFrom] = it->second - quantityToRemove;
			}
			else std::cout << "Could not remove item as there is already 0 of this item" << std::endl;
		}
	}
}

void Inventory::Draw(sf::RenderTarget& window)
{
	window.draw(backgroundSprite);
}
