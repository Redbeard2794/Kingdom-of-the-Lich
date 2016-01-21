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

	std::string line;
	std::ifstream myfile("Assets/Inventory/itemKeys.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line << '\n' << std::endl;;
		}
		myfile.close();
	}

	else std::cout << "Unable to open file" << std::endl;;

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

	itemTexts[0].setString("Health Potion x");
	itemTexts[0].setFont(font);
	itemTexts[0].setPosition(screenW / 8, 70 + healthPotTexture.getSize().y / 2);
	itemTexts[0].setCharacterSize(15);

	aleBottleSprite.setTexture(aleBottleTexture);
	aleBottleSprite.setOrigin(aleBottleTexture.getSize().x / 2, aleBottleTexture.getSize().y / 2);
	aleBottleSprite.setScale(2, 1.7f);
	aleBottleSprite.setPosition(screenW / 10, 200);

	itemTexts[1].setString("Bottle of Ale x");
	itemTexts[1].setFont(font);
	itemTexts[1].setPosition(screenW / 8, 170 + aleBottleTexture.getSize().y / 2);
	itemTexts[1].setCharacterSize(15);

	loafOfBreadSprite.setTexture(loafOfBreadTexture);
	loafOfBreadSprite.setOrigin(loafOfBreadTexture.getSize().x / 2, loafOfBreadTexture.getSize().y / 2);
	loafOfBreadSprite.setScale(2, 1.7f);
	loafOfBreadSprite.setPosition(screenW / 10, 300);

	itemTexts[2].setString("Loaf of Bread x");
	itemTexts[2].setFont(font);
	itemTexts[2].setPosition(screenW / 8, 270 + loafOfBreadTexture.getSize().y / 2);
	itemTexts[2].setCharacterSize(15);

	baracksKeySprite.setTexture(baracksKeyTexture);
	baracksKeySprite.setOrigin(baracksKeyTexture.getSize().x / 2, baracksKeyTexture.getSize().y / 2);
	baracksKeySprite.setRotation(-30);
	baracksKeySprite.setPosition(screenW / 10, 400);

	itemTexts[3].setString("Baracks key x");
	itemTexts[3].setFont(font);
	itemTexts[3].setPosition(screenW / 8, 370 + baracksKeyTexture.getSize().y / 2);
	itemTexts[3].setCharacterSize(15);

	parchmentSprite.setTexture(parchmentTexture);
	parchmentSprite.setOrigin(parchmentTexture.getSize().x / 2, parchmentTexture.getSize().y / 2);
	parchmentSprite.setPosition(screenW / 10, 500);

	itemTexts[4].setString("Parchment x");
	itemTexts[4].setFont(font);
	itemTexts[4].setPosition(screenW / 8, 470 + parchmentTexture.getSize().y / 2);
	itemTexts[4].setCharacterSize(15);

	inkBottleSprite.setTexture(inkBottleTexture);
	inkBottleSprite.setOrigin(inkBottleTexture.getSize().x / 2, inkBottleTexture.getSize().y / 2);
	inkBottleSprite.setScale(1.2f, 1.2f);
	inkBottleSprite.setPosition(screenW / 3.3, 100);

	itemTexts[5].setString("Ink Bottle x");
	itemTexts[5].setFont(font);
	itemTexts[5].setPosition(screenW / 3, 70 + inkBottleTexture.getSize().y / 2);
	itemTexts[5].setCharacterSize(15);

	gemSprite.setTexture(gemTexture);
	gemSprite.setOrigin(gemTexture.getSize().x / 2, gemTexture.getSize().y / 2);
	gemSprite.setScale(1.5f, 1.5f);
	gemSprite.setPosition(screenW / 3.3, 200);

	itemTexts[6].setString("Gems x");
	itemTexts[6].setFont(font);
	itemTexts[6].setPosition(screenW / 3, 170 + gemTexture.getSize().y / 2);
	itemTexts[6].setCharacterSize(15);

	appleSprite.setTexture(appleTexture);
	appleSprite.setOrigin(appleTexture.getSize().x / 2, appleTexture.getSize().y / 2);
	//appleSprite.setScale(1.5f, 1.5f);
	appleSprite.setPosition(screenW / 3.3, 300);

	itemTexts[7].setString("Apple x");
	itemTexts[7].setFont(font);
	itemTexts[7].setPosition(screenW / 3, 270 + appleTexture.getSize().y / 2);
	itemTexts[7].setCharacterSize(15);

	quillSprite.setTexture(quillTexture);
	quillSprite.setOrigin(quillTexture.getSize().x / 2, quillTexture.getSize().y / 2);
	//quillSprite.setScale(1.5f, 1.5f);
	quillSprite.setPosition(screenW / 3.3, 400);

	itemTexts[8].setString("Quill x");
	itemTexts[8].setFont(font);
	itemTexts[8].setPosition(screenW / 3, 370 + quillTexture.getSize().y / 2);
	itemTexts[8].setCharacterSize(15);

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
void Inventory::UseItem(int itemToUseIndex, Player& p)
{
	if (canMove == true)
	{
		if (drawableItems.at(itemToUseIndex) == i_healthPotion.key)
		{
			if (inventoryItems[i_healthPotion.key] > 0)
			{
				std::cout << "Using a health potion now" << std::endl;
				RemoveItemFromInventory(i_healthPotion.key, 1);
				std::cout << "Healing the player" << std::endl;
				p.setHealth(p.getHealth() + 25);
			}
			else std::cout << "you do not have any Health Potions" << std::endl;
		}

		else if (drawableItems.at(itemToUseIndex) == i_ale.key)
		{
			if (inventoryItems[i_ale.key] > 0)
			{
				std::cout << "Drinking a nice bottle of ale." << std::endl;
				RemoveItemFromInventory(i_ale.key, 1);
				std::cout << "Healed the player slightly. Add drunkness effect later...." << std::endl;
				p.setHealth(p.getHealth() + 7);
			}
			else std::cout << "You do not have any ale :(" << std::endl;
		}

		else if (drawableItems.at(itemToUseIndex) == i_bread.key)
		{
			if (inventoryItems[i_bread.key] > 0)
			{
				std::cout << "Eating some bread now." << std::endl;
				RemoveItemFromInventory(i_bread.key, 1);
				std::cout << "Healing the player." << std::endl;
				p.setHealth(p.getHealth() + 10);
			}
			else std::cout << "you do not have any Loaves of Bread" << std::endl;
		}

		else if (drawableItems.at(itemToUseIndex) == i_apple.key)
		{
			if (inventoryItems[i_apple.key] > 0)
			{
				std::cout << "Eating an apple now." << std::endl;
				RemoveItemFromInventory(i_apple.key, 1);
				std::cout << "Healing the player" << std::endl;
				p.setHealth(p.getHealth() + 10);//get the healing value from a file in future?
			}
			else std::cout << "You do not have any apples." << std::endl;
		}

		else if (drawableItems.at(itemToUseIndex) == i_gems.key)
		{
			if (inventoryItems[i_gems.key] > 0)
			{
				std::cout << "Now is not the time to use these gems." << std::endl;
			}
		}

		else if (drawableItems.at(itemToUseIndex) == i_baracksKey.key)
		{
			if (inventoryItems[i_baracksKey.key] > 0)
			{
				std::cout << "Now is not the time to use this key." << std::endl;
			}
		}

		else if (drawableItems.at(itemToUseIndex) == i_parchment.key)
		{
			if (inventoryItems[i_parchment.key] > 0)
			{
				std::cout << "Now is not the time to use this parchment." << std::endl;
			}
		}

		else if (drawableItems.at(itemToUseIndex) == i_inkBottle.key)
		{
			if (inventoryItems[i_inkBottle.key] > 0)
			{
				std::cout << "Now is not the time to use the ink in this bottle." << std::endl;
			}
		}

		else if (drawableItems.at(itemToUseIndex) == i_quill.key)
		{
			if (inventoryItems[i_quill.key] > 0)
			{
				std::cout << "Now is not the time to write a novel." << std::endl;
			}
		}
	}
	UpdateDrawableVector();
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

void Inventory::PositionText()
{
	for (int i = 0; i < drawableItems.size(); i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::string temp = itemTexts[j].getString();
			temp = temp.substr(0, temp.size() - 2);
			if (drawableItems.at(i) == temp)
			{
				std::cout << j << std::endl;
				itemTexts[j].setPosition(screenW / 8, i * 50);
			}
		}
	}
}

void Inventory::UpdateDrawableVector()
{
	std::cout << "DrawableItems.Size() before: " << drawableItems.size() << std::endl;
	for (auto it = drawableItems.begin(); it != drawableItems.end();)
	{
		if (inventoryItems[(*it)] <= 0)
		{
			it = drawableItems.erase(it);//erase the object(calls the objects destructor)
		}
		else ++it;
	}

	std::cout << "DrawableItems.Size() after: " << drawableItems.size() << std::endl;
}

/*Draw items that have a quantity > 0*/
void Inventory::Draw(sf::RenderTarget& window)
{
	CheckItemsToShow();
	PositionText();
	window.draw(backgroundSprite);
	window.draw(headerText);

	for (int i = 0; i < drawableItems.size(); i++)
	{
		if (drawableItems.at(i) == i_healthPotion.key)
		{
			//window.draw(healthPotSprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[0].setColor(sf::Color::Red);
			}
			else itemTexts[0].setColor(sf::Color::White);

			itemTexts[0].setString("Health Potion *" + std::to_string(CheckQuantity(i_healthPotion.key, false)));
			window.draw(itemTexts[0]);
		}
		else if (drawableItems.at(i) == i_ale.key)
		{
			//window.draw(aleBottleSprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[1].setColor(sf::Color::Red);
			}
			else itemTexts[1].setColor(sf::Color::White);

			itemTexts[1].setString("Bottle of Ale *" + std::to_string(CheckQuantity(i_ale.key, false)));
			window.draw(itemTexts[1]);
		}
		else if (drawableItems.at(i) == i_bread.key)
		{
			//window.draw(loafOfBreadSprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[2].setColor(sf::Color::Red);
			}
			else itemTexts[2].setColor(sf::Color::White);

			itemTexts[2].setString("Loaf of Bread *" + std::to_string(CheckQuantity(i_bread.key, false)));
			window.draw(itemTexts[2]);
		}
		else if (drawableItems.at(i) == i_baracksKey.key)
		{
			//window.draw(baracksKeySprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[3].setColor(sf::Color::Red);
			}
			else itemTexts[3].setColor(sf::Color::White);

			itemTexts[3].setString("Baracks key *" + std::to_string(CheckQuantity(i_baracksKey.key, false)));
			window.draw(itemTexts[3]);
		}
		else if (drawableItems.at(i) == i_parchment.key)
		{
			//window.draw(parchmentSprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[4].setColor(sf::Color::Red);
			}
			else itemTexts[4].setColor(sf::Color::White);

			itemTexts[4].setString("Parchment *" + std::to_string(CheckQuantity(i_parchment.key, false)));
			window.draw(itemTexts[4]);
		}
		else if (drawableItems.at(i) == i_inkBottle.key)
		{
			//window.draw(inkBottleSprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[5].setColor(sf::Color::Red);
			}
			else itemTexts[5].setColor(sf::Color::White);

			itemTexts[5].setString("Ink Bottle *" + std::to_string(CheckQuantity(i_inkBottle.key, false)));
			window.draw(itemTexts[5]);
		}
		else if (drawableItems.at(i) == i_gems.key)
		{
			//window.draw(gemSprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[6].setColor(sf::Color::Red);
			}
			else itemTexts[6].setColor(sf::Color::White);

			itemTexts[6].setString("Gems *" + std::to_string(CheckQuantity(i_gems.key, false)));
			window.draw(itemTexts[6]);
		}
		else if (drawableItems.at(i) == i_apple.key)
		{
			//window.draw(appleSprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[7].setColor(sf::Color::Red);
			}
			else itemTexts[7].setColor(sf::Color::White);

			itemTexts[7].setString("Apple *" + std::to_string(CheckQuantity(i_apple.key, false)));
			window.draw(itemTexts[7]);
		}
		else if (drawableItems.at(i) == i_quill.key)
		{
			//window.draw(quillSprite);

			if (currentlySelectedItem == i)
			{
				itemTexts[8].setColor(sf::Color::Red);
			}
			else itemTexts[8].setColor(sf::Color::White);

			itemTexts[8].setString("Quill *" + std::to_string(CheckQuantity(i_quill.key, false)));
			window.draw(itemTexts[8]);
		}
	}

	window.draw(exitHintSprite);
}

bool Inventory::getCanMove()
{
	return canMove;
}

void Inventory::setCanMove(bool b)
{
	canMove = b;
}

int Inventory::getCurrentlySelectedItem()
{
	return currentlySelectedItem;
}
