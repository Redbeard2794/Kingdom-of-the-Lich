#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
private:
	std::map<std::string, int> inventoryItems;
	//background stuff for UI
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;



public:
	/*Constructor*/
	Inventory();
	/*Destructor*/
	~Inventory();

	/*Prints out the contents of the inventory(all items+quantities)
	For debugging mostly.
	*/
	void PrintAllInventory();

	/*
	Checks the quantity of an item
	parameter is the item name
	*/
	int CheckQuantity(std::string itemToCheck);

	/*
	Adds an item to the inventory
	parameter 1 is the name of the item you want to add
	parameter 2 is the amount of that item that you want to add
	*/
	void AddItemToInventory(std::string itemToAddTo, int quantityToAdd);

	/*
	Remove an item from the inventory
	parameter 1 is the name of the item you want to remove
	parameter 2 is the amount of that item that you want to remove
	*/
	void RemoveItemFromInventory(std::string itemToRemoveFrom, int quantityToRemove);

	void Draw(sf::RenderTarget& window);
};

#endif
