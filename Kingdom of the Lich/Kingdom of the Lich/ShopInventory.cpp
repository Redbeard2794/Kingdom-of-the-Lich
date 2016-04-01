#include "stdafx.h"
#include "ShopInventory.h"

//constructor. params: number of items in stock, owners name, gems owned by shop, path to stock file, screen width, screen height, font
ShopInventory::ShopInventory(int niStock, std::string oName, int availGems, std::string sfp, int sw, int sh, sf::Font f) : screenW(sw), screenH(sh), font(f)
{
	numItemsInStock = niStock;
	ownersName = oName;
	availableGems = availGems;
	stockFilePath = sfp;
	currentSelected = 0;
	canMove = true;

	LoadStock();

	if (tableTexture.loadFromFile("Assets/CharacterCreation/table/table" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png")) {}
	else tableTexture.loadFromFile("Assets/CharacterCreation/table/table1.png");	//if it fails load placeholder
	tableSprite.setTexture(tableTexture);
	tableSprite.setPosition(0, 5);

	shopMoneyText.setFont(font);
	shopMoneyText.setColor(sf::Color::White);
	shopMoneyText.setString("Shop Gems: " + std::to_string(availableGems));
	shopMoneyText.setPosition(screenW / 5, screenH - 50);

	playersMoney = 0;
	playerMoneyText.setFont(font);
	playerMoneyText.setColor(sf::Color::White);
	playerMoneyText.setString("Your Gems: " + std::to_string(playersMoney));
	playerMoneyText.setPosition(screenW / 1.3, screenH - 50);

	currentState = CHOICE;

	choices[0].setFont(font);
	choices[0].setColor(sf::Color::Cyan);
	choices[0].setString("Buy");
	choices[0].setPosition(screenW / 4, screenH / 2);
	choices[0].setCharacterSize(50);

	choices[1].setFont(font);
	choices[1].setColor(sf::Color::Black);
	choices[1].setString("Sell");
	choices[1].setPosition(screenW / 1.6, screenH / 2);
	choices[1].setCharacterSize(50);

	shopGreetText.setFont(font);
	shopGreetText.setColor(sf::Color::White);
	shopGreetText.setString("Hello, I am " + ownersName + ". Welcome to my shop.\n How can I help you?");
	shopGreetText.setPosition(screenW / 10, screenH / 5);
	shopGreetText.setCharacterSize(50);

	canBackOut = true;
}

//destructor
ShopInventory::~ShopInventory()
{
	stock.clear();//redo this so its proper
	itemQuantityTexts.clear();
}

//load the shops stock from an xml file
void ShopInventory::LoadStock()
{
	xml_document<> doc;
	std::ifstream file(stockFilePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<>* stockList = doc.first_node("StockList");
	xml_node<>* item = stockList->first_node("Item");

	while (item != NULL)
	{
		std::string key = item->first_node("key")->value();
		std::string texturePath = item->first_node("texturePath")->value();
		int quantity = std::atoi(item->first_node("quantity")->value());
		int value = std::atoi(item->first_node("value")->value());

		/*Create the item*/
		Item* i = new Item(key, texturePath, value);
		stock.push_back(std::make_pair(i, quantity));

		/*Move onto the next item object tag*/
		item = item->next_sibling("Item");
	}

	//position the items to be displayed
	for (int i = 0; i < numItemsInStock; i++)
	{
		stock.at(i).first->setPosition(sf::Vector2f(100 * ((i + 2.75)), screenH/2));
	}
	stock.at(currentSelected).first->setColor(sf::Color::Blue);

	//set up the quantity text and price text
	for (int i = 0; i < numItemsInStock; i++)
	{
		sf::Text* text = new sf::Text();
		text->setFont(font);
		text->setColor(sf::Color::White);
		text->setString(std::to_string(stock.at(i).second));
		text->setPosition(stock.at(i).first->getPosition().x + 30, stock.at(i).first->getPosition().y - 45);
		text->setCharacterSize(20);
		itemQuantityTexts.push_back(text);

		sf::Text* text2 = new sf::Text();
		text2->setFont(font);
		text2->setColor(sf::Color::White);
		text2->setString("Gems: "+std::to_string(stock.at(i).first->GetValue()));
		text2->setPosition(stock.at(i).first->getPosition().x-15, stock.at(i).first->getPosition().y+45);
		text2->setCharacterSize(20);
		itemPriceTexts.push_back(text2);
	}
}

//nav right in the menus
void ShopInventory::NavRight()
{
	if (canMove == true)
	{
		if (currentState == CHOICE)//if we are deciding between buying or selling stuff
		{
			if (currentSelected == 1)
			{
				currentSelected = 0;
				choices[0].setColor(sf::Color::Cyan);
				choices[1].setColor(sf::Color::Black);
			}
			else
			{
				currentSelected = 1;
				choices[1].setColor(sf::Color::Cyan);
				choices[0].setColor(sf::Color::Black);
			}
		}

		else if (currentState == BUY)//if we are buying stuff
		{
			if (currentSelected == numItemsInStock - 1)
				currentSelected = 0;
			else currentSelected += 1;

			for (int i = 0; i < numItemsInStock; i++)
			{
				stock.at(i).first->setColor(sf::Color::White);
			}
			stock.at(currentSelected).first->setColor(sf::Color::Blue);
		}

		else if (currentState == SELL)//if we are selling stuff
		{
			if (currentSelected == playerInvItems.size() - 1)
				currentSelected = 0;
			else currentSelected += 1;

			for (int i = 0; i < playerInvItems.size(); i++)
			{
				playerInvItems.at(i).first->setColor(sf::Color::White);
			}
			playerInvItems.at(currentSelected).first->setColor(sf::Color::Blue);
		}
	}
}

//nav left in menus
void ShopInventory::NavLeft()
{
	if (canMove == true)
	{
		if (currentState == CHOICE)//if we are deciding between buying or selling stuff
		{
			if (currentSelected == 0)
			{
				currentSelected = 1;
				choices[1].setColor(sf::Color::Cyan);
				choices[0].setColor(sf::Color::Black);
			}
			else
			{
				currentSelected = 0;
				choices[0].setColor(sf::Color::Cyan);
				choices[1].setColor(sf::Color::Black);
			}
		}

		else if (currentState == BUY)//if we are buying stuff
		{
			if (currentSelected == 0)
				currentSelected = numItemsInStock - 1;
			else currentSelected -= 1;

			for (int i = 0; i < numItemsInStock; i++)
			{
				stock.at(i).first->setColor(sf::Color::White);
			}
			stock.at(currentSelected).first->setColor(sf::Color::Blue);
		}

		else if (currentState == SELL)//if we are selling stuff
		{
			if (currentSelected == 0)
				currentSelected = playerInvItems.size() - 1;
			else currentSelected -= 1;

			for (int i = 0; i < playerInvItems.size(); i++)
			{
				playerInvItems.at(i).first->setColor(sf::Color::White);
			}
			playerInvItems.at(currentSelected).first->setColor(sf::Color::Blue);
		}
	}
}

//Update. param: players gems
void ShopInventory::Update(int playerG)
{
	//update the text showing the players and shops gems
	if (playersMoney != playerG)
		playersMoney = playerG;
	shopMoneyText.setString("Shop Gems: " + std::to_string(availableGems));
	playerMoneyText.setString("Your Gems: " + std::to_string(playersMoney));

	if (currentState == BUY)//if we are buying
	{
		//show the quantity and price of each item
		for (int i = 0; i < numItemsInStock; i++)
		{
			itemQuantityTexts.at(i)->setString("x" + std::to_string(stock.at(i).second));
			itemPriceTexts.at(i)->setString("Gems: " + std::to_string(stock.at(i).first->GetValue()));
		}
	}
	else if (currentState == SELL)//if we are selling
	{
		for (int i = 0; i < playerInvItems.size(); i++)
		{
			itemQuantityTexts.at(i)->setString("x" + std::to_string(playerInvItems.at(i).second));
			itemPriceTexts.at(i)->setString("Gems: " + std::to_string(playerInvItems.at(i).first->GetValue()));
		}
	}
}

//draw. param is a render target
void ShopInventory::Draw(sf::RenderTarget & window)
{
	window.draw(shopMoneyText);
	window.draw(playerMoneyText);

	if (currentState == CHOICE)//if we are deciding between buying or selling stuff
	{
		window.draw(choiceBackgroundSprite);
		window.draw(shopGreetText);
		for (int i = 0; i < 2; i++)
		{
			window.draw(choices[i]);
		}
	}
	else if (currentState == BUY)//if we are buying stuff
	{
		window.draw(tableSprite);
		for (int i = 0; i < numItemsInStock; i++)
		{
			window.draw(*stock.at(i).first);
			window.draw(*itemQuantityTexts.at(i));
			window.draw(*itemPriceTexts.at(i));
		}
	}
	else if (currentState == SELL)//if we are selling stuff
	{
		window.draw(tableSprite);
		for (int i = 0; i < playerInvItems.size(); i++)
		{
			window.draw(*playerInvItems.at(i).first);
			window.draw(*itemQuantityTexts.at(i));
			window.draw(*itemPriceTexts.at(i));
		}
	}
}

//choose BUY or SELL. param in a pointer to the players inventory(only used for selling as we need to grab items)
void ShopInventory::MakeChoice(Inventory* inv)
{
	if (currentSelected == 0)
	{
		currentSelected = 0;
		currentState = BUY;
	}
	else if (currentSelected == 1)
	{
		currentSelected = 0;
		currentState = SELL;
		SetPlayerSellableItems(inv);
	}
}

//buy an item. params are the player's gems and a pointer to the players inventory
void ShopInventory::PurchaseItem(int playerGems, Inventory * playerInv)
{
	std::string purchaseKey = GetKeyOfCurrentItem();
	int cost = GetPriceOfCurrentItem();

	if (playerGems >= cost)//if player has enough gems to buy the item
	{
		if (stock.at(currentSelected).second > 0)//if there is at least one of these items
		{
			playerInv->AddItemToInventory(purchaseKey, 1);//add item to inventorys
			stock.at(currentSelected).second -= 1;//take 1 from the stock
			playerInv->RemoveItemFromInventory("Gems", cost);//take the payment from the player
			availableGems += cost;//give the shop the gems
			AudioManager::GetInstance()->PlaySoundEffectById(19, false);
		}
		else std::cout << purchaseKey << " is out of stock at the moment." << std::endl;
	}
	else
	{
		std::cout << "You do not possess enough gems to buy " << purchaseKey << std::endl;
		AudioManager::GetInstance()->PlaySoundEffectById(20, false);
	}
}

//sell an item. params are the player's gems and a pointer to the player's inventory
void ShopInventory::SellItem(int playerGems, Inventory * playerInv)
{
	if (playerInvItems.size() > 0)//if the player has at least 1 item
	{
		std::string sellKey = playerInvItems.at(currentSelected).first->RetrieveKey();
		int price = playerInvItems.at(currentSelected).first->GetValue();

		if (availableGems >= price)//if the shop keeper has enough gems to buy the item
		{
			if (playerInvItems.at(currentSelected).second > 0)//if there is at least one of the items
			{
				playerInv->RemoveItemFromInventory(sellKey, 1);//remove it from the player's inventory
				playerInvItems.at(currentSelected).second -= 1;//decrease the quantity
				playerInv->AddItemToInventory("Gems", price);//give the player their gems
				availableGems -= price;//take the gems from the shop keeper
				playerInvItems.clear();
				SetPlayerSellableItems(playerInv);//grab the player's inventory again
				AudioManager::GetInstance()->PlaySoundEffectById(19, false);
			}
		}
		else
		{
			std::cout << "The shopkeeper does not have enough gems to buy the item." << std::endl;
			AudioManager::GetInstance()->PlaySoundEffectById(20, false);
		}
	}
}

//grab the player's inventory in order to display items for them to sell. param is a pointer to the player's inventory
void ShopInventory::SetPlayerSellableItems(Inventory * playerInv)
{
	std::vector<std::string> keys;
	for (int i = 0; i < playerInv->itemSlots.size(); i++)
	{
		keys.push_back(playerInv->itemSlots.at(i)->GetCurrentItemKey());//get the item key for each item
	}

	for (int i = 0; i < keys.size(); i++)//go through these keys
	{
		int v = 0;
		std::string texPath;

		for (int j = 0; j < stock.size(); j++)
		{
			if (keys.at(i) == stock.at(j).first->RetrieveKey())//if the item is one that can possibly be sold by the shop keeper
			{
				v = stock.at(j).first->GetValue();
				texPath = stock.at(j).first->GetTextPath();
				break;
			}
		}
		if (v != 0)//if the item has a value
		{
			//make an item
			Item* it = new Item(keys.at(i), texPath, v);
			playerInvItems.push_back(std::make_pair(it, playerInv->CheckQuantity(keys.at(i), false)));

			//set the positions for the items
			for (int i = 0; i < playerInvItems.size(); i++)
			{
				playerInvItems.at(i).first->setPosition(sf::Vector2f(100 * ((i + 1)), 100));
			}
			playerInvItems.at(0).first->setColor(sf::Color::Blue);
		}
	}
}

std::string ShopInventory::GetKeyOfCurrentItem()
{
	return stock.at(currentSelected).first->RetrieveKey();
}

int ShopInventory::GetPriceOfCurrentItem()
{
	return stock.at(currentSelected).first->GetValue();
}

void ShopInventory::SetChoiceTexture(int pRace, int pGender)
{
	if (pRace == 0)//human
	{
		if (pGender == 0)//male
		{
			choiceBackgroundTexture.loadFromFile("Assets/Shops/ChoiceBackgrounds/" + ownersName + "/humanMale/ChoiceScreen" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png");
		}
		else if (pGender == 1)//female
		{
			choiceBackgroundTexture.loadFromFile("Assets/Shops/ChoiceBackgrounds/" + ownersName + "/humanFemale/ChoiceScreen" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png");
		}
	}
	else if (pRace == 1)//elf
	{
		if (pGender == 0)//male
		{
			choiceBackgroundTexture.loadFromFile("Assets/Shops/ChoiceBackgrounds/" + ownersName + "/elfMale/ChoiceScreen" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png");
		}
		else if (pGender == 1)//female
		{
			choiceBackgroundTexture.loadFromFile("Assets/Shops/ChoiceBackgrounds/" + ownersName + "/elfFemale/ChoiceScreen" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png");
		}
	}
	else if (pRace == 2)//dwarf
	{
		if (pGender == 0)//male
		{
			choiceBackgroundTexture.loadFromFile("Assets/Shops/ChoiceBackgrounds/" + ownersName + "/dwarfMale/ChoiceScreen" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png");
		}
		else if (pGender == 1)//female
		{
			choiceBackgroundTexture.loadFromFile("Assets/Shops/ChoiceBackgrounds/" + ownersName + "/dwarfFemale/ChoiceScreen" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png");
		}
	}

	choiceBackgroundSprite.setTexture(choiceBackgroundTexture);
	choiceBackgroundSprite.setPosition(0, 0);
}

//check how many items the shop has in stock
int ShopInventory::CheckNumItemsInStock()
{
	return numItemsInStock;
}

//set the number of items in stock to be the number passed in
void ShopInventory::SetNumItemsInStock(int i)
{
	numItemsInStock = i;
}

//retrieve the name of the shop's owner
std::string ShopInventory::GetOwnersName()
{
	return ownersName;
}

//Check how many gems the shop has to barter with
int ShopInventory::GetAvailableGems()
{
	return availableGems;
}

//set the number of gems the shop has to barter with
void ShopInventory::SetAvalailableGems(int g)
{
	availableGems = g;
}

bool ShopInventory::GetCanMove()
{
	return canMove;
}

void ShopInventory::SetCanMove(bool sel)
{
	canMove = sel;
}

bool ShopInventory::GetCanSelect()
{
	return canSelect;
}

void ShopInventory::SetCanSelect(bool sel)
{
	canSelect = sel;
}

int ShopInventory::GetCurrentState()
{
	return currentState;
}

void ShopInventory::SetCurrentState(int s)
{
	currentState = s;
}

bool ShopInventory::GetCanBackOut()
{
	return canBackOut;
}

void ShopInventory::SetCanBackOut(bool c)
{
	canBackOut = c;
}
