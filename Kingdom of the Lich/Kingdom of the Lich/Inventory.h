#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
private:
	std::map<std::string, int> inventoryItems;
	//background stuff for UI
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;

	sf::Text headerText;
	sf::Font font;

	std::vector<std::string> itemKeys;

	//std::vector<Item> drawableItems;

public:
	//these need to be visible in other classes....Is there a better way of doing this?
	struct items
	{
		std::string key;
	}i_healthPotion, i_ale, i_bread, i_apple, i_gems, i_baracksKey, i_parchment, i_inkBottle, i_quill;

	/*Constructor*/
	Inventory();

	/*Destructor*/
	~Inventory();

	/*Initialise all item in inventory to have '0' quantity*/
	void InitialiseInventoryItems();

	/*
	Prints out the contents of the inventory(all items+quantities)
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

	/*
	Use an item from the inventory
	parameter is the itme to use
	*/
	void UseItem(std::string itemToUse);

	/*Draw items that have a quantity > 0*/
	void Draw(sf::RenderTarget& window);

};

#endif
