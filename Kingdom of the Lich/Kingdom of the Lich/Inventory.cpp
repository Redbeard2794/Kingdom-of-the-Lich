#include "stdafx.h"
#include "Inventory.h"

/*Constructor*/
Inventory::Inventory(sf::Font f) : font(f)
{
	i_healthPotion.key = "Health Potion";
	i_ale.key = "Bottle of Ale";
	i_bread.key = "Loaf of Bread";
	i_apple.key = "Apple";
	i_gems.key = "Gems";
	i_baracksKey.key = "Baracks Key";
	i_parchment.key = "Parchment";
	i_inkBottle.key = "Ink Bottle";
	i_quill.key = "Quill";

	itemKeys.push_back(i_healthPotion.key);
	itemKeys.push_back(i_ale.key);
	itemKeys.push_back(i_bread.key);
	itemKeys.push_back(i_apple.key);
	itemKeys.push_back(i_gems.key);
	itemKeys.push_back(i_baracksKey.key);
	itemKeys.push_back(i_parchment.key);
	itemKeys.push_back(i_inkBottle.key);
	itemKeys.push_back(i_quill.key);

	InitialiseInventoryItems();

	backgroundTexture.loadFromFile("Assets/BackPackInterior.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(15, 5);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 127));

	font.loadFromFile("Assets/Kelt Caps Freehand.TTF");

	headerText.setString("Inventory");
	headerText.setStyle(sf::Text::Underlined);
	headerText.setCharacterSize(60);
	headerText.setFont(font);
	headerText.setPosition(SCREENWIDTH / 3, -12);
	headerText.setColor(sf::Color::Cyan);

	//load item textures
	healthPotTexture.loadFromFile("Assets/Icons/Items/healthPotionIcon.png");
	aleBottleTexture.loadFromFile("Assets/Icons/Items/ale.png");
	loafOfBreadTexture.loadFromFile("Assets/Icons/Items/loafOfBread.png");
	baracksKeyTexture.loadFromFile("Assets/Icons/Items/key.png");
	parchmentTexture.loadFromFile("Assets/Icons/Items/parchmentIcon.png");
	inkBottleTexture.loadFromFile("Assets/Icons/Items/inkBottle.png");

	//set up item sprites and text
	healthPotSprite.setTexture(healthPotTexture);
	healthPotSprite.setOrigin(healthPotTexture.getSize().x / 2, healthPotTexture.getSize().y / 2);
	healthPotSprite.setPosition(90, 100);
	healthText.setString("Health Potion x");
	healthText.setFont(font);
	healthText.setPosition(90, 100 + healthPotTexture.getSize().y / 2);
	healthText.setCharacterSize(15);

	aleBottleSprite.setTexture(aleBottleTexture);
	aleBottleSprite.setOrigin(aleBottleTexture.getSize().x / 2, aleBottleTexture.getSize().y / 2);
	aleBottleSprite.setScale(2, 1.7f);
	aleBottleSprite.setPosition(90, 200);

	loafOfBreadSprite.setTexture(loafOfBreadTexture);
	loafOfBreadSprite.setOrigin(loafOfBreadTexture.getSize().x / 2, loafOfBreadTexture.getSize().y / 2);
	loafOfBreadSprite.setScale(2, 1.7f);
	loafOfBreadSprite.setPosition(90, 300);

	baracksKeySprite.setTexture(baracksKeyTexture);
	baracksKeySprite.setOrigin(baracksKeyTexture.getSize().x / 2, baracksKeyTexture.getSize().y / 2);
	baracksKeySprite.setRotation(-30);
	baracksKeySprite.setPosition(90, 400);

	parchmentSprite.setTexture(parchmentTexture);
	parchmentSprite.setOrigin(parchmentTexture.getSize().x / 2, parchmentTexture.getSize().y / 2);
	parchmentSprite.setPosition(90, 500);

	inkBottleSprite.setTexture(inkBottleTexture);
	inkBottleSprite.setOrigin(inkBottleTexture.getSize().x / 2, inkBottleTexture.getSize().y / 2);
	inkBottleSprite.setScale(1.2f, 1.2f);
	inkBottleSprite.setPosition(290, 100);
}

/*Destructor*/
Inventory::~Inventory()
{

}

/*Initialise all item in inventory to have '0' quantity*/
void Inventory::InitialiseInventoryItems()
{
	for (int i = 0; i < itemKeys.size(); i++)
	{
		inventoryItems[itemKeys.at(i)] = 0;
	}
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
	std::cout << "Could not find that item in the player inventory." << std::endl;
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
			if (it->second < 99)
			{
				std::cout << "Adding " << quantityToAdd << " to " << itemToAddTo << std::endl;
				inventoryItems[itemToAddTo] = it->second + quantityToAdd;
			}
			else std::cout << "Could not add " << quantityToAdd << " " << itemToAddTo << " as it is at max capacity." << std::endl;
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
			else std::cout << "Could not remove item as there is already 0 of this item." << std::endl;
		}
	}
}

/*
Use an item from the inventory
parameter is the itme to use
*/
void Inventory::UseItem(std::string itemToUse)
{
	if (itemToUse == "Health Potion")
	{
		if (inventoryItems["Health Potion"] > 0)
		{
			std::cout << "Using a health potion now" << std::endl;
			RemoveItemFromInventory("Health Potion", 1);
			std::cout << "Healing the player" << std::endl;
			//player would be healed from here in the future
		}
		else std::cout << "you do not have any Health Potions" << std::endl;
	}

	else if (itemToUse == "Loaf of Bread")
	{
		if (inventoryItems["Loaf of Bread"] > 0)
		{

		}
		else std::cout << "you do not have any Loaves of Bread" << std::endl;
	}
}

/*Draw items that have a quantity > 0*/
void Inventory::Draw(sf::RenderTarget& window)
{
	window.draw(backgroundSprite);
	window.draw(headerText);

	//draw items
	window.draw(healthPotSprite);
	healthText.setString("Health Potion *" + std::to_string(CheckQuantity(i_healthPotion.key)));
	window.draw(healthText);

	window.draw(aleBottleSprite);
	window.draw(loafOfBreadSprite);
	window.draw(baracksKeySprite);
	window.draw(parchmentSprite);
	window.draw(inkBottleSprite);
}
