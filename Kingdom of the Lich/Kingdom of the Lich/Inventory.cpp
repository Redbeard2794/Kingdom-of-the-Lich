#include "stdafx.h"
#include "Inventory.h"

/*Constructor*/
Inventory::Inventory(sf::Font f, bool controller, int sw, int sh) : font(f), showControllerHints(controller)
{
	screenW = sw;
	screenH = sh;

	currentlySelectedItem = 0;
	canMove = true;

	//load these keys from a file eventually
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

	if (backgroundTexture.loadFromFile("Assets/Inventory/BackPackInterior" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png")) {}
	else backgroundTexture.loadFromFile("Assets/Inventory/BackPackInterior.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(15, 5);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 127));

	font.loadFromFile("Assets/Kelt Caps Freehand.TTF");

	headerText.setString("Inventory");
	headerText.setStyle(sf::Text::Underlined);
	headerText.setCharacterSize(60);
	headerText.setFont(font);
	headerText.setPosition(screenW / 2.5, -2);
	headerText.setColor(sf::Color::Cyan);

	//load item textures(maybe take these from a file too?)
	healthPotTexture.loadFromFile("Assets/Icons/Items/healthPotionIcon.png");
	aleBottleTexture.loadFromFile("Assets/Icons/Items/ale.png");
	loafOfBreadTexture.loadFromFile("Assets/Icons/Items/loafOfBread.png");
	baracksKeyTexture.loadFromFile("Assets/Icons/Items/key.png");
	parchmentTexture.loadFromFile("Assets/Icons/Items/parchmentIcon.png");
	inkBottleTexture.loadFromFile("Assets/Icons/Items/inkBottle.png");
	gemTexture.loadFromFile("Assets/Icons/Items/gemsIcon.png");
	appleTexture.loadFromFile("Assets/Icons/Items/apple.png");
	quillTexture.loadFromFile("Assets/Icons/Items/quill.png");

	//need to come up with a way of only showing items with quantity > 0
	//also need to take item names from keys/file

	//set up item sprites and text
	healthPotSprite.setTexture(healthPotTexture);
	healthPotSprite.setOrigin(healthPotTexture.getSize().x / 2, healthPotTexture.getSize().y / 2);
	healthPotSprite.setPosition(screenW / 10, 100);
	healthText.setString("Health Potion x");
	healthText.setFont(font);
	healthText.setPosition(screenW / 8, 70 + healthPotTexture.getSize().y / 2);
	healthText.setCharacterSize(15);

	aleBottleSprite.setTexture(aleBottleTexture);
	aleBottleSprite.setOrigin(aleBottleTexture.getSize().x / 2, aleBottleTexture.getSize().y / 2);
	aleBottleSprite.setScale(2, 1.7f);
	aleBottleSprite.setPosition(screenW / 10, 200);
	aleText.setString("Bottle of Ale x");
	aleText.setFont(font);
	aleText.setPosition(screenW / 8, 170 + aleBottleTexture.getSize().y / 2);
	aleText.setCharacterSize(15);

	loafOfBreadSprite.setTexture(loafOfBreadTexture);
	loafOfBreadSprite.setOrigin(loafOfBreadTexture.getSize().x / 2, loafOfBreadTexture.getSize().y / 2);
	loafOfBreadSprite.setScale(2, 1.7f);
	loafOfBreadSprite.setPosition(screenW / 10, 300);
	breadText.setString("Loaf of Bread x");
	breadText.setFont(font);
	breadText.setPosition(screenW / 8, 270 + loafOfBreadTexture.getSize().y / 2);
	breadText.setCharacterSize(15);

	baracksKeySprite.setTexture(baracksKeyTexture);
	baracksKeySprite.setOrigin(baracksKeyTexture.getSize().x / 2, baracksKeyTexture.getSize().y / 2);
	baracksKeySprite.setRotation(-30);
	baracksKeySprite.setPosition(screenW / 10, 400);
	baracksKeyText.setString("Baracks key x");
	baracksKeyText.setFont(font);
	baracksKeyText.setPosition(screenW / 8, 370 + baracksKeyTexture.getSize().y / 2);
	baracksKeyText.setCharacterSize(15);

	parchmentSprite.setTexture(parchmentTexture);
	parchmentSprite.setOrigin(parchmentTexture.getSize().x / 2, parchmentTexture.getSize().y / 2);
	parchmentSprite.setPosition(screenW / 10, 500);
	parchmentText.setString("Parchment x");
	parchmentText.setFont(font);
	parchmentText.setPosition(screenW / 8, 470 + parchmentTexture.getSize().y / 2);
	parchmentText.setCharacterSize(15);

	inkBottleSprite.setTexture(inkBottleTexture);
	inkBottleSprite.setOrigin(inkBottleTexture.getSize().x / 2, inkBottleTexture.getSize().y / 2);
	inkBottleSprite.setScale(1.2f, 1.2f);
	inkBottleSprite.setPosition(screenW / 3.3, 100);
	inkBottleText.setString("Ink Bottle x");
	inkBottleText.setFont(font);
	inkBottleText.setPosition(screenW / 3, 70 + inkBottleTexture.getSize().y / 2);
	inkBottleText.setCharacterSize(15);

	gemSprite.setTexture(gemTexture);
	gemSprite.setOrigin(gemTexture.getSize().x / 2, gemTexture.getSize().y / 2);
	gemSprite.setScale(1.5f, 1.5f);
	gemSprite.setPosition(screenW / 3.3, 200);
	gemText.setString("Gems x");
	gemText.setFont(font);
	gemText.setPosition(screenW / 3, 170 + gemTexture.getSize().y / 2);
	gemText.setCharacterSize(15);

	appleSprite.setTexture(appleTexture);
	appleSprite.setOrigin(appleTexture.getSize().x / 2, appleTexture.getSize().y / 2);
	//appleSprite.setScale(1.5f, 1.5f);
	appleSprite.setPosition(screenW / 3.3, 300);
	appleText.setString("Apple x");
	appleText.setFont(font);
	appleText.setPosition(screenW / 3, 270 + appleTexture.getSize().y / 2);
	appleText.setCharacterSize(15);

	quillSprite.setTexture(quillTexture);
	quillSprite.setOrigin(quillTexture.getSize().x / 2, quillTexture.getSize().y / 2);
	//quillSprite.setScale(1.5f, 1.5f);
	quillSprite.setPosition(screenW / 3.3, 400);
	quillText.setString("Quill x");
	quillText.setFont(font);
	quillText.setPosition(screenW / 3, 370 + quillTexture.getSize().y / 2);
	quillText.setCharacterSize(15);

	//hints
	if (showControllerHints == true)
		exitHintTexture.loadFromFile("Assets/ControllerHints/pressBackToReturnToGameHint.png");
	else if (showControllerHints == false)
		exitHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/PressEnterToReturnToGameHint.png");
	exitHintSprite.setTexture(exitHintTexture);
	exitHintSprite.setOrigin(exitHintTexture.getSize().x / 2, exitHintTexture.getSize().y / 2);
	exitHintSprite.setPosition(screenW/2.1, screenH/1.05);

	CheckItemsToShow();
}

/*Destructor*/
Inventory::~Inventory()
{

}

/*Initialise all items in inventory to have '0' quantity*/
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
int Inventory::CheckQuantity(std::string itemToCheck, bool output)
{
	std::map<std::string, int>::iterator it;
	if(output == true)
		std::cout << "Checking the player's inventory for the quantity of: " << itemToCheck << std::endl;
	for (it = inventoryItems.begin(); it != inventoryItems.end(); ++it)
	{
		if (it->first == itemToCheck)
		{
			if (output == true)
				std::cout << it->second << std::endl;
			return it->second;
		}
	}
	if (output == true)
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

//check items that should be drawn i.e. items that have a quantity > 0
void Inventory::CheckItemsToShow()
{
	for (int i = 0; i < itemKeys.size(); i++)
	{
		if (std::find(drawableItems.begin(), drawableItems.end(), itemKeys.at(i)) != drawableItems.end() == false)//if the item is not already in the drawable items vector
		{
			if (CheckQuantity(itemKeys.at(i), false) > 0)//if the quantity of this item is > 0
			{
				drawableItems.push_back(itemKeys.at(i));//add the item to the drawable items vector
			}
		}
	}
}

void Inventory::NavigateUp()
{
	if (canMove)
	{
		if (currentlySelectedItem == drawableItems.size())
			currentlySelectedItem = 0;
		else currentlySelectedItem++;
	}
}

void Inventory::NavigateDown()
{
	if (canMove)
	{
		if (currentlySelectedItem == 0)
			currentlySelectedItem = drawableItems.size();
		else currentlySelectedItem--;
	}
}

/*Draw items that have a quantity > 0*/
void Inventory::Draw(sf::RenderTarget& window)
{
	CheckItemsToShow();
	window.draw(backgroundSprite);
	window.draw(headerText);

	for (int i = 0; i < drawableItems.size(); i++)
	{
		if (drawableItems.at(i) == i_healthPotion.key)
		{
			window.draw(healthPotSprite);
			healthText.setString("Health Potion *" + std::to_string(CheckQuantity(i_healthPotion.key, false)));
			window.draw(healthText);
		}
		else if (drawableItems.at(i) == i_ale.key)
		{
			window.draw(aleBottleSprite);
			aleText.setString("Bottle of Ale *" + std::to_string(CheckQuantity(i_ale.key, false)));
			window.draw(aleText);
		}
		else if (drawableItems.at(i) == i_bread.key)
		{
			window.draw(loafOfBreadSprite);
			breadText.setString("Loaf of Bread *" + std::to_string(CheckQuantity(i_bread.key, false)));
			window.draw(breadText);
		}
		else if (drawableItems.at(i) == i_baracksKey.key)
		{
			window.draw(baracksKeySprite);
			baracksKeyText.setString("Baracks key *" + std::to_string(CheckQuantity(i_baracksKey.key, false)));
			window.draw(baracksKeyText);
		}
		else if (drawableItems.at(i) == i_parchment.key)
		{
			window.draw(parchmentSprite);
			parchmentText.setString("Parchment *" + std::to_string(CheckQuantity(i_parchment.key, false)));
			window.draw(parchmentText);
		}
		else if (drawableItems.at(i) == i_inkBottle.key)
		{
			window.draw(inkBottleSprite);
			inkBottleText.setString("Ink Bottle *" + std::to_string(CheckQuantity(i_inkBottle.key, false)));
			window.draw(inkBottleText);
		}
		else if (drawableItems.at(i) == i_gems.key)
		{
			window.draw(gemSprite);
			gemText.setString("Gems *" + std::to_string(CheckQuantity(i_gems.key, false)));
			window.draw(gemText);
		}
		else if (drawableItems.at(i) == i_apple.key)
		{
			window.draw(appleSprite);
			appleText.setString("Apple *" + std::to_string(CheckQuantity(i_apple.key, false)));
			window.draw(appleText);
		}
		else if (drawableItems.at(i) == i_quill.key)
		{
			window.draw(quillSprite);
			quillText.setString("Quill *" + std::to_string(CheckQuantity(i_quill.key, false)));
			window.draw(quillText);
		}
	}

	window.draw(exitHintSprite);
}
