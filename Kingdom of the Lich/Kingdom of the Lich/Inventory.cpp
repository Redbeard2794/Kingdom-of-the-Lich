#include "stdafx.h"
#include "Inventory.h"

/*Constructor*/
Inventory::Inventory(sf::Font f, bool controller, int sw, int sh) : font(f), showControllerHints(controller)
{
	screenW = sw;
	screenH = sh;

	currentlySelectedItem = 0;
	canMove = true;
	canSelect = true;

	std::vector<std::string> allKeys;
	std::string line;
	std::ifstream myfile("Assets/Inventory/itemKeys.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			allKeys.push_back(line);
		}
		myfile.close();
	}
	else std::cout << "Unable to open itemKeys.txt file!" << std::endl;

	i_healthPotion.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);
	i_ale.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);
	i_bread.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);
	i_apple.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);
	i_gems.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);
	i_baracksKey.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);
	i_parchment.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);
	i_inkBottle.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);
	i_quill.key = allKeys.at(0);
	allKeys.erase(allKeys.begin() + 0);

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
	aleBottleTexture.loadFromFile("Assets/Tiles/indoorTiles/indoor assets/indoorAssets2/clutterObjects/bottles/bottle2.png");
	loafOfBreadTexture.loadFromFile("Assets/Icons/Items/loafOfBread.png");
	baracksKeyTexture.loadFromFile("Assets/Icons/Items/key.png");
	parchmentTexture.loadFromFile("Assets/Icons/Items/parchmentIcon.png");
	inkBottleTexture.loadFromFile("Assets/Icons/Items/inkBottle.png");
	gemTexture.loadFromFile("Assets/Icons/Items/gemsIcon.png");
	appleTexture.loadFromFile("Assets/Icons/Items/apple.png");
	quillTexture.loadFromFile("Assets/Icons/Items/quill.png");

	//set up item sprites and text
	healthPotSprite.setTexture(healthPotTexture);
	healthPotSprite.setOrigin(healthPotTexture.getSize().x / 2, healthPotTexture.getSize().y / 2);
	healthPotSprite.setPosition(screenW / 10, 100);

	aleBottleSprite.setTexture(aleBottleTexture);
	aleBottleSprite.setOrigin(aleBottleTexture.getSize().x / 2, aleBottleTexture.getSize().y / 2);
	aleBottleSprite.setScale(3, 2.7f);
	aleBottleSprite.setPosition(screenW / 10, 200);

	loafOfBreadSprite.setTexture(loafOfBreadTexture);
	loafOfBreadSprite.setOrigin(loafOfBreadTexture.getSize().x / 2, loafOfBreadTexture.getSize().y / 2);
	loafOfBreadSprite.setScale(2, 1.7f);
	loafOfBreadSprite.setPosition(screenW / 10, 300);

	baracksKeySprite.setTexture(baracksKeyTexture);
	baracksKeySprite.setOrigin(baracksKeyTexture.getSize().x / 2, baracksKeyTexture.getSize().y / 2);
	baracksKeySprite.setRotation(-30);
	baracksKeySprite.setPosition(screenW / 10, 400);

	parchmentSprite.setTexture(parchmentTexture);
	parchmentSprite.setOrigin(parchmentTexture.getSize().x / 2, parchmentTexture.getSize().y / 2);
	parchmentSprite.setPosition(screenW / 10, 500);

	inkBottleSprite.setTexture(inkBottleTexture);
	inkBottleSprite.setOrigin(inkBottleTexture.getSize().x / 2, inkBottleTexture.getSize().y / 2);
	inkBottleSprite.setScale(1.2f, 1.2f);
	inkBottleSprite.setPosition(screenW / 3.3, 100);

	gemSprite.setTexture(gemTexture);
	gemSprite.setOrigin(gemTexture.getSize().x / 2, gemTexture.getSize().y / 2);
	gemSprite.setScale(1.5f, 1.5f);
	gemSprite.setPosition(screenW / 3.3, 200);

	appleSprite.setTexture(appleTexture);
	appleSprite.setOrigin(appleTexture.getSize().x / 2, appleTexture.getSize().y / 2);
	//appleSprite.setScale(1.5f, 1.5f);
	appleSprite.setPosition(screenW / 3.3, 300);

	quillSprite.setTexture(quillTexture);
	quillSprite.setOrigin(quillTexture.getSize().x / 2, quillTexture.getSize().y / 2);
	//quillSprite.setScale(1.5f, 1.5f);
	quillSprite.setPosition(screenW / 3.3, 400);

	//hints
	if (showControllerHints == true)
		exitHintTexture.loadFromFile("Assets/ControllerHints/pressBackToReturnToGameHint.png");
	else if (showControllerHints == false)
		exitHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/PressEnterToReturnToGameHint.png");
	exitHintSprite.setTexture(exitHintTexture);
	exitHintSprite.setOrigin(exitHintTexture.getSize().x / 2, exitHintTexture.getSize().y / 2);
	exitHintSprite.setPosition(screenW/2.1, screenH/1.05);

	moveHintTexture.loadFromFile("Assets/ControllerHints/useLeftStickToMoveHintWhite.png");
	moveHintSprite.setTexture(moveHintTexture);
	moveHintSprite.setOrigin(moveHintTexture.getSize().x / 2, moveHintTexture.getSize().y / 2);
	moveHintSprite.setPosition(screenW / 10, screenH / 1.05);

	selectHintTexture.loadFromFile("Assets/ControllerHints/pressAtoSelectHintWhite.png");
	selectHintSprite.setTexture(selectHintTexture);
	selectHintSprite.setOrigin(selectHintTexture.getSize().x / 2, selectHintTexture.getSize().y / 2);
	selectHintSprite.setPosition(screenW / 1.13, screenH / 1.05);

	itemToStealKey = "";
	itemToStealQuantity = 0;
}

/*Destructor*/
Inventory::~Inventory()
{
	//blank for the moment
}

/*Initialise all items in inventory to have '0' quantity*/
void Inventory::InitialiseInventoryItems()
{
	for (int i = 0; i < itemKeys.size(); i++)
	{
		inventoryItems[itemKeys.at(i)] = 0;

		//for (int j = 0; j < itemSlots.size(); j++)
		//{
		//	if (itemSlots.at(j)->IsOpen())
		//	{
		//		itemSlots.at(j)->FillSlot(itemKeys.at(j));
		//		break;
		//	}
		//}
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

				bool foundKey = false;
				for (int i = 0; i < itemSlots.size(); i++)
				{
					if (itemSlots.at(i)->GetCurrentItemKey() == itemToAddTo)
						foundKey = true;
				}
				if(foundKey == false)
					itemSlots.push_back(new ItemSlot(itemToAddTo, itemSlots.size() + 1, font));

			}
			else std::cout << "Could not add " << quantityToAdd << " " << itemToAddTo << " as it is at max capacity." << std::endl;
		}
	}
	CalculateFilledSlots();
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
				if (inventoryItems[itemToRemoveFrom] == 0)
				{
					for (int i = 0; i < itemSlots.size(); i++)
					{
						if (itemSlots.at(i)->GetCurrentItemKey() == itemToRemoveFrom)
						{
							itemSlots.at(i)->EmptySlot();
							break;
						}
					}
				}
			}
			else std::cout << "Could not remove item as there is already 0 of this item." << std::endl;
		}
	}
	ReorderSlots();
	CalculateFilledSlots();
}

/*
Use an item from the inventory
parameter is the itme to use
*/
void Inventory::UseItem(Player& p, AudioManager& audioManager)
{
	std::string itemToUse = itemSlots.at(currentlySelectedItem)->GetCurrentItemKey();
	if (canMove == true)
	{
		if (itemToUse == i_healthPotion.key)
		{
			if (inventoryItems[i_healthPotion.key] > 0 && p.getHealth() <100)
			{
				audioManager.PlaySoundEffectById(8, false);
				std::cout << "Using a health potion now" << std::endl;
				RemoveItemFromInventory(i_healthPotion.key, 1);
				std::cout << "Healing the player" << std::endl;
				p.setHealth(p.getHealth() + 25);
				p.IncreasePotionsDrank(1);
				p.Notify();
			}
			else std::cout << "you do not have any Health Potions or already have max health." << std::endl;
		}

		if (itemToUse == i_ale.key)
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

		if (itemToUse == i_bread.key)
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

		if (itemToUse == i_apple.key)
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

		if (itemToUse == i_gems.key)
		{
			if (inventoryItems[i_gems.key] > 0)
			{
				audioManager.PlaySoundEffectById(1, false);
				std::cout << "Now is not the time to use these gems." << std::endl;
			}
		}

		if (itemToUse == i_baracksKey.key)
		{
			if (inventoryItems[i_baracksKey.key] > 0)
			{
				audioManager.PlaySoundEffectById(1, false);
				std::cout << "Now is not the time to use this key." << std::endl;
			}
		}

		if (itemToUse == i_parchment.key)
		{
			if (inventoryItems[i_parchment.key] > 0)
			{
				audioManager.PlaySoundEffectById(1, false);
				std::cout << "Now is not the time to use this parchment." << std::endl;
			}
		}

		if (itemToUse == i_inkBottle.key)
		{
			if (inventoryItems[i_inkBottle.key] > 0)
			{
				audioManager.PlaySoundEffectById(1, false);
				std::cout << "Now is not the time to use the ink in this bottle." << std::endl;
			}
		}

		if (itemToUse == i_quill.key)
		{
			if (inventoryItems[i_quill.key] > 0)
			{
				audioManager.PlaySoundEffectById(1, false);
				std::cout << "Now is not the time to write a novel." << std::endl;
			}
		}
	}
}

/*Figure out how many item slots are filled*/
void Inventory::CalculateFilledSlots()
{
	numFilledSlots = 0;
	for (int i = 0; i < itemSlots.size(); i++)
	{
		if (itemSlots.at(i)->IsOpen() == false)
			numFilledSlots++;
	}
	std::cout << "Filled slots: " << numFilledSlots << std::endl;
}

/*Re-order item slots after an item has been used up and its slot removed*/
void Inventory::ReorderSlots()
{
	int removeIndex = -1;
	for (int i = 0; i < itemSlots.size(); i++)
	{
		if (itemSlots.at(i)->IsOpen())//if the slot was emptied(last item of that type was removed from it)
		{
			currentlySelectedItem = 0;
			itemSlots.erase(itemSlots.begin() + i);//erase it from the vector
			removeIndex = i;//store the index it was found at
		}
	}

	if (itemSlots.size() > 1 && removeIndex != -1)//if there is more than 1 item in the inventory
	{
		for (int i = removeIndex; i < itemSlots.size(); i++)
		{
			itemSlots.at(i)->ResetSlotNumAndPos(itemSlots.at(i)->GetSlotNumber() - 1);//move all slots after the removed slot down a slot
		}
	}
}

/*Choose an item for a thief to steal*/
void Inventory::SetItemToSteal()
{
	std::vector<std::string> possibleItemsToSteal;

	//look for items with quantity > 0
	std::map<std::string, int>::iterator it;
	for (it = inventoryItems.begin(); it != inventoryItems.end(); ++it)
	{
		if (it->second > 0)
		{
			possibleItemsToSteal.push_back(it->first);
		}
	}

	int index = 0;

	if(possibleItemsToSteal.size() > 1)
		index = rand() % (possibleItemsToSteal.size() - 1);

	itemToStealKey = possibleItemsToSteal.at(index);
}

void Inventory::NavigateUp()
{
	if (canMove)
	{
		if (currentlySelectedItem == itemSlots.size()-1)
			currentlySelectedItem = 0;
		else currentlySelectedItem++;
	}
}

void Inventory::NavigateDown()
{
	if (canMove)
	{
		if (currentlySelectedItem == 0)
			currentlySelectedItem = itemSlots.size() -1;
		else currentlySelectedItem--;
	}
}


/*Draw items that have a quantity > 0*/
void Inventory::Draw(sf::RenderTarget& window)
{
	window.draw(backgroundSprite);
	window.draw(headerText);

	for (int i = 0; i < itemSlots.size(); i++)
	{
		if (itemSlots.at(i)->IsOpen() == false)
		{
			if(currentlySelectedItem == i)
				itemSlots.at(i)->Draw(window, inventoryItems[itemSlots.at(i)->GetCurrentItemKey()], sf::Color::Red, true);
			else itemSlots.at(i)->Draw(window, inventoryItems[itemSlots.at(i)->GetCurrentItemKey()], sf::Color::White, false);

			if (itemSlots.at(i)->GetCurrentItemKey() == i_healthPotion.key)
			{
				healthPotSprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(healthPotSprite);
			}
			else if (itemSlots.at(i)->GetCurrentItemKey() == i_ale.key)
			{
				aleBottleSprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(aleBottleSprite);
			}

			else if (itemSlots.at(i)->GetCurrentItemKey() == i_bread.key)
			{
				loafOfBreadSprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(loafOfBreadSprite);
			}

			else if (itemSlots.at(i)->GetCurrentItemKey() == i_apple.key)
			{
				appleSprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(appleSprite);
			}

			else if (itemSlots.at(i)->GetCurrentItemKey() == i_gems.key)
			{
				gemSprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(gemSprite);
			}

			else if (itemSlots.at(i)->GetCurrentItemKey() == i_baracksKey.key)
			{
				baracksKeySprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(baracksKeySprite);
			}

			else if (itemSlots.at(i)->GetCurrentItemKey() == i_parchment.key)
			{
				parchmentSprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(parchmentSprite);
			}

			else if (itemSlots.at(i)->GetCurrentItemKey() == i_inkBottle.key)
			{
				inkBottleSprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(inkBottleSprite);
			}

			else if (itemSlots.at(i)->GetCurrentItemKey() == i_quill.key)
			{
				quillSprite.setPosition(250, 75 * itemSlots.at(i)->GetSlotNumber());
				window.draw(quillSprite);
			}
		}
	}

	window.draw(exitHintSprite);
	window.draw(moveHintSprite);
	window.draw(selectHintSprite);
}

bool Inventory::getCanMove()
{
	return canMove;
}

void Inventory::setCanMove(bool b)
{
	canMove = b;
}

bool Inventory::getCanSelect()
{
	return canSelect;
}

void Inventory::setCanSelect(bool cs)
{
	canSelect = cs;
}

int Inventory::getCurrentlySelectedItem()
{
	return currentlySelectedItem;
}

void Inventory::setCurrentlySelectedItem(int i)
{
	currentlySelectedItem = i;
}

std::string Inventory::GetItemToSteal()
{
	return itemToStealKey;
}

int Inventory::GetItemToStealQuantity()
{
	return itemToStealQuantity;
}

void Inventory::SetItemToStealQuantity(int q)
{
	itemToStealQuantity = q;
}
